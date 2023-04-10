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
class OT4XB_API TBinFile : public T_ot4xb_base
{
   public:
       HANDLE              m_hFile;
       DWORD               m_dwLastError;
       // ------------
       DWORD               m_dwAttributes;
       DWORD               m_dwReserved;
       // ------------
       LONGLONG            m_qlPos;       // CURRENT FILE POINTER POSITION
       LONGLONG            m_qlSize;      // SIZE OF THE FILE
       LONGLONG            m_qlBuffStart; // CURRENT BUFFER POSITION FROM THE BEGIN
       // ------------
       LPBYTE              m_pBuffer;
       DWORD               m_dwBuffSize;   // Size of the read/write buffer
       // -----------
       DWORD               m_dwBuffShift;  // begin of buffer ( for search optimization)
       DWORD               m_dwBuffLen;    // Valid Len of Buffer ( from dwShift )
       // ------------

       // ---------------------------------------------------------------------------------
       TBinFile(void);
       ~TBinFile(void);
       // ------------
       void InitFromHandle( HANDLE hFile );
       HANDLE DetachHandle(void);
       // ------------       
       void Close(void);
       BOOL Open(LPSTR pFName , DWORD dwAccess = (GENERIC_READ | GENERIC_WRITE) ,
                 DWORD dwShare = 0 , BOOL bOpenAlways = FALSE );
       BOOL Create(LPSTR pFName , DWORD dwAccess = (GENERIC_READ | GENERIC_WRITE),
                   DWORD dwShare = 0, LPSECURITY_ATTRIBUTES psa = NULL ,
                   DWORD dwCmd = OPEN_ALWAYS ,DWORD dwFlags = FILE_ATTRIBUTE_NORMAL ,HANDLE hTemp = 0);
       // ------------
       LONGLONG SetFPointer64( LONGLONG ql = 0 , DWORD dwFrom = FILE_BEGIN);
       LONGLONG GetFPointer64(void);
       // ------------
       BOOL bSkipFPointer32( LONG nSkip = 0 , LONG* pSkiped = 0);
       BOOL bSkipFPointer64( LONGLONG nSkip , LONGLONG* pSkipped = 0);
       // ------------
       void ResetBuffer( void );
       void ResetBuffer( DWORD dwSize );
       BOOL LoadBuffer( BOOL * pbEof);
       BOOL bValidBufferOffset(void);
       LONGLONG nqBufferStartOffset(void);
       LONGLONG nqBufferEndOffset(void);
       LPBYTE   OffsetToBuffer( void);
       LPBYTE   OffsetToBuffer( LONGLONG qlOffSet );
       LONGLONG BufferToOffset( LPBYTE p );
       LPBYTE GetBaseBuffer( void);
       LPBYTE GetMaxBuffer( void);
       void SetBaseBuffer( LONGLONG qlPos );
       void PackBuffer( void );
       BOOL LoadRestOfBuffer(BOOL * pbEof);
       // ------------
       LPBYTE ReadLine(DWORD * pnLineLen , BOOL * pbEof , BOOL * pbEol );
	   LPBYTE ReadMimeHeader(DWORD * pnHeaderLen, BOOL * pbEof, BOOL * pbEoh);
       BOOL   SaveBuffer(void); 
       // ------------
       BOOL IsValidHandle(void);

};
//----------------------------------------------------------------------------------------------------------------------
class OT4XB_API TFileWriter
{
   public:
   // ---------------------------------------------------------------------------------
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
   TBinFile      m_file;
   TByteStream   m_cache;
   DWORD         m_cache_size;
   enc_e         m_encoder;
   DWORD         m_encoder_flags;   
   BOOL          m_memory_only;
   
   // ---------------------------------------------------------------------------------
   TFileWriter(void);
   ~TFileWriter(void);
   // ---------------------------------------------------------------------------------
   BOOL   Create( LPSTR pFilename , BOOL bPreserveBuffer = FALSE );
   void   AttachFileHandle( HANDLE hFile ,BOOL bPreserveBuffer = FALSE );
   HANDLE DetachFileHandle(void);
   HANDLE GetFileHandle(void);
   void   Close(void);
   // ---------------------------------------------------------------------------------
   BOOL SetEncoderEngine( enc_e encoder , DWORD nFlags = 0 );
   
   void SetCacheSize( DWORD nBytes);
   // ---------------------------------------------------------------------------------
   BOOL Add( LPBYTE p , int cb = - 1 );
   BOOL Add(LPSTR p);
   void*  _reserve_bytes_(DWORD nBytes);
   BOOL   _skip_bytes_(DWORD nBytes);
   BOOL Write(void);
   void Commit(void);
   // ---------------------------------------------------------------------------------
   BOOL write_xml_node_from_container_value(ContainerHandle con, LPSTR tag, DWORD flags = 0, LPSTR node_name = 0);
	BOOL write_xml_value_from_container( ContainerHandle con );
	   // ---------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// C++ functions
//----------------------------------------------------------------------------------------------------------------------
#endif // __cplusplus
//----------------------------------------------------------------------------------------------------------------------
#endif