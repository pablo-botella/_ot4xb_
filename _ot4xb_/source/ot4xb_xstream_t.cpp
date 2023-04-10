//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#define _CRT_SECURE_NO_DEPRECATE
#include <ot4xb_api.h>
// -----------------------------------------------------------------------------------------------------------------
void  xstream_t::_init_heap_( void )
{
   ; // nothing to do under this implementation
}
//----------------------------------------------------------------------------------------------------------------------
void  xstream_t::_release_heap_( void )
{
   ; // nothing to do under this implementation
}
// -----------------------------------------------------------------------------------------------------------------
void* xstream_t::_alloc_memory_( UINT n )
{
   return _xgrab(n);
}
// -----------------------------------------------------------------------------------------------------------------
void  xstream_t::_free_memory_( void* p )
{
   _xfree(p);
}
// -----------------------------------------------------------------------------------------------------------------
xstream_t::xstream_t( DWORD nInitialSize , DWORD nBlockSize)
{
   m_pBuffer    = 0;
   m_nBuffSize  = 0;
   m_nLen       = 0;
   m_nBlockSize = nBlockSize;
   _init_heap_();
   if( nInitialSize )
   {
      _grow_( nInitialSize );
   }
}
// -----------------------------------------------------------------------------------------------------------------
xstream_t::~xstream_t()
{
   if( m_pBuffer )
   {
      _free_memory_( (void*) m_pBuffer );
      m_pBuffer    = 0;
   }
   m_nBuffSize  = 0;
   m_nLen       = 0;
   m_nBlockSize = 0;
   _release_heap_();
}
// -----------------------------------------------------------------------------------------------------------------
BOOL xstream_t::_grow_( DWORD nNewSize )
{
   if( ((int) nNewSize) < 0 ){ return FALSE; }
   if( m_nBuffSize >= nNewSize ){ return TRUE; } // nothing to do
   if( ((int) m_nBlockSize) > 2 ) // check if using granularity
   {
      nNewSize += (nNewSize % m_nBlockSize);
   }
   void* p = _alloc_memory_( nNewSize );
   if( m_pBuffer )
   {
      if( m_nLen )
      {
         _bcopy( (LPBYTE) p, (LPBYTE) m_pBuffer , m_nLen );
      }
      _free_memory_( (void*) m_pBuffer );
   }
   m_pBuffer = p;
   m_nBuffSize = nNewSize;
   return TRUE;
}
// -----------------------------------------------------------------------------------------------------------------
void* xstream_t::_reserve_bytes_( DWORD nBytes )
{
   if( ((int) nBytes) < 1 )
   {
      return 0;
   }

   if( !_grow_( m_nLen + nBytes ) )
   {
      return 0;
   }
   return _mk_ptr_(LPVOID,m_pBuffer,m_nLen);
}
// -----------------------------------------------------------------------------------------------------------------
void*  xstream_t::_reserve_bytes_( DWORD offset , DWORD nBytes )      
{
   if( offset > m_nLen )
   {
      return 0;
   }
   if( ((int) nBytes) < 1 )
   {
      return 0;
   }

   if( !_grow_( offset + nBytes ) )
   {
      return 0;
   }
   return _mk_ptr_(LPVOID,m_pBuffer,offset);
}

