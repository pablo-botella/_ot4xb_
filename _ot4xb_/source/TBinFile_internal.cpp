//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
// #define OT4XB_DEBUG
#include <ot4xb_api.h>
//-----------------------------------------------------------------------------------------------------------------------
TBinFile::TBinFile(void)
{
   m_hFile        = INVALID_HANDLE_VALUE;
   m_dwLastError  = 0;
   m_dwAttributes = 0;
   m_dwReserved   = 0;
   m_qlPos        = 0;
   m_qlSize       = 0;
   m_qlBuffStart  = 0;
   m_pBuffer      = 0;
   m_dwBuffSize   = 0;
   m_dwBuffShift  = 0;
   m_dwBuffLen    = 0;
}
//----------------------------------------------------------------------------------------------------------------------
TBinFile::~TBinFile(void)
{
   if(m_pBuffer)
   {
      _xfree( (void * ) m_pBuffer );
   }
}
//-----------------------------------------------------------------------------------------------------------------------
void TBinFile::InitFromHandle( HANDLE hFile )
{
   m_hFile = hFile;
   m_qlPos       = m_qlSize = m_qlBuffStart = 0;
   if(m_pBuffer   ) _xfree( (void * ) m_pBuffer   );
   m_pBuffer  = NULL;
   GetFPointer64();
}
// -----------------------------------------------------------------------------------------------------------------
HANDLE TBinFile::DetachHandle(void)
{
   HANDLE hFile = m_hFile;
   if(m_pBuffer   ) _xfree( (void * ) m_pBuffer   );
   m_dwLastError  = 0;
   m_dwAttributes = 0;
   m_dwReserved   = 0;
   m_qlPos        = 0;
   m_qlSize       = 0;
   m_qlBuffStart  = 0;
   m_pBuffer      = 0;
   m_dwBuffSize   = 0;
   m_dwBuffShift  = 0;
   m_dwBuffLen    = 0;
   return hFile;
}
//-----------------------------------------------------------------------------------------------------------------------
void TBinFile::Close( void )
{
   if( m_hFile != INVALID_HANDLE_VALUE ) CloseHandle( m_hFile ) ;
   m_hFile = INVALID_HANDLE_VALUE;
   if(m_pBuffer   ) _xfree( (void * ) m_pBuffer   );
   m_pBuffer  = NULL;
   m_qlPos       = m_qlSize = m_qlBuffStart = 0;
   m_dwBuffSize  = m_dwBuffLen = m_dwBuffShift = 0;
}
//-----------------------------------------------------------------------------------------------------------------------
BOOL TBinFile::Open(LPSTR pFName , DWORD dwAccess , DWORD dwShare , BOOL bOpenAlways)
{
   Close();
   if( pFName )
   {
      HANDLE hFile = CreateFile( pFName , dwAccess , dwShare , NULL , ( bOpenAlways ? OPEN_ALWAYS : OPEN_EXISTING ) ,0 , 0);
      if( hFile != INVALID_HANDLE_VALUE ){ InitFromHandle( hFile ); return TRUE;}
   }
   return FALSE;
}
//-----------------------------------------------------------------------------------------------------------------------
BOOL TBinFile::Create(LPSTR pFName , DWORD dwAccess,DWORD dwShare,LPSECURITY_ATTRIBUTES psa,
                      DWORD dwCmd,DWORD dwFlags,HANDLE hTemp)
{
   Close();
   if( pFName )
   {
      HANDLE hFile = CreateFile( pFName , dwAccess , dwShare , psa , dwCmd,dwFlags,hTemp);
      if( hFile != INVALID_HANDLE_VALUE ){ InitFromHandle( hFile ); return TRUE;}
   }
   return FALSE;
}
//----------------------------------------------------------------------------------------------------------------------
LONGLONG TBinFile::SetFPointer64( LONGLONG ql , DWORD dwFrom)
{

   if( m_hFile == (HANDLE) -1 )
   {
      m_dwLastError = ERROR_INVALID_HANDLE;
      SetLastError( ERROR_INVALID_HANDLE );
      m_qlPos = -1;
      return -1;
   }
   else
   {
      LARGE_INTEGER li;
      m_dwLastError = 0;
      SetLastError(0);
      li.QuadPart   = ql;
      li.LowPart    = SetFilePointer( m_hFile , li.LowPart , &(li.HighPart) , dwFrom );
      m_dwLastError = ( (li.LowPart == INVALID_SET_FILE_POINTER) ?  GetLastError() : 0);

      if( m_dwLastError )
      {
         SetLastError(0);
         li.QuadPart   = 0;
         li.LowPart    = SetFilePointer( m_hFile , 0 , &(li.HighPart) , FILE_CURRENT );
         if( GetLastError() ) m_qlPos = -1;
         else m_qlPos = li.QuadPart;
         SetLastError( m_dwLastError );
         return -1;
      }
      else m_qlPos = li.QuadPart;
      return m_qlPos;
   }
}
//-----------------------------------------------------------------------------------------------------------------------
LONGLONG TBinFile::GetFPointer64(void){ return SetFPointer64( 0 , FILE_CURRENT); }
//-----------------------------------------------------------------------------------------------------------------------
BOOL TBinFile::bSkipFPointer32( LONG nSkip , LONG* pSkipped )
{
   LONGLONG qlStart = m_qlPos;
   LARGE_INTEGER li;

   if( m_hFile == (HANDLE) -1 ) return FALSE;
   if( qlStart == -1 ) qlStart = GetFPointer64(); // Give a chance to update pos
   if( qlStart == -1 ) return FALSE;

   SetLastError(0);
   li.QuadPart = 0;
   li.LowPart  = SetFilePointer( m_hFile , nSkip , &(li.HighPart) , FILE_CURRENT );
   m_dwLastError = ( (li.LowPart == INVALID_SET_FILE_POINTER) ?  GetLastError() : 0);
   if( m_dwLastError ) li.QuadPart = GetFPointer64();
   else m_qlPos = li.QuadPart;
   if( m_qlPos == -1 ) return FALSE;
   li.QuadPart =  qlStart - m_qlPos;
   if( pSkipped ) pSkipped[0] = (LONG) li.LowPart;
   return TRUE;
}
//-----------------------------------------------------------------------------------------------------------------------
BOOL TBinFile::bSkipFPointer64( LONGLONG nSkip , LONGLONG* pSkipped )
{
   LONGLONG qlStart = m_qlPos;
   LARGE_INTEGER li;

   if( m_hFile == (HANDLE) -1 ) return FALSE;
   if( qlStart == -1 ) qlStart = GetFPointer64(); // Give a chance to update pos
   if( qlStart == -1 ) return FALSE;

   SetLastError(0);
   li.QuadPart = nSkip;
   li.LowPart  = SetFilePointer( m_hFile ,  (LONG) li.LowPart , &(li.HighPart) , FILE_CURRENT );
   m_dwLastError = ( (li.LowPart == INVALID_SET_FILE_POINTER) ?  GetLastError() : 0);
   if( m_dwLastError ) li.QuadPart = GetFPointer64();
   else m_qlPos = li.QuadPart;
   if( m_qlPos == -1 ) return FALSE;
   li.QuadPart =  qlStart - m_qlPos;
   if( pSkipped ) pSkipped[0] = li.QuadPart;
   return TRUE;
}
//----------------------------------------------------------------------------------------------------------------------
LONGLONG TBinFile::nqBufferStartOffset(void)
{
   if( m_qlBuffStart ==  -1 ) return -1;
   if( !m_dwBuffLen ) return -1;
   return m_qlBuffStart;
}
//----------------------------------------------------------------------------------------------------------------------
LONGLONG TBinFile::nqBufferEndOffset(void)
{
   LARGE_INTEGER li;
   if( m_qlBuffStart ==  -1 ) return -1;
   if( !m_dwBuffLen ) return -1;
   li.LowPart  = m_dwBuffLen;
   li.HighPart = 0;
   return m_qlBuffStart + li.QuadPart;
}
//-----------------------------------------------------------------------------------------------------------------------
BOOL TBinFile::bValidBufferOffset(void)
{
   if( !m_dwBuffLen ) return 0;
   if( !m_pBuffer   ) return 0;
   if( m_qlBuffStart == (LONGLONG) -1 ) return FALSE;
   if( GetFPointer64() < nqBufferStartOffset() ) return FALSE;
   return (BOOL) ( m_qlPos < nqBufferEndOffset() );
}
//----------------------------------------------------------------------------------------------------------------------
void TBinFile::ResetBuffer( void ){ ResetBuffer( m_dwBuffSize ); }
//----------------------------------------------------------------------------------------------------------------------
void TBinFile::ResetBuffer( DWORD dwSize)
{
   if( dwSize > 0x4000000 ) dwSize =  0x4000000;
   if( dwSize == 0) dwSize = 65536;
   if( m_dwBuffSize != dwSize ) { if( m_pBuffer ){ _xfree( (void * ) m_pBuffer); m_pBuffer = 0;} }
   m_dwBuffSize = dwSize;
   if( !m_pBuffer ) m_pBuffer = (LPBYTE) _xgrab(m_dwBuffSize);
   m_qlBuffStart = GetFPointer64();
   m_dwBuffShift = 0;
   m_dwBuffLen   = 0;
}
//----------------------------------------------------------------------------------------------------------------------
BOOL TBinFile::LoadBuffer( BOOL * pbEof)
{
   DWORD  nRead;
   DWORD  nDone   = 0;
   LPBYTE p       = 0;
   BOOL bOk       = FALSE;
   BOOL bEof = FALSE;
   ResetBuffer();
   nRead   = (m_dwBuffSize - m_dwBuffShift);
   p       = (LPBYTE) (  m_pBuffer + m_dwBuffShift );
   if( ReadFile(m_hFile,p, nRead,&nDone,NULL) )
   {
      m_dwBuffLen = nDone;
      bEof = !( nRead == nDone);
      bOk = TRUE;
   }
   if( pbEof ) pbEof[0] = bEof;
   return bOk;
}
//----------------------------------------------------------------------------------------------------------------------
LPBYTE TBinFile::OffsetToBuffer( void){ return OffsetToBuffer( GetFPointer64() ); }
//----------------------------------------------------------------------------------------------------------------------
LPBYTE TBinFile::OffsetToBuffer( LONGLONG qlOffSet )
{
   if( !m_dwBuffLen ) return 0;
   if( !m_pBuffer   ) return 0;
   if( m_qlBuffStart == (LONGLONG) -1 ) return 0;
   if( qlOffSet < nqBufferStartOffset() ) return 0;
   if( qlOffSet < nqBufferEndOffset() )
   {
      LARGE_INTEGER li;
      li.QuadPart = qlOffSet - nqBufferStartOffset();
      if( li.HighPart ) return 0;
      return (LPBYTE) (m_pBuffer + m_dwBuffShift + li.LowPart);
   }
   return 0;
}
//----------------------------------------------------------------------------------------------------------------------
LONGLONG TBinFile::BufferToOffset( LPBYTE p )
{
   if( bValidBufferOffset() )
   {
      LPBYTE pBase = (LPBYTE) (m_pBuffer + m_dwBuffShift);
      LPBYTE pMax  = (LPBYTE) (pBase + m_dwBuffLen );
      if( (p >= pBase) && (p < pMax) )
      {
         LARGE_INTEGER li;
         li.HighPart  = 0;
         li.LowPart   = ( ((DWORD) p) - ((DWORD) pBase) );
         li.QuadPart += nqBufferStartOffset();
         return li.QuadPart;
      }
   }
   return -1;
}
//----------------------------------------------------------------------------------------------------------------------
LPBYTE TBinFile::GetBaseBuffer(void)
{
   if( m_pBuffer && m_dwBuffLen ) return (LPBYTE) (m_pBuffer + m_dwBuffShift);
   return 0;
}
//----------------------------------------------------------------------------------------------------------------------
LPBYTE TBinFile::GetMaxBuffer( void)
{
   if( m_pBuffer && m_dwBuffLen ) return (LPBYTE) (m_pBuffer + m_dwBuffShift + m_dwBuffLen);
   return 0;
}

