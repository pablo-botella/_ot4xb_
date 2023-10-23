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
class OT4XB_API TZString : public T_ot4xb_base
{
   public:
       LPSTR       m_pBuffer;
       UINT        m_nBuffSize;
       UINT        m_nLen;
       UINT        m_nMinPrintf;
       // ---------------------------------------------------------------------------------
       TZString(void);
       TZString(LPSTR);
       TZString(UINT);
       ~TZString(void);
       // ---------------------------------------------------------------------------------
       void _reset_(void);
       void _grow_cb_(UINT cb);
       // ---------------------------------------------------------------------------------
       void Add_cp850_to_html( LPSTR pStr , DWORD dwFlags = 0); // 1 CRLF2BR | 2 sp+sp = sp+&nbsp;
       void Add_cp437_to_html( LPSTR pStr , DWORD dwFlags = 0); // 1 CRLF2BR | 2 sp+sp = sp+&nbsp;
       void Add_cp1252_to_html( LPSTR pStr , DWORD dwFlags = 0); // 1 CRLF2BR | 2 sp+sp = sp+&nbsp;
       void Add_to_xml( LPSTR pStr );
	    void Add_to_sql(LPSTR pStr);
       void Add_to_sql_bin(LPBYTE p , DWORD cb );
       void Add_to_sql_q(LPSTR pStr);
       void Add_to_sql_bin_q(LPBYTE p, DWORD cb);
       void Add_to_json( LPSTR pStr , int cb = -1);
       void Add( LPSTR pStr );
       DWORD AddStrCb( LPSTR pStr ,  DWORD cb  , DWORD offset , DWORD  bytes_to_write , DWORD flags );
       void Add_RTrim( LPSTR pStr );
       void Add_LTrim( LPSTR pStr );
       void Add_AllTrim( LPSTR pStr );
       void AddW( LPWSTR pWide );
       void AddChar( char ch );
       void AddChar_1252_to_utf8( char ch );
       void str_1252_to_svc_utf8_cell( LPSTR p, DWORD cb, DWORD flags );
       // ULONG TZString::AddChar_a2xmlutf8( char ch )
       // ---------------------------------------------------------------------------------
       void  TrimZ(BOOL bRealloc = FALSE);
	   void  RTrim(void);
       LPSTR Detach(UINT* pcb = 0 , UINT* pcs = 0);
       //LPSTR Detach_mb2mb(UINT nAcpFrom , UINT nAcpTo , UINT flags , DWORD & cb_out);
       LPSTR Detach_mb2mb(UINT nAcpFrom , UINT nAcpTo ,DWORD  * pcb_out , DWORD flags1, DWORD flags2);
       LPSTR GetBuffer(void);
       // ---------------------------------------------------------------------------------
       void operator+=( LPSTR  pStr );
       void operator+=( LPWSTR pWide );
       LPSTR _pt_next_( UINT nSize );
       void printf(LPSTR pt , ... );
       LPSTR _pt_(void);
       CHAR LastChar(void);
       ULONG len( void );
       ULONG dump( LPSTR pOut , ULONG cbMax = -1);
       // ---------------------------------------------------------------------------------
};
// -----------------------------------------------------------------------------------------------------------------
class OT4XB_API xstream_t  : public T_ot4xb_base // the ot4cpp xstream_t class
{
   public:
       void*    m_pBuffer;
       DWORD    m_nBuffSize;
       DWORD    m_nLen;
       DWORD    m_nBlockSize;
       // ---------------------------------------------------------------------------------
       virtual void _init_heap_( void );
       virtual void _release_heap_( void );
       virtual void* _alloc_memory_( UINT n );
       virtual void  _free_memory_( void* p );
      // ---------------------------------------------------------------------------------
      xstream_t( DWORD nInitialSize = 0 , DWORD nBlockSize = 1024 );
      ~xstream_t();
      // ---------------------------------------------------------------------------------
      BOOL   _grow_( DWORD nNewSize );
      void*  _reserve_bytes_( DWORD nBytes );
      void*  _reserve_bytes_( DWORD offset , DWORD nBytes );
      BOOL   _skip_bytes_( DWORD nBytes );
      void*  _offset_ptr_( DWORD offset = 0 , DWORD cb = 0 );
      DWORD  _offset_len_( DWORD offset = 0);
      DWORD  _truncate_buffer_( DWORD len = 0);
      // ---------------------------------------------------------------------------------
      BOOL append_buffer(void* p , DWORD cb );
      BOOL append_BYTE(BYTE n);
      BOOL append_WORD(WORD n);
      BOOL append_DWORD(DWORD n);
      // ---------------------------------------------------------------------------------
      BOOL append_ansi_to_utf8(LPSTR pa , int cb = -1);
      BOOL append_ansi_to_xform_utf8(LPSTR p , int cb = -1 , int nLevel = 4);
      // ---------------------------------------------------------------------------------
      BOOL append_decode_base64(LPSTR p , int cb = -1);
      BOOL append_decode_qp(LPSTR p , int cb = -1 , DWORD nFlags = 0); // flags: 1 dot , 2 add CRLF
      BOOL append_decode_uu(LPSTR p , int cb = -1);
      //BOOL append_encode_b(LPSTR p , int cb = -1);
      //BOOL append_encode_base64(LPSTR p , int cb = -1);
      //BOOL append_encode_q(LPSTR p , int cb = -1);
      //BOOL append_encode_qp(LPSTR p , int cb = -1);
      //BOOL append_encode_uu(LPSTR p , int cb = -1);
      //BOOL append_escape_xml(LPSTR p , int cb = -1);
	  BOOL append_encode_ot4xb(LPSTR p, int cb = -1, DWORD nFlags = 0);
      // ---------------------------------------------------------------------------------
      void ansi_ZTrim(void);
      void ansi_ZSafe(void);
      // ---------------------------------------------------------------------------------
      void* Detach(UINT* pcb = 0 , UINT* pcs = 0);
};
// -----------------------------------------------------------------------------------------------------------------
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
       TByteStream(DWORD nInitialSize = 0 , DWORD nBlockSize = 1024 ):xstream_t(nInitialSize,nBlockSize){;};
       // ---------------------------------------------------------------------------------
       void _grow_cb_(UINT cb);
       // ---------------------------------------------------------------------------------
       LPBYTE Detach(UINT* pcb = 0 , UINT* pcs = 0);
       LPBYTE GetBuffer(void);
       ULONG  len( void );
       // ---------------------------------------------------------------------------------
       BOOL Add( LPBYTE p , UINT cb = (UINT) -1 );
       // ---------------------------------------------------------------------------------
       IStream* get_IStream(void);
       // ---------------------------------------------------------------------------------
};
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