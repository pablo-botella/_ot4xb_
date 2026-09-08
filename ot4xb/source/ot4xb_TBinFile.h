//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#ifndef _API_cpp_TBinFile_h_
#define _API_cpp_TBinFile_h_
//----------------------------------------------------------------------------------------------------------------------
#ifdef __cplusplus
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-class}}*/
/*{{cpp-class_: TBinFile
   | parent: {{ilink: <cpp-class T_ot4xb_base> T_ot4xb_base}}
   | category: c-api/classes , filesystem
   | desc: A Win32 file handle with a 64-bit file pointer and a read buffer: opens or creates the file with
     CreateFile options, moves the pointer with LONGLONG offsets, and reads lines or MIME header blocks through
     the buffer without copying them. It is the engine of the Xbase++ class
     {{ilink: <class TBinFile> TBinFile}}. Every member is public: the buffer bookkeeping is meant to be used
     by the caller when the line readers are not enough.
   | note: The buffer holds one window of the file: **m_qlBuffStart** is the file offset of its first valid
     byte, the valid bytes start at **m_dwBuffShift** inside the allocation and are **m_dwBuffLen** long.
     Pointers returned by the readers point inside this window and stay valid only until the next buffer
     operation; the data is not zero-terminated.
   | note: The destructor frees the buffer but does not close the handle: call Close(), or DetachHandle() to
     keep it.
   | _kw_: TBinFile, Class }}*/
class OT4XB_API TBinFile : public T_ot4xb_base
{
   public:
       /*{{|member_: `HANDLE m_hFile` | desc_: The Win32 handle; INVALID_HANDLE_VALUE when closed. }}*/
       HANDLE              m_hFile;
       /*{{|member_: `DWORD m_dwLastError` | desc_: Win32 error of the last file pointer operation, 0 when it
          succeeded. }}*/
       DWORD               m_dwLastError;
       // ------------
       /*{{|member_: `DWORD m_dwAttributes` | desc_: Kept at 0 by the class; free for the owner. }}*/
       DWORD               m_dwAttributes;
       /*{{|member_: `DWORD m_dwReserved` | desc_: Kept at 0 by the class; free for the owner. }}*/
       DWORD               m_dwReserved;
       // ------------
       /*{{|member_: `LONGLONG m_qlPos` | desc_: The file pointer as last read or set through the class, -1
          after a failed move. }}*/
       LONGLONG            m_qlPos;       // CURRENT FILE POINTER POSITION
       /*{{|member_: `LONGLONG m_qlSize` | desc_: Kept at 0 by the class; free for the owner. }}*/
       LONGLONG            m_qlSize;      // SIZE OF THE FILE
       /*{{|member_: `LONGLONG m_qlBuffStart` | desc_: File offset of the first valid byte of the buffer. }}*/
       LONGLONG            m_qlBuffStart; // CURRENT BUFFER POSITION FROM THE BEGIN
       // ------------
       /*{{|member_: `LPBYTE m_pBuffer` | desc_: The read buffer, allocated by ResetBuffer(); 0 until then. }}*/
       LPBYTE              m_pBuffer;
       /*{{|member_: `DWORD m_dwBuffSize` | desc_: Size of the allocation (64 KB unless ResetBuffer( size )
          said otherwise, 64 MB at most). }}*/
       DWORD               m_dwBuffSize;   // Size of the read/write buffer
       // -----------
       /*{{|member_: `DWORD m_dwBuffShift` | desc_: Offset of the first valid byte inside the allocation
          (bytes before it were consumed by SetBaseBuffer()). }}*/
       DWORD               m_dwBuffShift;  // begin of buffer ( for search optimization)
       /*{{|member_: `DWORD m_dwBuffLen` | desc_: Number of valid bytes from m_dwBuffShift on. }}*/
       DWORD               m_dwBuffLen;    // Valid Len of Buffer ( from dwShift )
       // ------------

