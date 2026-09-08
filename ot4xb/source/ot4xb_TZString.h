//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#ifndef _API_cpp_TZString_h_
#define _API_cpp_TZString_h_
//----------------------------------------------------------------------------------------------------------------------
#ifdef __cplusplus
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-class}}*/
/*{{cpp-class_: TZString
   | parent: {{ilink: <cpp-class T_ot4xb_base> T_ot4xb_base}}
   | category: c-api/classes , memory/string
   | desc: A growable, always zero-terminated string builder: every Add* appends at the end, growing the buffer
     by powers of two in the ot4xb heap, and the text is ready as a C string at any moment through
     GetBuffer(). Besides plain appends it has the escapers ot4xb needs when it writes text for other
     consumers: HTML from the OEM and ANSI code pages, XML, SQL literals, JSON strings, UTF-8 and CSV cells.
     printf() formats straight into the buffer.
     | _kw_: TZString, Class }}*/
class OT4XB_API TZString : public T_ot4xb_base
{
   public:
       /*{{|member_: `LPSTR m_pBuffer` | desc_: The text, zero-terminated; 0 before the first append. }}*/
       LPSTR       m_pBuffer;
       /*{{|member_: `UINT m_nBuffSize` | desc_: Bytes allocated (64 at least, then doubled). }}*/
       UINT        m_nBuffSize;
       /*{{|member_: `UINT m_nLen` | desc_: Length of the text, terminator not counted. }}*/
       UINT        m_nLen;
       /*{{|member_: `UINT m_nMinPrintf` | desc_: Bytes reserved for one printf() call, raised in 1 KB steps
          when a call needs more. }}*/
       UINT        m_nMinPrintf;
       // ---------------------------------------------------------------------------------
       /*{{|method_: `TZString( void )` | desc_: An empty string. }}*/
       TZString(void);
       /*{{|method_: `TZString( LPSTR p )` | desc_: A string initialised with a copy of **p**. }}*/
       TZString(LPSTR);
       /*{{|method_: `TZString( UINT cb )` | desc_: An empty string with **cb** bytes already reserved. }}*/
       TZString(UINT);
       /*{{|method_: `~TZString( void )` | desc_: Frees the buffer. }}*/
       ~TZString(void);
       // ---------------------------------------------------------------------------------
       /*{{|method_: `void _reset_( void )` | desc_: Empties the text (the buffer is kept). }}*/
       void _reset_(void);
       /*{{|method_: `void _grow_cb_( UINT cb )` | desc_: Makes the buffer at least **cb** bytes, keeping the
          text. }}*/
       void _grow_cb_(UINT cb);
       // ---------------------------------------------------------------------------------
       /*{{|method_: `void Add_cp850_to_html( LPSTR pStr, DWORD dwFlags = 0 )`
          | desc_: Appends **pStr**, a code page 850 (OEM) text, as HTML: the characters above 127 become
            their HTML entities and the markup characters are escaped.
          | flags: bits of **dwFlags**:
            - `0x01` a line end (CR, LF or CRLF) becomes `<br>`
            - `0x02` the second of two consecutive spaces becomes `&nbsp;`
            - `0x04` the text is converted to upper case
            - `0x10` without 0x01, CRLF and LF are written as a single CR }}*/
       void Add_cp850_to_html( LPSTR pStr , DWORD dwFlags = 0); // 1 CRLF2BR | 2 sp+sp = sp+&nbsp;
       /*{{|method_: `void Add_cp437_to_html( LPSTR pStr, DWORD dwFlags = 0 )` | desc_: Same for a code page
          437 text. }}*/
       void Add_cp437_to_html( LPSTR pStr , DWORD dwFlags = 0); // 1 CRLF2BR | 2 sp+sp = sp+&nbsp;
       /*{{|method_: `void Add_cp1252_to_html( LPSTR pStr, DWORD dwFlags = 0 )` | desc_: Same for a Windows-1252
          (ANSI) text. }}*/
       void Add_cp1252_to_html( LPSTR pStr , DWORD dwFlags = 0); // 1 CRLF2BR | 2 sp+sp = sp+&nbsp;
       /*{{|method_: `void Add_to_xml( LPSTR pStr )` | desc_: Appends the text with the five XML escapes
          (`&amp;` `&quot;` `&lt;` `&gt;` `&#39;`); other bytes go as they are. }}*/
       void Add_to_xml( LPSTR pStr );
       /*{{|method_: `void Add_to_sql( LPSTR pStr )` | desc_: Appends the zero-terminated text escaped for a
          SQL string literal, without quotes. }}*/
	    void Add_to_sql(LPSTR pStr);
       /*{{|method_: `void Add_to_sql_bin( LPBYTE p, DWORD cb )` | desc_: Appends **cb** bytes escaped for a
          SQL binary literal, without quotes. }}*/
       void Add_to_sql_bin(LPBYTE p , DWORD cb );
       /*{{|method_: `void Add_to_sql_q( LPSTR pStr )` | desc_: Add_to_sql() between quotes. }}*/
       void Add_to_sql_q(LPSTR pStr);
       /*{{|method_: `void Add_to_sql_bin_q( LPBYTE p, DWORD cb )` | desc_: Add_to_sql_bin() between quotes. }}*/
       void Add_to_sql_bin_q(LPBYTE p, DWORD cb);
       /*{{|method_: `void Add_to_json( LPSTR pStr, int cb = -1 )` | desc_: Appends **cb** bytes (-1: up to the
          terminator) as the body of a JSON string: the control characters and the quote and backslash with
          their escapes, and every byte outside 32-127 as `\uXXXX` through the ANSI code page. The quotes
          around the string are the caller's. }}*/
       void Add_to_json( LPSTR pStr , int cb = -1);
       /*{{|method_: `void Add( LPSTR pStr )` | desc_: Appends a zero-terminated string (nothing for 0). }}*/
       void Add( LPSTR pStr );
       /*{{|method_: `DWORD AddStrCb( LPSTR pStr, DWORD cb, DWORD offset, DWORD bytes_to_write, DWORD flags )`
          | desc_: Appends a slice of **pStr** (**cb** bytes long): from **offset**, at most **bytes_to_write**
            bytes, stopping at a zero byte. With **flags** bit 0 the bytes are converted from Windows-1252 to
            UTF-8 on the way. Returns the offset reached, so that the next call can go on from there. }}*/
       DWORD AddStrCb( LPSTR pStr ,  DWORD cb  , DWORD offset , DWORD  bytes_to_write , DWORD flags );
       /*{{|method_: `void Add_With_Safe_Map( BYTE map[256], LPSTR pStr )` | desc_: Appends only the bytes of
          **pStr** whose entry in **map** is not zero: a filter by byte value. }}*/
       void Add_With_Safe_Map( BYTE map[256], LPSTR pStr );
       /*{{|method_: `void Add_RTrim( LPSTR pStr )` | desc_: Appends the string without its trailing spaces. }}*/
       void Add_RTrim( LPSTR pStr );
       /*{{|method_: `void Add_LTrim( LPSTR pStr )` | desc_: Appends the string without its leading spaces. }}*/
       void Add_LTrim( LPSTR pStr );
       /*{{|method_: `void Add_AllTrim( LPSTR pStr )` | desc_: Appends the string without leading or trailing
          spaces. }}*/
       void Add_AllTrim( LPSTR pStr );
       /*{{|method_: `void AddW( LPWSTR pWide )` | desc_: Appends a wide string converted to the ANSI code
          page. }}*/
       void AddW( LPWSTR pWide );
       /*{{|method_: `void AddChar( char ch )` | desc_: Appends one byte (a zero byte is ignored). }}*/
       void AddChar( char ch );
       /*{{|method_: `void AddChar_1252_to_utf8( char ch )` | desc_: Appends one Windows-1252 character as
          UTF-8 (one to three bytes; the five undefined 1252 codes become a space). }}*/
       void AddChar_1252_to_utf8( char ch );
       /*{{|method_: `void str_1252_to_svc_utf8_cell( LPSTR p, DWORD cb, DWORD flags )`
          | desc_: Appends **cb** bytes of Windows-1252 text as one cell of a separated-values file (CSV) in
            UTF-8: the cell is quoted when it holds a quote, a comma, or a tab or line end, inner quotes are
            doubled, and control characters become spaces.
          | flags: bits of **flags**:
            - `0x0001` drop the leading blanks and line ends of the cell
            - `0x0002` drop its trailing blanks
            - `0x0008` with 0x0100, a value that looks like a number also gets a leading apostrophe
            - `0x0100` a value that looks like a number (digits, sign, dot, slash, an exponent) is quoted, so
              that a spreadsheet keeps it as text
            - `0x0200` no UTF-8 conversion, the bytes go as they are
            - `0x0400` tabs and line ends are folded into one space instead of kept (and do not force quotes)
            - `0x0800` double quotes are written as single quotes
            - `0x4000` / `0x8000` / `0xC000` cut the cell to 400 / 800 / 1200 bytes }}*/
       void str_1252_to_svc_utf8_cell( LPSTR p, DWORD cb, DWORD flags );
       // ULONG TZString::AddChar_a2xmlutf8( char ch )
       // ---------------------------------------------------------------------------------
       /*{{|method_: `void TrimZ( BOOL bRealloc = FALSE )` | desc_: Sets the length from the first zero byte
          (for text written into the buffer by hand) and, with **bRealloc**, shrinks the buffer to fit. }}*/
       void  TrimZ(BOOL bRealloc = FALSE);
       /*{{|method_: `void RTrim( void )` | desc_: Removes the trailing spaces of the text. }}*/
	   void  RTrim(void);
       /*{{|method_: `LPSTR Detach( UINT* pcb = 0, UINT* pcs = 0 )` | desc_: Hands the buffer over to the
          caller (free it with _xfree) with its length in **pcb** and its size in **pcs**; the object is left
          empty. }}*/
       LPSTR Detach(UINT* pcb = 0 , UINT* pcs = 0);
       //LPSTR Detach_mb2mb(UINT nAcpFrom , UINT nAcpTo , UINT flags , DWORD & cb_out);
       /*{{|method_: `LPSTR Detach_mb2mb( UINT nAcpFrom, UINT nAcpTo, DWORD* pcb_out, DWORD flags1, DWORD flags2 )`
          | desc_: Detach() with a code page conversion: the text is converted from **nAcpFrom** to **nAcpTo**
            (through UTF-16, **flags1** and **flags2** being the flags of MultiByteToWideChar and
            WideCharToMultiByte) and the new buffer returned, its length in **pcb_out**. Equal code pages
            return the buffer as it is. }}*/
       LPSTR Detach_mb2mb(UINT nAcpFrom , UINT nAcpTo ,DWORD  * pcb_out , DWORD flags1, DWORD flags2);
       /*{{|method_: `LPSTR GetBuffer( void )` | desc_: The text (0 before the first append). }}*/
       LPSTR GetBuffer(void);
       // ---------------------------------------------------------------------------------
       /*{{|method_: `void operator+=( LPSTR pStr )` | desc_: Add(). }}*/
       void operator+=( LPSTR  pStr );
       /*{{|method_: `void operator+=( LPWSTR pWide )` | desc_: AddW(). }}*/
       void operator+=( LPWSTR pWide );
       /*{{|method_: `LPSTR _pt_next_( UINT nSize )` | desc_: Room for **nSize** bytes at the end of the text,
          to be written by the caller, who then adds what was written to m_nLen. }}*/
       LPSTR _pt_next_( UINT nSize );
       /*{{|method_: `void printf( LPSTR pt, ... )` | desc_: Appends the printf-style formatting of the
          arguments, whatever its length. }}*/
       void printf(LPSTR pt , ... );
       /*{{|method_: `LPSTR _pt_( void )` | desc_: The buffer, allocated if needed. }}*/
       LPSTR _pt_(void);
       /*{{|method_: `CHAR LastChar( void )` | desc_: The last byte of the text, 0 when empty. }}*/
       CHAR LastChar(void);
       /*{{|method_: `ULONG len( void )` | desc_: Length of the text. }}*/
       ULONG len( void );
       /*{{|method_: `ULONG dump( LPSTR pOut, ULONG cbMax = -1 )` | desc_: Copies up to **cbMax** bytes of the
          text into **pOut** (no terminator) and returns the bytes copied. }}*/
       ULONG dump( LPSTR pOut , ULONG cbMax = -1);
       // ---------------------------------------------------------------------------------
};
/*{{end-cpp-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-class}}*/
/*{{cpp-class_: xstream_t
   | parent: {{ilink: <cpp-class T_ot4xb_base> T_ot4xb_base}}
   | category: c-api/classes , c-api/byte-stream
   | desc: A growable byte buffer, the base of {{ilink: <cpp-class TByteStream> TByteStream}}: a block of
     **m_nLen** valid bytes inside **m_nBuffSize** allocated ones, grown in multiples of **m_nBlockSize**. The
     primitives reserve room at the end (or at an offset) and let the caller write there, and the append_*
     family fills it with bytes, integers, UTF-8 conversions and the decoded form of base64, quoted-printable
     and uuencoded text. The memory functions are virtual so that a derived class can take the bytes from
     another heap; here they use the ot4xb heap.
     | _kw_: xstream_t, Class }}*/