// -----------------------------------------------------------------------------------------------------------------
void*  xstream_t::_offset_ptr_( DWORD offset , DWORD cb )
{
   if( m_nLen < (offset + cb) ){ return 0; }
   if( !m_pBuffer ){ return 0; }
   return _mk_ptr_(LPVOID,m_pBuffer,offset);
}
// -----------------------------------------------------------------------------------------------------------------
DWORD xstream_t::_offset_len_( DWORD offset )
{
   if( offset >= m_nLen ){ return 0; }
   return (m_nLen - offset);
}
// -----------------------------------------------------------------------------------------------------------------
DWORD xstream_t::_truncate_buffer_( DWORD len )
{
   if( len > m_nLen ){ len = m_nLen; }
   if( m_nLen > m_nBuffSize ){ m_nLen = m_nBuffSize; }
   m_nLen = len;
   return m_nLen;
}
// -----------------------------------------------------------------------------------------------------------------
BOOL xstream_t::_skip_bytes_( DWORD nBytes )
{
   if( !_reserve_bytes_(nBytes) )
   {
      return FALSE;
   }
   m_nLen += nBytes;
   return TRUE;
}
// -----------------------------------------------------------------------------------------------------------------
BOOL xstream_t::append_buffer(void* p , DWORD cb )
{
   LPBYTE dst = (LPBYTE) _reserve_bytes_(cb);
   if( !dst ){ return FALSE; }
   if( cb == (DWORD) -1 )
   {
      cb = _xstrlen((LPSTR) p );
   }
   _bcopy(dst,(LPBYTE) p , cb );
   m_nLen += cb;
   return TRUE;
}
// -----------------------------------------------------------------------------------------------------------------
BOOL xstream_t::append_BYTE(BYTE n)
{
   return append_buffer( (void*) &n , sizeof(BYTE) );
}
// -----------------------------------------------------------------------------------------------------------------
BOOL xstream_t::append_WORD(WORD n)
{
   return append_buffer( (void*) &n , sizeof(WORD) );
}
// -----------------------------------------------------------------------------------------------------------------
BOOL xstream_t::append_DWORD(DWORD n)
{
   return append_buffer( (void*) &n , sizeof(DWORD) );
}
// -----------------------------------------------------------------------------------------------------------------
void xstream_t::ansi_ZTrim(void)
{
   if( m_pBuffer && m_nLen )
   {
      for( ; m_nLen ; m_nLen-- )
      {
         if( reinterpret_cast<LPSTR>(m_pBuffer)[(m_nLen - 1)] ){ return; }
      }
   }
}
// -----------------------------------------------------------------------------------------------------------------
void xstream_t::ansi_ZSafe(void)
{
   _reserve_bytes_(1);
   if( m_nLen == 0 ){append_BYTE(0); }
   if( reinterpret_cast<LPSTR>(m_pBuffer)[(m_nLen - 1)] ){ append_BYTE(0); }
}
// -----------------------------------------------------------------------------------------------------------------
BOOL xstream_t::append_ansi_to_utf8(LPSTR pa , int cb)
{
   if(pa)
   {
      int    cc = 0;
      LPWSTR pw = ansi2w(pa, cb,&cc);
      if( pw )
      {
         int   cbu = 0;
         LPSTR  pu = 0;
         cbu = WideCharToMultiByte(CP_UTF8,0,pw,cc,NULL,0,0,0);
         pu = (LPSTR) _reserve_bytes_( ((DWORD) cbu ) + 2 );
         _skip_bytes_( WideCharToMultiByte(CP_UTF8,0,pw,cc,pu,cbu,0,0) );
         _xfree((void*) pw);
         pw = 0;
         return TRUE;
      }
   }
   return FALSE;
}
// -----------------------------------------------------------------------------------------------------------------
BOOL xstream_t::append_ansi_to_xform_utf8(LPSTR p , int cb, int nLevel)
{
   if( !p ){ return FALSE; }
   if( cb < 0 ){ cb = lstrlenA(p); }
   if( cb < 1 ){ return FALSE; }
   _reserve_bytes_(((DWORD) cb) + 16);
   int n;
   for( n=0; n < cb ; n++ )
   {
      LPBYTE dst = (LPBYTE) _reserve_bytes_(16);
      _skip_bytes_( (DWORD) ansi_byte_to_utf8_urlenc((BYTE) p[n],dst,nLevel) );
   }
   return TRUE;
}
// -----------------------------------------------------------------------------------------------------------------
BOOL xstream_t::append_decode_qp(LPSTR p , int cb , DWORD nFlags ) // flags: 1 dot , 2 add CRLF
{
   if( !p ){ return FALSE; }
   if( cb < 0 ){ cb = lstrlenA(p); }
   if( cb < 1 ){ return FALSE; }
   int cb_out = ot4xb_qp_decode_required_length(cb) + 16;
   LPSTR dst = (LPSTR) _reserve_bytes_(cb_out + 16);
   if( ot4xb_qp_decode((LPBYTE) p,cb,dst,&cb_out,nFlags) )
   {
      _skip_bytes_((DWORD) cb_out);
      return TRUE;      
   }
   return FALSE;
}
//----------------------------------------------------------------------------------------------------------------------
BOOL xstream_t::append_decode_base64(LPSTR p , int cb)
{
   if( !p ){ return FALSE; }
   if( cb < 0 ){ cb = lstrlenA(p); }
   if( cb < 1 ){ return FALSE; }
   int cb_out = ot4xb_base64_decode_required_length(cb) + 16;
   LPBYTE dst = (LPBYTE) _reserve_bytes_(cb_out + 16);   
   if( ot4xb_base64_decode(p,cb,dst,&cb_out) )
   {
      _skip_bytes_((DWORD) cb_out);
      return TRUE;      
   }
   return FALSE;
}
// -----------------------------------------------------------------------------------------------------------------
BOOL xstream_t::append_encode_ot4xb(LPSTR ps, int cbs, DWORD nFlags) // 1 % , 2 " , 8 extra spaces
{
	UINT n;

	if (!ps) { return FALSE; }
	if (cbs < 0) { cbs = lstrlenA(ps); }
	if (cbs < 1) { return FALSE; }
	_reserve_bytes_((DWORD)cbs + 1024);

	for (n = 0; n < (ULONG) cbs; n++)
	{
		BYTE ch = (BYTE)ps[n];
		switch (ch)
		{
		case 0: {append_buffer((void*) "\\0", 2); break; }
		case 0x20:
		{
			if (nFlags & 8)
			{
				if (n == (ULONG)cbs) { append_buffer((void*)"\\s", 2); }
				else
				{
					if (((BYTE)ps[(n + 1)]) == ch) { append_buffer((void*)"\\s", 2); }
					else { append_buffer((void*)&ch, 1); }
				}
			}
			else
			{
				append_buffer((void*)&ch, 1);
			}
			break;
		}
		case '%': 
		{
			if (nFlags & 1)
			{
				append_buffer((void*) "\\x25", 4);
			}
			else
			{
				append_buffer((void*)&ch, 1);
			}
			break; 
		}
		case '"': 
		{
			if (nFlags & 4)
			{
				append_buffer((void*) "\\q", 2);
			}
			else
			{
				append_buffer((void*)&ch, 1);
			}
			break; 
		} //  Double Quote
		case '&': { append_buffer((void*) "\\x26", 4); break; }
		case '<': { append_buffer((void*) "\\x3C", 4); break; }
		case '>': { append_buffer((void*) "\\x3E", 4); break; }
		case '\a': {append_buffer((void*) "\\a", 2); break; } //  Bell (alert)
		case '\b': {append_buffer((void*) "\\b", 2); break; } //  Backspace
		case '\f': {append_buffer((void*) "\\f", 2); break; } //  Formfeed
		case '\n': {append_buffer((void*) "\\n", 2); break; } //  New line
		case '\r': {append_buffer((void*) "\\r", 2); break; } //  Carriage return
		case '\t': {append_buffer((void*) "\\t", 2); break; } //  Horizontal tab
		case '\v': {append_buffer((void*) "\\v", 2); break; } //  Vertical tab
		case '\\': {append_buffer((void*) "\\", 1); append_buffer((void*) "\\", 1); break; } //  Backslash
		default:
		{
			if ((ch < 32) || (ch > 127))
			{
				LPSTR p = (LPSTR)_reserve_bytes_(16);
				_skip_bytes_(wsprintfA(p, "\\x%02.2X", ch));
			}
			else
			{
				append_buffer((void*)&ch, 1);
				break;
			}
		}
		}
	}
	return TRUE;
}
// -----------------------------------------------------------------------------------------------------------------
BOOL xstream_t::append_decode_uu(LPSTR p , int cb)
{
   if( !p ){ return FALSE; }
   if( cb < 0 ){ cb = lstrlenA(p); }
   if( cb < 1 ){ return FALSE; }
   int cb_out = ot4xb_uu_decode_required_length(cb) + 16;
   LPBYTE dst = (LPBYTE) _reserve_bytes_(cb_out + 16);   
   if( ot4xb_uu_decode((LPBYTE) p,cb,dst,&cb_out) )
   {
      _skip_bytes_((DWORD) cb_out);
      return TRUE;      
   }
   return FALSE;
}
// -----------------------------------------------------------------------------------------------------------------
void* xstream_t::Detach(UINT* pcb , UINT* pcs )
{
   void* p = m_pBuffer; 
   if( pcb ) pcb[0] = m_nLen;
   if( pcs ) pcs[0] = m_nBuffSize;
   m_pBuffer = 0; m_nBuffSize = 0; m_nLen = 0;
   return p;
}
// -----------------------------------------------------------------------------------------------------------------