       // ---------------------------------------------------------------------------------
       /*{{|method_: `TBinFile( void )` | desc_: A closed file, no buffer. }}*/
       TBinFile(void);
       /*{{|method_: `~TBinFile( void )` | desc_: Frees the buffer; the handle is left open. }}*/
       ~TBinFile(void);
       // ------------
       /*{{|method_: `void InitFromHandle( HANDLE hFile )` | desc_: Adopts an open handle: the buffer is
          dropped and the file pointer read. The previous handle is not closed. }}*/
       void InitFromHandle( HANDLE hFile );
       /*{{|method_: `HANDLE DetachHandle( void )` | desc_: Returns the handle, which stays open, and leaves
          the object closed and buffer-less. }}*/
       HANDLE DetachHandle(void);
       // ------------
       /*{{|method_: `void Close( void )` | desc_: Closes the handle when there is one and frees the buffer. }}*/
       void Close(void);
       /*{{|method_: `BOOL Open( LPSTR pFName, DWORD dwAccess = GENERIC_READ | GENERIC_WRITE, DWORD dwShare = 0, BOOL bOpenAlways = FALSE )`
          | desc_: Closes what was open and opens **pFName** with CreateFile, OPEN_EXISTING or OPEN_ALWAYS
            with **bOpenAlways**, no security attributes and no flags. TRUE when the file is open. }}*/
       BOOL Open(LPSTR pFName , DWORD dwAccess = (GENERIC_READ | GENERIC_WRITE) ,
                 DWORD dwShare = 0 , BOOL bOpenAlways = FALSE );
       /*{{|method_: `BOOL Create( LPSTR pFName, DWORD dwAccess = GENERIC_READ | GENERIC_WRITE, DWORD dwShare = 0, LPSECURITY_ATTRIBUTES psa = NULL, DWORD dwCmd = OPEN_ALWAYS, DWORD dwFlags = FILE_ATTRIBUTE_NORMAL, HANDLE hTemp = 0 )`
          | desc_: Closes what was open and calls CreateFile with every parameter as given (dwCmd is the
            creation disposition). TRUE when the file is open. }}*/
       BOOL Create(LPSTR pFName , DWORD dwAccess = (GENERIC_READ | GENERIC_WRITE),
                   DWORD dwShare = 0, LPSECURITY_ATTRIBUTES psa = NULL ,
                   DWORD dwCmd = OPEN_ALWAYS ,DWORD dwFlags = FILE_ATTRIBUTE_NORMAL ,HANDLE hTemp = 0);
       // ------------
       /*{{|method_: `LONGLONG SetFPointer64( LONGLONG ql = 0, DWORD dwFrom = FILE_BEGIN )`
          | desc_: Moves the file pointer **ql** bytes from **dwFrom** (FILE_BEGIN, FILE_CURRENT, FILE_END)
            and returns the new absolute position, kept in m_qlPos. On failure returns -1, leaves the error
            in m_dwLastError and in GetLastError(), and refreshes m_qlPos with the real position. }}*/
       LONGLONG SetFPointer64( LONGLONG ql = 0 , DWORD dwFrom = FILE_BEGIN);
       /*{{|method_: `LONGLONG GetFPointer64( void )` | desc_: The current position (a zero move from
          FILE_CURRENT), -1 on a closed file. }}*/
       LONGLONG GetFPointer64(void);
       // ------------
       /*{{|method_: `BOOL bSkipFPointer32( LONG nSkip = 0, LONG* pSkipped = 0 )`
          | desc_: Moves the pointer **nSkip** bytes from the current position. TRUE when the position is
            known afterwards; **pSkipped**, when given, receives the previous position minus the new one. }}*/
       BOOL bSkipFPointer32( LONG nSkip = 0 , LONG* pSkiped = 0);
       /*{{|method_: `BOOL bSkipFPointer64( LONGLONG nSkip, LONGLONG* pSkipped = 0 )`
          | desc_: The 64-bit form of bSkipFPointer32(). }}*/
       BOOL bSkipFPointer64( LONGLONG nSkip , LONGLONG* pSkipped = 0);
       // ------------
       /*{{|method_: `void ResetBuffer( void )` | desc_: Empties the buffer and anchors it at the current file
          position, keeping its size. }}*/
       void ResetBuffer( void );
       /*{{|method_: `void ResetBuffer( DWORD dwSize )` | desc_: Same, with a buffer of **dwSize** bytes
          (0 means 64 KB, more than 64 MB is cut to 64 MB); the allocation is redone only when the size
          changes. }}*/
       void ResetBuffer( DWORD dwSize );
       /*{{|method_: `BOOL LoadBuffer( BOOL* pbEof )` | desc_: Resets the buffer and fills it from the current
          file position. TRUE when ReadFile succeeded; **pbEof** is set when fewer bytes than the buffer size
          came back. }}*/
       BOOL LoadBuffer( BOOL * pbEof);
       /*{{|method_: `BOOL bValidBufferOffset( void )` | desc_: TRUE when the current file pointer falls
          inside the valid bytes of the buffer. }}*/
       BOOL bValidBufferOffset(void);
       /*{{|method_: `LONGLONG nqBufferStartOffset( void )` | desc_: File offset of the first valid byte, -1
          when the buffer is empty. }}*/
       LONGLONG nqBufferStartOffset(void);
       /*{{|method_: `LONGLONG nqBufferEndOffset( void )` | desc_: File offset one past the last valid byte, -1
          when the buffer is empty. }}*/
       LONGLONG nqBufferEndOffset(void);
       /*{{|method_: `LPBYTE OffsetToBuffer( void )` | desc_: Pointer to the byte at the current file position
          inside the buffer, 0 when it is not buffered. }}*/
       LPBYTE   OffsetToBuffer( void);
       /*{{|method_: `LPBYTE OffsetToBuffer( LONGLONG qlOffSet )` | desc_: Pointer to the byte at file offset
          **qlOffSet** inside the buffer, 0 when it is not buffered. }}*/
       LPBYTE   OffsetToBuffer( LONGLONG qlOffSet );
       /*{{|method_: `LONGLONG BufferToOffset( LPBYTE p )` | desc_: The file offset of a pointer inside the
          valid bytes, -1 when p is outside them. }}*/
       LONGLONG BufferToOffset( LPBYTE p );
       /*{{|method_: `LPBYTE GetBaseBuffer( void )` | desc_: The first valid byte, 0 when the buffer is empty. }}*/
       LPBYTE GetBaseBuffer( void);
       /*{{|method_: `LPBYTE GetMaxBuffer( void )` | desc_: One past the last valid byte, 0 when the buffer is
          empty. }}*/
       LPBYTE GetMaxBuffer( void);
       /*{{|method_: `void SetBaseBuffer( LONGLONG qlPos )` | desc_: Makes file offset **qlPos** the first
          valid byte: inside the window the bytes before it are just consumed (m_dwBuffShift grows); outside
          it the buffer is emptied and anchored at qlPos, to be loaded again. }}*/
       void SetBaseBuffer( LONGLONG qlPos );
       /*{{|method_: `void PackBuffer( void )` | desc_: Moves the valid bytes to the start of the allocation,
          so that LoadRestOfBuffer() has room after them. }}*/
       void PackBuffer( void );
       /*{{|method_: `BOOL LoadRestOfBuffer( BOOL* pbEof )` | desc_: Appends to the valid bytes what fits in
          the allocation, read from the file at the end offset of the buffer. TRUE when something was read;
          FALSE when the buffer is not valid or already full. }}*/
       BOOL LoadRestOfBuffer(BOOL * pbEof);
       // ------------
       /*{{|method_: `LPBYTE ReadLine( DWORD* pnLineLen, BOOL* pbEof, BOOL* pbEol )`
          | desc_: The line at the current file position, as a pointer inside the buffer (loaded or extended
            as needed) with its length in **pnLineLen**, without the line end. A line ends at CR, LF or CRLF;
            **pbEol** is FALSE when the buffer ran out before an end of line was found (the line is longer
            than the buffer, or the file ended). The file pointer moves past the line and its terminator, so
            the next call reads the next line. Returns 0, with **pbEof** TRUE, when nothing could be read. }}*/
       LPBYTE ReadLine(DWORD * pnLineLen , BOOL * pbEof , BOOL * pbEol );
       /*{{|method_: `LPBYTE ReadMimeHeader( DWORD* pnHeaderLen, BOOL* pbEof, BOOL* pbEoh )`
          | desc_: Like ReadLine() for a whole MIME header block: the bytes from the current position up to
            and including the empty line that closes the headers (CRLF CRLF, CR CR or LF LF), **pbEoh** TRUE
            when that separator was found. Without it, and not at the end of the file, only the bytes up to
            the last character that is not a line end are consumed. }}*/
	   LPBYTE ReadMimeHeader(DWORD * pnHeaderLen, BOOL * pbEof, BOOL * pbEoh);
       /*{{|method_: `BOOL SaveBuffer( void )` | desc_: Writes m_dwBuffLen bytes from the start of the
          allocation at the current file position (call PackBuffer() first when m_dwBuffShift is not 0).
          TRUE when WriteFile succeeded. }}*/
       BOOL   SaveBuffer(void);
       // ------------
       /*{{|method_: `BOOL IsValidHandle( void )` | desc_: TRUE when the handle is neither 0 nor
          INVALID_HANDLE_VALUE. }}*/
       BOOL IsValidHandle(void);

};
/*{{end-cpp-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-class}}*/
/*{{cpp-class_: TFileWriter
   | category: c-api/classes , filesystem
   | desc: A buffered writer: the bytes given to Add() accumulate in a {{ilink: <cpp-class TByteStream> TByteStream}}
     cache, optionally transformed by an encoder engine on the way in, and are written to the file when the
     cache reaches its size, on Write(), Commit() or Close(). The output is a file created by the writer or an
     attached handle; with neither the writer is memory-only and the cache is the result. It is the engine of
     the Xbase++ class {{ilink: <class TFileWriter> TFileWriter}}. It does not derive from T_ot4xb_base: it is
     meant to live on the stack or inside another object.
     | _kw_: TFileWriter, Class }}*/