//----------------------------------------------------------------------------------------------------------------------
void TBinFile::SetBaseBuffer( LONGLONG qlPos )
{
   LONGLONG qlStart = nqBufferStartOffset();
   LONGLONG qlEnd   = nqBufferEndOffset();
   if( qlPos == qlStart ) return;
   if( (qlPos > qlStart ) && (qlPos < qlEnd) )
   {
      DWORD dw =  (DWORD) ((qlPos - qlStart) & 0xFFFFFFFF);
      m_dwBuffLen   -= dw;
      m_dwBuffShift += dw;
      m_qlBuffStart = qlPos;
      return;
   }
   ResetBuffer();
   m_qlBuffStart = qlPos;
   return;
}
//----------------------------------------------------------------------------------------------------------------------
void TBinFile::PackBuffer( void )
{
   if( m_dwBuffShift )
   {
      DWORD   dw;
      LPBYTE  p = GetBaseBuffer();
      for( dw = 0; dw < m_dwBuffLen; dw++)  m_pBuffer[dw] = p[dw];
      m_dwBuffShift = 0;
   }
}
//----------------------------------------------------------------------------------------------------------------------
BOOL TBinFile::LoadRestOfBuffer(BOOL * pbEof)
{
   if( bValidBufferOffset() )
   {
      if( m_dwBuffLen < m_dwBuffSize)
      {
         DWORD  nRead = (m_dwBuffSize - m_dwBuffLen);
         DWORD  nDone   = 0;
         LPBYTE p       = GetMaxBuffer();
         SetFPointer64( nqBufferEndOffset() );
         if( ReadFile(m_hFile,p, nRead,&nDone,NULL) )
         {
            m_dwBuffLen += nDone;
            if( pbEof ) pbEof[0] = !( nRead == nDone);
            return TRUE;
         }
      }
   }
   return FALSE;
}
//-----------------------------------------------------------------------------------------------------------------------
BOOL TBinFile::SaveBuffer(void)
{

   if( m_pBuffer && IsValidHandle() )
   {
      DWORD cb = 0;
      return ::WriteFile(m_hFile,(void*) m_pBuffer,m_dwBuffLen,&cb,0);
   }
   return FALSE;
} 
// -----------------------------------------------------------------------------------------------------------------
LPBYTE TBinFile::ReadLine(DWORD * pnLineLen , BOOL * pbEof , BOOL * pbEol)
{
   LONGLONG qlPos  = GetFPointer64();
   LARGE_INTEGER li;
   BOOL   bEof     = 0;
   LPBYTE p        = 0;
   DWORD  dw       = 0;

   if( !m_pBuffer ) ResetBuffer();
   SetBaseBuffer( qlPos );
   if( !bValidBufferOffset() )
   {
      ResetBuffer();
      LoadBuffer(&bEof);
   }
   p = GetBaseBuffer();
   if( !p )
   {
      if( pbEof ) pbEof[0] = TRUE;
      return 0;
   }

   for(; dw < m_dwBuffLen; dw++ )
   {
      switch( p[dw] )
      {
         case 13: goto Found_CR;
         case 10: goto Found_LF;
      }
   }
   // EOL not found so try to search in the rest of buffer if m_dwBuffShift
   PackBuffer();
   if( LoadRestOfBuffer(&bEof) )
   {
      p = GetBaseBuffer();
      for(; dw < m_dwBuffLen; dw++ )
      {
         switch( p[dw] )
         {
            case 13: goto Found_CR;
            case 10: goto Found_LF;
         }
      }
   }
   goto Not_Found;

   Found_CR: ;
   {
      if( pbEol )     pbEol[0] = TRUE;
      if( pnLineLen ) pnLineLen[0] = dw;
      dw++;
      if( dw < m_dwBuffLen )
      {
         if( p[dw] == 10 ) dw++;
      }
      else
      {
         PackBuffer();
         if( LoadRestOfBuffer(&bEof) )
         {
            p = GetBaseBuffer();
            if( dw < m_dwBuffLen )
            {
               if( p[dw] == 10 ) dw++;
            }
         }
         else
         {
            DWORD nDone = 0;
            BYTE  ch;
            li.LowPart  = dw;
            li.HighPart = 0;
            SetFPointer64( qlPos + li.QuadPart );
            ReadFile(m_hFile,&ch,1,&nDone,NULL);
            if( nDone == 1 ){ if( ch == 10) dw++; }
            else bEof = TRUE;
         }
      }
      li.LowPart  = dw;
      li.HighPart = 0;
      SetFPointer64( qlPos + li.QuadPart );
      if( pbEof ) pbEof[0] = (BOOL) ( bEof && (dw > m_dwBuffLen ) );
      return p;
   }
   Found_LF: ;
   {
      if( pbEol )     pbEol[0] = TRUE;
      if( pnLineLen ) pnLineLen[0] = dw;
      dw++;
      li.LowPart  = dw;
      li.HighPart = 0;
      SetFPointer64( qlPos + li.QuadPart );
      if( pbEof ) pbEof[0] = (BOOL) ( bEof && (dw > m_dwBuffLen ) );
      return p;
   }
   Not_Found: ;
   if( pbEol )     pbEol[0] = FALSE;
   if( pnLineLen ) pnLineLen[0] = dw;
   li.LowPart  = dw;
   li.HighPart = 0;
   SetFPointer64( qlPos + li.QuadPart );
   if( pbEof ) pbEof[0] = (BOOL) ( bEof && (dw > m_dwBuffLen ) );
   return p;
}
// -----------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------
LPBYTE TBinFile::ReadMimeHeader(DWORD * pnHeaderLen, BOOL * pbEof, BOOL * pbEoh)
{
	LONGLONG qlPos = GetFPointer64();
	LARGE_INTEGER li;
	BOOL   bEof = 0;
	LPBYTE p = 0;
	DWORD  dw = 0;
	BOOL bFound = FALSE;
	DWORD cb = 0;



	if (!m_pBuffer) ResetBuffer();
	SetBaseBuffer(qlPos);
	if (!bValidBufferOffset())
	{
		ResetBuffer();
		LoadBuffer(&bEof);
	}
	PackBuffer();
	p = GetBaseBuffer();
	if (!p)
	{
		if (pbEof) pbEof[0] = TRUE;
		return 0;
	}

	for (; dw < m_dwBuffLen && !bFound ; dw++)
	{
		
		if (p[dw] == 0x0D || p[dw] == 0x0A)
		{

			if ((m_dwBuffLen - dw) > 2)
			{

				if ((m_dwBuffLen - dw) > 4 && *_mk_ptr_(LPDWORD, p, dw) == 0x0A0D0A0D)
				{
					dw += 3; bFound = TRUE;
				}
				if (!bFound)
				{
					if(*_mk_ptr_(LPWORD, p, dw) == 0x0D0D || *_mk_ptr_(LPWORD, p, dw) == 0x0A0A )
					{
						dw++; bFound = TRUE;
					}
					else
					{
						if(*_mk_ptr_(LPWORD, p, dw) ==  0x0A0D)
						{ 
							dw++;  
						}
					}
				}
			}
		}
		else
		{
			cb = dw;
		}
	}
	
	if (!bFound)
	{
		if (!bEof)
		{
			dw = cb;
		}
	}

	if (pbEoh)     pbEoh[0] = bFound;
	if (pnHeaderLen) pnHeaderLen[0] = dw;
	li.LowPart = dw; li.HighPart = 0;
	SetFPointer64(qlPos + li.QuadPart);
	if (pbEof) pbEof[0] = (BOOL)(bEof && (dw > m_dwBuffLen));
	return p;
}
// -----------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------
BOOL TBinFile::IsValidHandle(void)
{
   if( m_hFile )
   {
      if( m_hFile != INVALID_HANDLE_VALUE )
      {
         return TRUE;
      }
   }
   return FALSE;
}
//----------------------------------------------------------------------------------------------------------------------
TFileWriter::TFileWriter(void)
{
   m_cache_size = 1024 * 1024; // 1MB   
   m_encoder    = e_enc_none;
   m_cache.m_nBlockSize = 512 * 1024;
   m_memory_only        = TRUE;
}
// -----------------------------------------------------------------------------------------------------------------
TFileWriter::~TFileWriter(void)
{
   Close();
}
// -----------------------------------------------------------------------------------------------------------------
void TFileWriter::SetCacheSize( DWORD nBytes)
{
   m_cache_size = nBytes;
}
// -----------------------------------------------------------------------------------------------------------------
BOOL TFileWriter::SetEncoderEngine( enc_e encoder , DWORD nFlags)
{
   if( (encoder >= e_enc_none) && ( encoder < e_enc_count ) )
   {
      m_encoder = encoder;
      m_encoder_flags = nFlags;
      return TRUE;
   }
   return FALSE;
}
// -----------------------------------------------------------------------------------------------------------------
BOOL TFileWriter::Create( LPSTR pFilename , BOOL bPreserveBuffer  )
{
   if( ! bPreserveBuffer)
   {
      m_cache._truncate_buffer_();
   }
   m_memory_only= !m_file.Create(pFilename,GENERIC_WRITE,0,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
   return !m_memory_only;
}
// -----------------------------------------------------------------------------------------------------------------
void TFileWriter::AttachFileHandle( HANDLE hFile , BOOL bPreserveBuffer  )
{
   if( ! bPreserveBuffer)
   {
      m_cache._truncate_buffer_();
   }
   m_file.Close();
   m_file.InitFromHandle( hFile );
   m_memory_only = (BOOL) ((( hFile == 0) || ( hFile == INVALID_HANDLE_VALUE)) ? 1 : 0 );
}
// -----------------------------------------------------------------------------------------------------------------
HANDLE TFileWriter::DetachFileHandle(void)
{
   m_memory_only = TRUE;
   return m_file.DetachHandle();
}
// -----------------------------------------------------------------------------------------------------------------
HANDLE TFileWriter::GetFileHandle(void)
{
   return m_file.m_hFile;
}
// -----------------------------------------------------------------------------------------------------------------
void TFileWriter::Close(void)
{
   Write();
   m_file.Close();
   m_memory_only        = TRUE;   
}
// -----------------------------------------------------------------------------------------------------------------
void*  TFileWriter::_reserve_bytes_(DWORD nBytes){return m_cache._reserve_bytes_(nBytes);}
// -----------------------------------------------------------------------------------------------------------------
BOOL   TFileWriter::_skip_bytes_(DWORD nBytes) { return m_cache._skip_bytes_(nBytes); }
// -----------------------------------------------------------------------------------------------------------------
BOOL TFileWriter::Add(LPSTR p)
{
	return Add( (LPBYTE) p , -1);
}
// -----------------------------------------------------------------------------------------------------------------
BOOL TFileWriter::Add( LPBYTE p , int cb )
{
   HANDLE hFile = m_file.m_hFile;
   if(!m_memory_only )
   {
      if( (!hFile ) || (hFile == INVALID_HANDLE_VALUE) )
      {
         return FALSE;
      }
   }
   switch( m_encoder )
   {
      case e_enc_none:
      {
         if( !m_cache.Add(p,cb) )
         {
            return FALSE;
         }
         break;
      }
      case e_enc_base64_decode:
      {
         if( !m_cache.append_decode_base64((LPSTR) p,cb) )
         {
            return FALSE;
         }
         break;
      }
      case e_enc_uu_decode:
      {
         if( !m_cache.append_decode_uu((LPSTR) p,cb) )
         {
            return FALSE;
         }
         break;
      }         
      case e_enc_qp_decode:
      {
         if( !m_cache.append_decode_qp((LPSTR) p,cb,m_encoder_flags) )
         {
            return FALSE;
         }
         break;
      }      
	  case e_enc_ot4xb_encode:
	  {
		  if (!m_cache.append_encode_ot4xb((LPSTR)p, cb , m_encoder_flags ))
		  {
			  return FALSE;
		  }
		  break;
	  }
      default:
      {
         return FALSE;
      }
   }
   if( m_memory_only ){ return TRUE; }   
   if( m_cache.len() >= m_cache_size )
   {
      return Write();
   }
   return TRUE;
}
// -----------------------------------------------------------------------------------------------------------------
BOOL TFileWriter::Write(void)
{
   if( m_memory_only ){ return TRUE; }

   HANDLE hFile = m_file.m_hFile;
   if( (!hFile ) || (hFile == INVALID_HANDLE_VALUE) )
   {
      return FALSE;
   }
   LONGLONG q = m_file.GetFPointer64();
   DWORD cb = m_cache.len();
   if( !cb ){ return TRUE; }
   void* p = (void*) m_cache.GetBuffer();
   if(!p){ return FALSE; }
   DWORD dw = 0;
   BOOL result = WriteFile(hFile,p,cb,&dw,0);
   if( result && (dw != cb) ){ result = FALSE; }
   if( result )
   {
      m_cache._truncate_buffer_();
   }
   else
   {
      m_file.SetFPointer64(q);
   }
   return result;
}
// -----------------------------------------------------------------------------------------------------------------
void TFileWriter::Commit(void)
{
   if( m_memory_only ){ return; }
   HANDLE hFile = m_file.m_hFile;
   if( (hFile ) && (hFile != INVALID_HANDLE_VALUE) )
   {
      Write();
      FlushFileBuffers(hFile);
   }
}
// ------------------------------------------------------------------------------------------------------------------
static ULONG xml_ot4xb_unsafe_count(LPBYTE p, ULONG cb, BOOL * pbNeedEncode)
{
	ULONG count = 0;
	ULONG n;
	BOOL bNeedEncode = FALSE;
	for (n = 0; n < cb; n++)
	{
		BYTE c = p[n];
		if ((c == '&') || (c == '\\') || (c == '<') || (c == '>') || (c == 13) || (c == 10))
		{
			bNeedEncode = TRUE;
		}
		if ((c < 32 || c > 127) && (c != 13) && (c != 10))
		{
			count++;
			bNeedEncode = TRUE;
		}

	}
	if (pbNeedEncode) { pbNeedEncode[0] = bNeedEncode; }
	return count;
}
// -----------------------------------------------------------------------------------------------------------------
BOOL TFileWriter::write_xml_node_from_container_value( ContainerHandle con , LPSTR tag , DWORD flags, LPSTR node_name )
{
	BOOL result = FALSE;
	if (con)
	{
		ULONG ft = 0;
		DWORD attrib_count = 0;
		_conType(con, &ft);
		result = TRUE;
		Add("<"); Add(tag ? tag : "col");
		if (node_name) 
		{
           Add(" name=\""); Add(node_name); Add("\""); 
		   attrib_count++;
		}
		switch (ft & 0xFF)
		{
			case XPP_NUMERIC:
			{
				if ((ft & _xpp_DOUBLE) == _xpp_DOUBLE)
				{
					double v; LONG ii; LONG dd; LPSTR p; int cb;
					_conGetNDF(con, &v, &ii, &dd);

					if (flags & 0x80000000)
					{
						p = (LPSTR)_reserve_bytes_(1024); 
						cb = _sprintf_p(p, 1024, " t=\"double\" d=\"%i\"", dd);
						attrib_count++;
						_skip_bytes_(cb);
					}
					if (attrib_count) { Add(" "); }
					p = (LPSTR)_reserve_bytes_(1024);
					cb = _sprintf_p(p, 1024, ">%.*f",dd, v);
					_skip_bytes_(cb);
				}
				else
				{
					LONG v; LPSTR p; int cb;
					_conGetNL(con, &v);
					if (flags & 0x80000000)
					{
						Add( " t=\"int\"");
						attrib_count++;
					}
					if (attrib_count) { Add(" "); }
					p = (LPSTR)_reserve_bytes_(1024);
					cb = _sprintf_p(p, 1024, ">%.i",v);
					_skip_bytes_(cb);
				}
				break;
			}
			case XPP_LOGICAL:
			{
				BOOL v; 
				_conGetL(con, &v);
				if (flags & 0x80000000)
				{
					Add(" t=\"bool\"");
					attrib_count++;
				}
				if (attrib_count) { Add(" "); }
				if (flags & 0x40000000)
				{
					Add(v ? ">true" : ">false");
				}
				else
				{
					Add(v ? ">1" : ">0");
				}
				break;
			}
			case XPP_DATE:
			{
				BOOL bEmpty;
				_conIsEmpty(con, &bEmpty);
				if (flags & 0x80000000)
				{
					Add(" t=\"date\"");
					attrib_count++;
				}
				if (attrib_count) { Add(" "); }
				Add(">");
				if (!bEmpty)
				{
					_conGetDS(con, (LPSTR)_reserve_bytes_(1024));
					_skip_bytes_(8);
				}
				break;
			}
			case XPP_CHARACTER:
			{
				LPSTR ps; ULONG cbs = 0;
				if (flags & 0x80000000)
				{
					Add(" t=\"string\"");
					attrib_count++;
				}
				if (_conRLockC(con, &ps, &cbs) )
				{
					Add(" cb=\"error\""); 
					attrib_count++;
				}
				else
				{
					LPSTR pd; int cbd;
					if (flags & 0x80000000)
					{
						pd = (LPSTR)_reserve_bytes_(1024);
						cbd = _sprintf_p(pd, 1024, " cb=\"%i\"", cbs);
						_skip_bytes_(cbd);
						attrib_count++;
					}

					if (cbs && ((flags & 0x20000000) || (flags & 0x01000000) ) )
					{
						int lt = 0;
						while (*ps == 0x20) { ps++; cbs--; lt++; }
						if (lt && (flags & 0x10000000))
						{
							pd = (LPSTR)_reserve_bytes_(1024);
							cbd = _sprintf_p(pd, 1024, " lt=\"%i\" ", lt);
							_skip_bytes_(cbd);
							attrib_count++;
						}
					}
					if (cbs && ((flags & 0x10000000) || (flags & 0x01000000)))
					{
						int rt = 0;
						while (cbs && ps[(cbs - 1)] == 0x20) { cbs--; rt++; }
						if (rt && (flags & 0x10000000))
						{
						   pd = (LPSTR)_reserve_bytes_(1024);
						   cbd = _sprintf_p(pd, 1024, " rt=\"%i\" ", rt);
						   _skip_bytes_(cbd);
						   attrib_count++;
						}
					}
					if (cbs)
					{

						int encode = 0;	// 0 ot4xb; 1 hex ; 2 base64;
						BOOL bNeedEncode = FALSE;
						ULONG unsafe_count = xml_ot4xb_unsafe_count((LPBYTE)ps, cbs, &bNeedEncode);

						if (bNeedEncode && (cbs > 10))
						{

							if (unsafe_count > ((cbs >> 2) & 0x3FFFFFFF))
							{
								encode = (cbs > 32) ? 2 : 1;
							}
						}
						if (flags & 0x00100000) { encode = 0; }
						switch (encode)
						{
							case 2:
							{
								Add(" enc=\"base64\" >");
								cbd = ot4xb_base64_encode_required_length(cbs);
								pd = pd = (LPSTR)_reserve_bytes_(cbd + 1024);
								if (ot4xb_base64_encode((LPBYTE)ps, (int)cbs, pd, &cbd, 2))
								{
									_skip_bytes_(cbd);
								}
								break;
							}
							case 1:
							{
								Add(" enc=\"hex\" >");
								cbd = (cbs * 2);
								pd = pd = (LPSTR)_reserve_bytes_(cbd + 1024);
								cbd = Bin2Hex_buffer((LPBYTE)ps, cbs, pd, cbd);
								_skip_bytes_(cbd);
								break;
							}
							default:
							{
								if (bNeedEncode)
								{
									Add(" enc=\"ot4xb\"");
								}
								if (attrib_count) { Add(" "); }
								Add(">");
								if (bNeedEncode)
								{
									SetEncoderEngine(TFileWriter::enc_e::e_enc_ot4xb_encode);
								}
								Add((LPBYTE)ps, cbs);
								SetEncoderEngine(TFileWriter::enc_e::e_enc_none);
								break;
							}
						}
					}
					else
					{
						if (attrib_count) { Add(" "); }
						Add(">");
					}
					_conUnlockC(con);
				}
				break;
			}
			default:
			{
				if (attrib_count) { Add(" "); }
				Add(">");
				break;
			}


		}
		Add("</"); Add(tag ? tag : "col");Add(">");
	}
	return result;
}
// ------------------------------------------------------------------------------------------------------------------------------------------------
BOOL TFileWriter::write_xml_value_from_container( ContainerHandle con )
{
	BOOL result = FALSE;
	if ( con )
	{
		ULONG ft = 0;
		
		_conType( con, &ft );
		result = TRUE;
		switch ( ft & 0xFF )
		{
			case XPP_NUMERIC:
			{
				if ( ( ft & _xpp_DOUBLE ) == _xpp_DOUBLE )
				{
					double v; LONG ii; LONG dd; LPSTR p; int cb;
					_conGetNDF( con, &v, &ii, &dd );
					p = (LPSTR) _reserve_bytes_( 1024 );
					cb = _sprintf_p( p, 1024, "%.*f", dd, v );
					_skip_bytes_( cb );
				}
				else
				{
					LONG v; LPSTR p; int cb;
					_conGetNL( con, &v );
					p = (LPSTR) _reserve_bytes_( 1024 );
					cb = _sprintf_p( p, 1024, "%.i", v );
					_skip_bytes_( cb );
				}
				break;
			}
			case XPP_LOGICAL:
			{
				BOOL v;
				_conGetL( con, &v );
            Add( v ? "true" : "false" );
				break;
			}
			case XPP_DATE:
			{
				BOOL bEmpty;
				_conIsEmpty( con, &bEmpty );
				if ( !bEmpty )
				{
					_conGetDS( con, (LPSTR) _reserve_bytes_( 1024 ) );
					_skip_bytes_( 8 );
				}
				break;
			}
			case XPP_CHARACTER:
			{
				LPSTR ps; ULONG cbs = 0;
				if ( _conRLockC( con, &ps, &cbs ) )
				{
					;
				}
				else
				{
					if ( cbs )
					{
						BOOL bNeedEncode = FALSE;
						xml_ot4xb_unsafe_count( (LPBYTE) ps, cbs, &bNeedEncode );

						if ( bNeedEncode )
						{
							SetEncoderEngine( TFileWriter::enc_e::e_enc_ot4xb_encode );
						}
						Add( (LPBYTE) ps, cbs );
						if ( bNeedEncode )
						{
							SetEncoderEngine( TFileWriter::enc_e::e_enc_none );
						}
						break;
					}
					_conUnlockC( con );
				}
				break;
			}
		}
	}
	return result;
}