class OT4XB_API xstream_t  : public T_ot4xb_base // the ot4cpp xstream_t class
{
   public:
       /*{{|member_: `void* m_pBuffer` | desc_: The bytes, 0 until something is reserved. }}*/
       void*    m_pBuffer;
       /*{{|member_: `DWORD m_nBuffSize` | desc_: Bytes allocated. }}*/
       DWORD    m_nBuffSize;
       /*{{|member_: `DWORD m_nLen` | desc_: Valid bytes (the content length). }}*/
       DWORD    m_nLen;
       /*{{|member_: `DWORD m_nBlockSize` | desc_: Growth granularity (1024 by default; 2 or less means
          exact sizes). }}*/
       DWORD    m_nBlockSize;
       // ---------------------------------------------------------------------------------
       /*{{|method_: `virtual void _init_heap_( void )` | desc_: Hook for a derived class with its own heap;
          nothing here. }}*/
       virtual void _init_heap_( void );
       /*{{|method_: `virtual void _release_heap_( void )` | desc_: The matching hook at destruction; nothing
          here. }}*/
       virtual void _release_heap_( void );
       /*{{|method_: `virtual void* _alloc_memory_( UINT n )` | desc_: _xgrab( n ). }}*/
       virtual void* _alloc_memory_( UINT n );
       /*{{|method_: `virtual void _free_memory_( void* p )` | desc_: _xfree( p ). }}*/
       virtual void  _free_memory_( void* p );
      // ---------------------------------------------------------------------------------
      /*{{|method_: `xstream_t( DWORD nInitialSize = 0, DWORD nBlockSize = 1024 )` | desc_: An empty stream,
         with **nInitialSize** bytes already allocated when given. }}*/
      xstream_t( DWORD nInitialSize = 0 , DWORD nBlockSize = 1024 );
      /*{{|method_: `~xstream_t()` | desc_: Frees the buffer. }}*/
      ~xstream_t();
      // ---------------------------------------------------------------------------------
      /*{{|method_: `BOOL _grow_( DWORD nNewSize )` | desc_: Makes the buffer at least **nNewSize** bytes
         (rounded up to the block size), keeping the content. FALSE for a negative size. }}*/
      BOOL   _grow_( DWORD nNewSize );
      /*{{|method_: `void* _reserve_bytes_( DWORD nBytes )` | desc_: Room for **nBytes** after the content:
         the address where the caller writes them, followed by _skip_bytes_() to count them. 0 for a size
         below 1. }}*/
      void*  _reserve_bytes_( DWORD nBytes );
      /*{{|method_: `void* _reserve_bytes_( DWORD offset, DWORD nBytes )` | desc_: Same at **offset** (within
         the content): the buffer can hold offset + nBytes and the address of offset is returned; the length
         does not change. }}*/
      void*  _reserve_bytes_( DWORD offset , DWORD nBytes );
      /*{{|method_: `BOOL _skip_bytes_( DWORD nBytes )` | desc_: Adds **nBytes** to the content length
         (reserving them first). }}*/
      BOOL   _skip_bytes_( DWORD nBytes );
      /*{{|method_: `void* _offset_ptr_( DWORD offset = 0, DWORD cb = 0 )` | desc_: A pointer into the content
         after checking that offset + cb bytes fit inside it; 0 otherwise. }}*/
      void*  _offset_ptr_( DWORD offset = 0 , DWORD cb = 0 );
      /*{{|method_: `DWORD _offset_len_( DWORD offset = 0 )` | desc_: Content bytes from **offset** to the end. }}*/
      DWORD  _offset_len_( DWORD offset = 0);
      /*{{|method_: `DWORD _truncate_buffer_( DWORD len = 0 )` | desc_: Cuts the content length down to
         **len** (it can only shrink) and returns the new length; the memory stays allocated. }}*/
      DWORD  _truncate_buffer_( DWORD len = 0);
      // ---------------------------------------------------------------------------------
      /*{{|method_: `BOOL append_buffer( void* p, DWORD cb )` | desc_: Appends **cb** bytes ((DWORD) -1: up to
         the zero terminator). }}*/
      BOOL append_buffer(void* p , DWORD cb );
      /*{{|method_: `BOOL append_BYTE( BYTE n )` | desc_: Appends one byte. }}*/
      BOOL append_BYTE(BYTE n);
      /*{{|method_: `BOOL append_WORD( WORD n )` | desc_: Appends two bytes, little endian. }}*/
      BOOL append_WORD(WORD n);
      /*{{|method_: `BOOL append_DWORD( DWORD n )` | desc_: Appends four bytes, little endian. }}*/
      BOOL append_DWORD(DWORD n);
      // ---------------------------------------------------------------------------------
      /*{{|method_: `BOOL append_ansi_to_utf8( LPSTR pa, int cb = -1 )` | desc_: Appends ANSI text (the active
         code page) converted to UTF-8. }}*/
      BOOL append_ansi_to_utf8(LPSTR pa , int cb = -1);
      /*{{|method_: `BOOL append_ansi_to_xform_utf8( LPSTR p, int cb = -1, int nLevel = 4 )` | desc_: Appends
         the text transformed byte by byte from Windows-1252 to URL (percent) encoded UTF-8; **nLevel**
         selects how many characters are left unencoded. }}*/
      BOOL append_ansi_to_xform_utf8(LPSTR p , int cb = -1 , int nLevel = 4);
      // ---------------------------------------------------------------------------------
      /*{{|method_: `BOOL append_decode_base64( LPSTR p, int cb = -1 )` | desc_: Appends the bytes decoded
         from base64 text. FALSE for empty or invalid input. }}*/
      BOOL append_decode_base64(LPSTR p , int cb = -1);
      /*{{|method_: `BOOL append_decode_qp( LPSTR p, int cb = -1, DWORD nFlags = 0 )` | desc_: Appends the
         bytes decoded from quoted-printable text; **nFlags** bit 0 handles the dot-stuffed lines of a mail
         transfer, bit 1 adds a CRLF at the end. }}*/
      BOOL append_decode_qp(LPSTR p , int cb = -1 , DWORD nFlags = 0); // flags: 1 dot , 2 add CRLF
      /*{{|method_: `BOOL append_decode_uu( LPSTR p, int cb = -1 )` | desc_: Appends the bytes decoded from
         uuencoded text. }}*/
      BOOL append_decode_uu(LPSTR p , int cb = -1);
      //BOOL append_encode_b(LPSTR p , int cb = -1);
      //BOOL append_encode_base64(LPSTR p , int cb = -1);
      //BOOL append_encode_q(LPSTR p , int cb = -1);
      //BOOL append_encode_qp(LPSTR p , int cb = -1);
      //BOOL append_encode_uu(LPSTR p , int cb = -1);
      //BOOL append_escape_xml(LPSTR p , int cb = -1);
      /*{{|method_: `BOOL append_encode_ot4xb( LPSTR p, int cb = -1, DWORD nFlags = 0 )`
         | desc_: Appends the text in the ot4xb escape notation, a C-like backslash notation that keeps
           XML-unsafe bytes out: `\0 \a \b \f \n \r \t \v \\` for the control characters and the
           backslash, `\x26 \x3C \x3E` for `& < >`, and `\xHH` for any other byte outside 32-127.
           **nFlags**: bit 0 also escapes `%` (as `\x25`), bit 2 (0x04) the double quote (as `\q`), and
           bit 3 (0x08) writes `\s` for a space that is the last byte or is followed by another space, so
           that runs of spaces survive. }}*/
	  BOOL append_encode_ot4xb(LPSTR p, int cb = -1, DWORD nFlags = 0);
      // ---------------------------------------------------------------------------------
      /*{{|method_: `void ansi_ZTrim( void )` | desc_: Shortens the content while its last byte is zero. }}*/
      void ansi_ZTrim(void);
      /*{{|method_: `void ansi_ZSafe( void )` | desc_: Makes the content safe to read as a C string: when it
         is empty or its last byte is not zero, a zero byte is appended and counted. }}*/
      void ansi_ZSafe(void);
      // ---------------------------------------------------------------------------------
      /*{{|method_: `void* Detach( UINT* pcb = 0, UINT* pcs = 0 )` | desc_: Hands the buffer over to the caller
         (length in **pcb**, allocated size in **pcs**) and leaves the stream empty. }}*/
      void* Detach(UINT* pcb = 0 , UINT* pcs = 0);
};
/*{{end-cpp-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-class}}*/
/*{{cpp-class_: TByteStream
   | parent: {{ilink: <cpp-class xstream_t> xstream_t}}
   | category: c-api/classes , c-api/byte-stream
   | desc: The byte stream of ot4xb: an {{ilink: <cpp-class xstream_t> xstream_t}} with byte-typed
     accessors, an Add() that keeps a zero byte after the content, and a COM IStream view for the APIs that
     want one. The same object is reachable from C through the `TByteStream_*` functions
     ({{ilink: <c-function TByteStream_new> TByteStream_new}}, {{ilink: <c-function TByteStream_Add> TByteStream_Add}},
     ...), one per method. The nested IByteStream class is the IStream implementation, private to
     get_IStream().
     | _kw_: TByteStream, Class }}*/