class OT4XB_API TFileWriter
{
   public:
   // ---------------------------------------------------------------------------------
   /*{{|member_: `enum enc_e` | desc_: The encoder engines, applied to every Add():
      - `e_enc_none`: bytes as they are.
      - `e_enc_base64_decode`: the input is base64 text, the cache gets the decoded bytes.
      - `e_enc_uu_decode`: the input is uuencoded text.
      - `e_enc_qp_decode`: the input is quoted-printable text (the engine flags select its variant).
      - `e_enc_ot4xb_encode`: the input is escaped with the ot4xb notation for XML-unsafe bytes.
      - `e_enc_count`: one past the last valid engine. }}*/
   enum enc_e
   {
      e_enc_none          = 0 ,
      e_enc_base64_decode = 1 ,
      e_enc_uu_decode     = 2 ,
      e_enc_qp_decode     = 3 ,
	  e_enc_ot4xb_encode  = 4 ,
      e_enc_count
   };

   // ---------------------------------------------------------------------------------
   /*{{|member_: `TBinFile m_file` | desc_: The output file. }}*/
   TBinFile      m_file;
   /*{{|member_: `TByteStream m_cache` | desc_: The pending bytes (block size 512 KB). }}*/
   TByteStream   m_cache;
   /*{{|member_: `DWORD m_cache_size` | desc_: Cache length that triggers an automatic Write() inside Add();
      1 MB by default. }}*/
   DWORD         m_cache_size;
   /*{{|member_: `enc_e m_encoder` | desc_: The engine in use, e_enc_none by default. }}*/
   enc_e         m_encoder;
   /*{{|member_: `DWORD m_encoder_flags` | desc_: The flags given with the engine. }}*/
   DWORD         m_encoder_flags;
   /*{{|member_: `BOOL m_memory_only` | desc_: TRUE while there is no output file: nothing is ever written and
      the cache keeps everything. }}*/
   BOOL          m_memory_only;

   // ---------------------------------------------------------------------------------
   /*{{|method_: `TFileWriter( void )` | desc_: Memory-only, no engine, 1 MB cache size. }}*/
   TFileWriter(void);
   /*{{|method_: `~TFileWriter( void )` | desc_: Close(): pending bytes are written and the file closed. }}*/
   ~TFileWriter(void);
   // ---------------------------------------------------------------------------------
   /*{{|method_: `BOOL Create( LPSTR pFilename, BOOL bPreserveBuffer = FALSE )`
      | desc_: Creates (CREATE_ALWAYS, write only, no sharing) the output file; the cache is emptied unless
        **bPreserveBuffer**, so bytes added in memory-only mode can be kept and written to the new file.
        TRUE when the file is open; FALSE leaves the writer memory-only. }}*/
   BOOL   Create( LPSTR pFilename , BOOL bPreserveBuffer = FALSE );
   /*{{|method_: `void AttachFileHandle( HANDLE hFile, BOOL bPreserveBuffer = FALSE )`
      | desc_: Uses an open handle as output (the previous file is closed); a 0 or invalid handle makes the
        writer memory-only. The cache is emptied unless **bPreserveBuffer**. }}*/
   void   AttachFileHandle( HANDLE hFile ,BOOL bPreserveBuffer = FALSE );
   /*{{|method_: `HANDLE DetachFileHandle( void )` | desc_: Returns the output handle without closing it and
      goes memory-only. Pending bytes are not written first. }}*/
   HANDLE DetachFileHandle(void);
   /*{{|method_: `HANDLE GetFileHandle( void )` | desc_: The output handle (INVALID_HANDLE_VALUE when
      memory-only). }}*/
   HANDLE GetFileHandle(void);
   /*{{|method_: `void Close( void )` | desc_: Writes the pending bytes, closes the file and goes memory-only. }}*/
   void   Close(void);
   // ---------------------------------------------------------------------------------
   /*{{|method_: `BOOL SetEncoderEngine( enc_e encoder, DWORD nFlags = 0 )`
      | desc_: Selects the engine for the next Add() calls; FALSE, and no change, for a value out of the
        enumeration. }}*/
   BOOL SetEncoderEngine( enc_e encoder , DWORD nFlags = 0 );