class OT4XB_API TByteStream : public xstream_t
{
       // ---------------------------------------------------------------------------------
       class IByteStream : public ::IStream
       {
          public:
          // ---------------------------------------------------------------------------------
          // IUnknown interface
          // ---------------------------------------------------------------------------------
          virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void ** ppvObject);
          virtual ULONG   STDMETHODCALLTYPE AddRef(void);
          virtual ULONG   STDMETHODCALLTYPE Release(void);
          // ---------------------------------------------------------------------------------
          // ISequentialStream Interface
          // ---------------------------------------------------------------------------------
          virtual HRESULT STDMETHODCALLTYPE Read(void* pv, ULONG cb, ULONG* pcbRead);
          virtual HRESULT STDMETHODCALLTYPE Write(void const* pv, ULONG cb, ULONG* pcbWritten);
          // ---------------------------------------------------------------------------------
          // IStream Interface
          // ---------------------------------------------------------------------------------
          virtual HRESULT STDMETHODCALLTYPE SetSize(ULARGE_INTEGER);
          virtual HRESULT STDMETHODCALLTYPE CopyTo(IStream*, ULARGE_INTEGER, ULARGE_INTEGER*,ULARGE_INTEGER*);
          virtual HRESULT STDMETHODCALLTYPE Commit(DWORD);
          virtual HRESULT STDMETHODCALLTYPE Revert(void);
          virtual HRESULT STDMETHODCALLTYPE LockRegion(ULARGE_INTEGER, ULARGE_INTEGER, DWORD);
          virtual HRESULT STDMETHODCALLTYPE UnlockRegion(ULARGE_INTEGER, ULARGE_INTEGER, DWORD);
          virtual HRESULT STDMETHODCALLTYPE Clone(IStream **);
          virtual HRESULT STDMETHODCALLTYPE Seek(LARGE_INTEGER liDistanceToMove, DWORD dwOrigin,ULARGE_INTEGER* lpNewPos);
          virtual HRESULT STDMETHODCALLTYPE Stat(STATSTG* pStatstg, DWORD grfStatFlag);
          // ---------------------------------------------------------------------------------
          TByteStream* m_xstream;
          LONG         m_refcount;
          DWORD        m_pos;
          BOOL         m_destroy_on_release;
          // ---------------------------------------------------------------------------------
          IByteStream(TByteStream* xstream){ m_xstream = xstream; m_refcount = 1; m_pos = 0; m_destroy_on_release = 0;};
          ~IByteStream(){;};
          // ---------------------------------------------------------------------------------
       };
       // ---------------------------------------------------------------------------------
   public:
       // ---------------------------------------------------------------------------------
       /*{{|method_: `TByteStream( DWORD nInitialSize = 0, DWORD nBlockSize = 1024 )` | desc_: An empty stream
          (see xstream_t). }}*/
       TByteStream(DWORD nInitialSize = 0 , DWORD nBlockSize = 1024 ):xstream_t(nInitialSize,nBlockSize){;};
       // ---------------------------------------------------------------------------------
       /*{{|method_: `void _grow_cb_( UINT cb )` | desc_: _grow_( cb ), without a result. }}*/
       void _grow_cb_(UINT cb);
       // ---------------------------------------------------------------------------------
       /*{{|method_: `LPBYTE Detach( UINT* pcb = 0, UINT* pcs = 0 )` | desc_: xstream_t::Detach() as bytes. }}*/
       LPBYTE Detach(UINT* pcb = 0 , UINT* pcs = 0);
       /*{{|method_: `LPBYTE GetBuffer( void )` | desc_: The content. }}*/
       LPBYTE GetBuffer(void);
       /*{{|method_: `ULONG len( void )` | desc_: The content length. }}*/
       ULONG  len( void );
       // ---------------------------------------------------------------------------------
       /*{{|method_: `BOOL Add( LPBYTE p, UINT cb = (UINT) -1 )` | desc_: Appends **cb** bytes (-1: up to the
          zero terminator) and writes a zero byte after them, not counted in the length, so the content stays
          readable as a C string. FALSE for a null pointer or nothing to add. }}*/
       BOOL Add( LPBYTE p , UINT cb = (UINT) -1 );
       // ---------------------------------------------------------------------------------
       /*{{|method_: `IStream* get_IStream( void )` | desc_: A new COM IStream view over the content: Read,
          Write, Seek and SetSize work with 32-bit sizes and writing past the end extends the content; Stat
          only reports the size; the other members return E_NOTIMPL. The TByteStream must outlive the view,
          and releasing the view never destroys it. }}*/
       IStream* get_IStream(void);
       // ---------------------------------------------------------------------------------
};
/*{{end-cpp-class}}*/
// -----------------------------------------------------------------------------------------------------------------
BEGIN_EXTERN_C
OT4XB_API    TByteStream*        __cdecl TByteStream_new( DWORD nInitialSize , DWORD nBlockSize );
OT4XB_API    void                __cdecl TByteStream_destroy(TByteStream* pbs);
OT4XB_API    BOOL                __cdecl TByteStream__grow_( TByteStream* pbs ,  DWORD nNewSize );
OT4XB_API    void*               __cdecl TByteStream__reserve_bytes_( TByteStream* pbs ,  DWORD nBytes );
OT4XB_API    void*               __cdecl TByteStream__reserve_bytes_at( TByteStream* pbs ,  DWORD offset , DWORD nBytes );
OT4XB_API    BOOL                __cdecl TByteStream__skip_bytes_( TByteStream* pbs ,  DWORD nBytes );
OT4XB_API    void*               __cdecl TByteStream__offset_ptr_( TByteStream* pbs ,  DWORD offset , DWORD cb );
OT4XB_API    DWORD               __cdecl TByteStream__offset_len_( TByteStream* pbs ,  DWORD offset );
OT4XB_API    DWORD               __cdecl TByteStream__truncate_buffer_( TByteStream* pbs ,  DWORD len );
OT4XB_API    BOOL                __cdecl TByteStream_append_buffer( TByteStream* pbs , void* p , DWORD cb );
OT4XB_API    BOOL                __cdecl TByteStream_append_BYTE( TByteStream* pbs , BYTE n);
OT4XB_API    BOOL                __cdecl TByteStream_append_WORD( TByteStream* pbs , WORD n);
OT4XB_API    BOOL                __cdecl TByteStream_append_DWORD( TByteStream* pbs , DWORD n);
OT4XB_API    BOOL                __cdecl TByteStream_append_ansi_to_utf8( TByteStream* pbs , LPSTR pa , int cb );
OT4XB_API    BOOL                __cdecl TByteStream_append_ansi_to_xform_utf8( TByteStream* pbs , LPSTR p , int cb , int nLevel );
OT4XB_API    BOOL                __cdecl TByteStream_append_decode_base64( TByteStream* pbs , LPSTR p , int cb );
OT4XB_API    BOOL                __cdecl TByteStream_append_decode_qp( TByteStream* pbs , LPSTR p , int cb , DWORD nFlags ); // flags: 1 dot , 2 add CRLF
OT4XB_API    BOOL                __cdecl TByteStream_append_decode_uu( TByteStream* pbs , LPSTR p , int cb );
//OT4XB_API  BOOL                __cdecl TByteStream_append_encode_b( TByteStream* pbs , LPSTR p , int cb );
//OT4XB_API  BOOL                __cdecl TByteStream_append_encode_base64( TByteStream* pbs , LPSTR p , int cb );
//OT4XB_API  BOOL                __cdecl TByteStream_append_encode_q( TByteStream* pbs , LPSTR p , int cb );
//OT4XB_API  BOOL                __cdecl TByteStream_append_encode_qp( TByteStream* pbs , LPSTR p , int cb );
//OT4XB_API  BOOL                __cdecl TByteStream_append_encode_uu( TByteStream* pbs , LPSTR p , int cb );
//OT4XB_API  BOOL                __cdecl TByteStream_append_escape_xml( TByteStream* pbs , LPSTR p , int cb );
OT4XB_API    void                __cdecl TByteStream_ansi_ZTrim( TByteStream* pbs );
OT4XB_API    void                __cdecl TByteStream_ansi_ZSafe( TByteStream* pbs );
OT4XB_API    void                __cdecl TByteStream__grow_cb_( TByteStream* pbs , UINT cb);
OT4XB_API    LPBYTE              __cdecl TByteStream_Detach( TByteStream* pbs , UINT* pcb , UINT* pcs );
OT4XB_API    LPBYTE              __cdecl TByteStream_GetBuffer( TByteStream* pbs );
OT4XB_API    ULONG               __cdecl TByteStream_len( TByteStream* pbs  );
OT4XB_API    BOOL                __cdecl TByteStream_Add( TByteStream* pbs ,  LPBYTE p , UINT cb );
OT4XB_API    IStream*            __cdecl TByteStream_get_IStream( TByteStream* pbs);
END_EXTERN_C
// -----------------------------------------------------------------------------------------------------------------
#endif // __cplusplus
//----------------------------------------------------------------------------------------------------------------------
#endif