   /*{{|method_: `void SetCacheSize( DWORD nBytes )` | desc_: Sets the length that triggers an automatic
      Write(). }}*/
   void SetCacheSize( DWORD nBytes);
   // ---------------------------------------------------------------------------------
   /*{{|method_: `BOOL Add( LPBYTE p, int cb = -1 )`
      | desc_: Appends **cb** bytes (-1: up to the zero terminator) through the engine. With an output file the
        cache is written when it reaches m_cache_size. FALSE when the engine rejects the data, the write
        fails, or the writer has an output but its handle is no longer valid. }}*/
   BOOL Add( LPBYTE p , int cb = - 1 );
   /*{{|method_: `BOOL Add( LPSTR p )` | desc_: Appends a zero-terminated string. }}*/
   BOOL Add(LPSTR p);
   /*{{|method_: `void* _reserve_bytes_( DWORD nBytes )` | desc_: Room for nBytes at the end of the cache, to be
      filled by the caller (no engine, no automatic write). }}*/
   void*  _reserve_bytes_(DWORD nBytes);
   /*{{|method_: `BOOL _skip_bytes_( DWORD nBytes )` | desc_: Advances the cache length over bytes reserved
      with _reserve_bytes_(). }}*/
   BOOL   _skip_bytes_(DWORD nBytes);
   /*{{|method_: `BOOL Write( void )` | desc_: Writes the cache to the file and empties it. TRUE when everything
      was written (or there was nothing, or the writer is memory-only); on a short write the file pointer is
      put back and the cache kept. }}*/
   BOOL Write(void);
   /*{{|method_: `void Commit( void )` | desc_: Write() followed by FlushFileBuffers(). }}*/
   void Commit(void);
   // ---------------------------------------------------------------------------------
   /*{{|method_: `BOOL write_xml_node_from_container_value( ContainerHandle con, LPSTR tag, DWORD flags = 0, LPSTR node_name = 0 )`
      | desc_: Adds the value of the container **con** as an XML node, `<tag>value</tag>`; a null tag means
        "col", and **node_name** is written as a `name="..."` attribute. Numeric, Logical, Date and Character
        values are written, any other type gives an empty node; Character content that needs it is escaped or
        encoded, and marked with an `enc="..."` attribute. FALSE only for a null container.
      | flags: bits of **flags** (0 in C++; the Xbase++ method defaults to 0x01100000):
        - `0x80000000` add the type attributes: `t="int|double|bool|string"`, `d="decimals"`, `cb="bytes"`
        - `0x40000000` Logical as `true` / `false` instead of `1` / `0`
        - `0x20000000` strip leading spaces of Character values
        - `0x10000000` strip trailing spaces and record what was stripped as `lt="n"` / `rt="n"` attributes
        - `0x01000000` strip leading and trailing spaces, no attributes
        - `0x00100000` always use the ot4xb escape notation for unsafe content (never `enc="hex"` /
          `enc="base64"`, which are chosen automatically otherwise when the unsafe share is high) }}*/
   BOOL write_xml_node_from_container_value(ContainerHandle con, LPSTR tag, DWORD flags = 0, LPSTR node_name = 0);
   /*{{|method_: `BOOL write_xml_value_from_container( ContainerHandle con )`
      | desc_: Adds the plain XML text of the value, no tag: Numeric with its decimals, Logical as true or
        false, Date as YYYYMMDD, Character with the ot4xb escape notation when it holds XML-unsafe bytes.
        Other types add nothing. FALSE only for a null container. }}*/
	BOOL write_xml_value_from_container( ContainerHandle con );
	   // ---------------------------------------------------------------------------------
};
/*{{end-cpp-class}}*/
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// C++ functions
//----------------------------------------------------------------------------------------------------------------------
#endif // __cplusplus
//----------------------------------------------------------------------------------------------------------------------
#endif