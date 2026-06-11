//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
// -----------------------------------------------------------------------------------------------------------------
#define OT4XB_HASH_FLAGS_OUTPUT_HEX     0x00000000
#define OT4XB_HASH_FLAGS_OUTPUT_BIN     0x00000001

#define OT4XB_HASH_FLAGS_INPUT_STRING   0x00000000
#define OT4XB_HASH_FLAGS_INPUT_FILENAME 0x00000010
#define OT4XB_HASH_FLAGS_INPUT_HFILE    0x00000020


#define OT4XB_HASH_FLAGS_INPUT_START            0x00000100
#define OT4XB_HASH_FLAGS_INPUT_MAX_BYTES        0x00000200

#define OT4XB_HASH_FLAGS_INPUT_RESTORE_POS      0x00001000
#define OT4XB_HASH_FLAGS_GRANULARITY            0x00010000

// -----------------------------------------------------------------------------------------------------------------

/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>OT4XB_HASH</name>
      <category>crypto/hash</category>
      <description>
         CryptoAPI-backed hashing helper class. It computes MD2, MD4, MD5, SHA, SHA1, SHA256, SHA384 and SHA512
         hashes from a string, a file name, or an existing file handle.
      </description>
      <syntax>OT4XB_HASH():sha256( cInput | cFile | hFile, [nFlags := 0], [nOffset], [nBytes], [nGranularity] ) -> cHash</syntax>
      <class-methods>
         <method name="sha" syntax="OT4XB_HASH():sha( uInput, [nFlags], [nOffset], [nBytes], [nGranularity] ) -> cHash" />
         <method name="sha1" syntax="OT4XB_HASH():sha1( uInput, [nFlags], [nOffset], [nBytes], [nGranularity] ) -> cHash" />
         <method name="sha256" syntax="OT4XB_HASH():sha256( uInput, [nFlags], [nOffset], [nBytes], [nGranularity] ) -> cHash" />
         <method name="sha384" syntax="OT4XB_HASH():sha384( uInput, [nFlags], [nOffset], [nBytes], [nGranularity] ) -> cHash" />
         <method name="sha512" syntax="OT4XB_HASH():sha512( uInput, [nFlags], [nOffset], [nBytes], [nGranularity] ) -> cHash" />
         <method name="md2" syntax="OT4XB_HASH():md2( uInput, [nFlags], [nOffset], [nBytes], [nGranularity] ) -> cHash" />
         <method name="md4" syntax="OT4XB_HASH():md4( uInput, [nFlags], [nOffset], [nBytes], [nGranularity] ) -> cHash" />
         <method name="md5" syntax="OT4XB_HASH():md5( uInput, [nFlags], [nOffset], [nBytes], [nGranularity] ) -> cHash" />
      </class-methods>
      <flags>
         <flag value="0x00000000">Output hex string. This is the default.</flag>
         <flag value="0x00000001">Output raw binary hash bytes.</flag>
         <flag value="0x00000000">Input is the string value itself. This is the default input mode.</flag>
         <flag value="0x00000010">Input is a file name.</flag>
         <flag value="0x00000020">Input is an existing file handle.</flag>
         <flag value="0x00000100">Use nOffset as the file start offset.</flag>
         <flag value="0x00000200">Use nBytes as maximum file bytes to hash.</flag>
         <flag value="0x00001000">Restore original file position after hashing an existing handle.</flag>
         <flag value="0x00010000">Use nGranularity as file read buffer size, clamped internally between 64 KB and 8 MB.</flag>
      </flags>
      <remarks>
         Combine flags with OR or nOr(). The filename mode opens the file read-only and closes it internally. The
         handle mode leaves the handle open; use 0x00001000 when the current file position must be preserved.
      </remarks>
   </class>
</xbdoc>
*******************************************************************************************************************/

BEGIN_NAMESPACE( ot4xb_hash_ns )
      // ---------------------------------------------------------------------------------
      BOOL process_input_file( TXppParamList &  xpp  , DWORD dwFlags  , HCRYPTHASH hHash )
      {
         HANDLE hFile = INVALID_HANDLE_VALUE;
         BOOL bOk = TRUE;
         if( (dwFlags & 0xF0) == OT4XB_HASH_FLAGS_INPUT_FILENAME )
         {
            LPSTR pFName = xpp[4]->LockStr();
            if( pFName )
            {
               hFile = CreateFile(pFName,GENERIC_READ, FILE_SHARE_READ ,0,OPEN_EXISTING, 0 ,0 );
               xpp[4]->UnlockStr();
            }
         }
         else
         {
            hFile = xpp[4]->GetHandle();
         }
         if(  (hFile == 0) || (hFile == INVALID_HANDLE_VALUE) )
         {
            return FALSE;
         }


         void*  buffer = 0;
         LARGE_INTEGER li;
         LARGE_INTEGER buffer_size; buffer_size.HighPart = 0;  buffer_size.LowPart = 65536;
         LARGE_INTEGER start_offset; start_offset.QuadPart  = 0;
         LARGE_INTEGER save_offset;  save_offset.QuadPart  = 0;
         LARGE_INTEGER max_bytes;  max_bytes.HighPart = 0x7FFFFFFF; max_bytes.LowPart = 0xFFFFFFFF;

         SetFilePointerEx(hFile,start_offset,&save_offset,FILE_CURRENT );

         if( ( dwFlags & OT4XB_HASH_FLAGS_INPUT_START) == OT4XB_HASH_FLAGS_INPUT_START )
         {
            start_offset.QuadPart = xpp[6]->GetQWord();
            if( !SetFilePointerEx(hFile,start_offset,0,FILE_BEGIN ) )
            {
               bOk = FALSE;
            }
         }
         if( ( dwFlags & OT4XB_HASH_FLAGS_GRANULARITY) == OT4XB_HASH_FLAGS_GRANULARITY )
         {
            buffer_size.LowPart = xpp[8]->GetDWord(); // 64kb to 8MB
            if(  buffer_size.LowPart < 65536 ){ buffer_size.LowPart = 65536; }
            if(  buffer_size.LowPart > 0x800000 ){ buffer_size.LowPart = 0x800000; }
         }

         if( ( dwFlags & OT4XB_HASH_FLAGS_INPUT_MAX_BYTES ) == OT4XB_HASH_FLAGS_INPUT_MAX_BYTES )
         {
            max_bytes.QuadPart = xpp[6]->GetQWord();
         }
         BOOL bEof = FALSE;
         if( bOk )
         {
            buffer = _xgrab(buffer_size.LowPart);
         }
         while(  bOk  &&  !bEof  && (max_bytes.QuadPart > 0LL ) && buffer )
         {
            li.QuadPart = ( ( max_bytes.QuadPart < buffer_size.QuadPart ) ? max_bytes.QuadPart : buffer_size.QuadPart );
            DWORD dwRead = 0;
            bOk = ReadFile(hFile,buffer,li.LowPart,&dwRead,0);
            if( bOk )
            {
               bOk = CryptHashData(hHash,(LPBYTE) buffer ,dwRead , 0);
               bEof = ( dwRead < buffer_size.LowPart );
               li.LowPart = dwRead;
               max_bytes.QuadPart = ( max_bytes.QuadPart - li.QuadPart );
            }
         }
         if( buffer ){ _xfree( buffer); buffer = 0; }
         if( (dwFlags & 0xF0) == OT4XB_HASH_FLAGS_INPUT_FILENAME )
         {
            CloseHandle( hFile );
            hFile = INVALID_HANDLE_VALUE;
         }
         else
         {
            if( ( dwFlags & OT4XB_HASH_FLAGS_INPUT_RESTORE_POS) == OT4XB_HASH_FLAGS_INPUT_RESTORE_POS )
            {
               SetFilePointerEx(hFile,save_offset,0,FILE_BEGIN );
            }
         }
         return bOk;
      }
      // ---------------------------------------------------------------------------------
      BOOL process_input_bufer( TXppParamList &  xpp  , DWORD dwFlags  , HCRYPTHASH hHash )
      {
         BOOL bOk = FALSE;
         switch( dwFlags & 0xF0 )
         {
            case OT4XB_HASH_FLAGS_INPUT_STRING :
            {
               DWORD  input_size = 0;
               LPBYTE input_buffer = (LPBYTE ) xpp[4]->LockStr(&input_size,FALSE);
               if( input_buffer )
               {
                  bOk = CryptHashData(hHash,input_buffer,input_size, 0);
                  xpp[4]->UnlockStr();
               }
               return bOk;
            }
            case OT4XB_HASH_FLAGS_INPUT_FILENAME :
            {
               return process_input_file( xpp  , dwFlags  , hHash );
            }
            case OT4XB_HASH_FLAGS_INPUT_HFILE    :
            {
               return process_input_file( xpp  , dwFlags  , hHash );
            }
         }
         return FALSE;
      }
      // ---------------------------------------------------------------------------------
      // hash(1 pt , 2 Self , 3 dwAlgorithm , 4 p1 input , 5 p2 nFlags , 6 p3 qwOffsetFrom , 7 dwBytes , 8 granularity )
      void hash( XppParamList pl )
      {
         TXppParamList xpp(pl,5);
         DWORD dwFlags     = xpp[5]->GetDWord();
         DWORD dwAlgorithm = xpp[3]->GetDWord();
         HCRYPTPROV hProv = 0;
         HCRYPTHASH hHash = 0;
         DWORD dwProviderType = 0;

         switch( dwAlgorithm )
         {
            case CALG_MD2     : { dwProviderType = PROV_RSA_FULL; break; }
            case CALG_MD4     : { dwProviderType = PROV_RSA_FULL; break; }
            case CALG_MD5     : { dwProviderType = PROV_RSA_FULL; break; }
            case CALG_SHA1    : { dwProviderType = PROV_RSA_FULL; break; }
            case CALG_SHA_256 : { dwProviderType = PROV_RSA_AES; break;  }
            case CALG_SHA_384 : { dwProviderType = PROV_RSA_AES; break;  }
            case CALG_SHA_512 : { dwProviderType = PROV_RSA_AES; break;  }
            default: { return; }
         }


         if( CryptAcquireContext(&hProv,0,0,dwProviderType,CRYPT_VERIFYCONTEXT) )
         {
            if( CryptCreateHash(hProv, dwAlgorithm , 0, 0, &hHash) )
            {
               if( process_input_bufer(xpp,dwFlags,hHash) )
               {
                  DWORD hash_cb = 0;
                  DWORD cb = sizeof(DWORD);
                  if( CryptGetHashParam(hHash, HP_HASHSIZE, (LPBYTE) &hash_cb, &cb,0 ) )
                  {
                     LPBYTE hash_buffer = (LPBYTE) _xgrab( hash_cb + 1 );
                     if( CryptGetHashParam(hHash, HP_HASHVAL, hash_buffer, &hash_cb, 0) )
                     {
                        if( (dwFlags & 0x0F) == OT4XB_HASH_FLAGS_OUTPUT_HEX  )
                        {
                           LPBYTE p = hash_buffer;
                           cb       = hash_cb;
                           hash_buffer = (LPBYTE) pBin2Hex(p,cb);
                           hash_cb = cb <<  1;
                           _xfree( (void*) p );
                           p = 0;
                        }
                        xpp[0]->PutStrLen( (LPSTR) hash_buffer, hash_cb );
                     }
                     _xfree( (void*) hash_buffer );
                  }
               }
               CryptDestroyHash(hHash); hHash = 0;
            }
            CryptReleaseContext(hProv, 0); hProv = 0;
         }
      }
      // ---------------------------------------------------------------------------------

      // ---------------------------------------------------------------------------------
      END_NAMESPACE() // ot4xb_hash_ns
// -----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_( OT4XB_HASH )
{
   XppFuncType fp = _mk_ptr_( XppFuncType, _parLong(pl,1,0) , 0 );
   if( fp && ( _partype(pl,2) & XPP_OBJECT) )
   {
      (*fp)(pl);
      return;
   }
   ContainerHandle conco = _conClsObj("OT4XB_HASH");
   if( conco == NULLCONTAINER )
   {
      TXbClass * pc = new TXbClass;pc->ClassName("OT4XB_HASH");
      pc->EXPORTED();
      pc->Var( "__m_v0" );
      pc->Var( "__m_v1" );
      // -----
	  //...(  p1 input , 5 p2 nFlags , 6 p3 qwOffsetFrom , 7 dwBytes , 8 granularity )
	  // hash(1 pt , 2 Self , 3 dwAlgorithm , 4 p1 input , 5 p2 nFlags , 6 p3 qwOffsetFrom , 7 dwBytes , 8 granularity )
      pc->ClassMethod_cbbs("sha"   , "{|s,p1,p2,p3,p4,p5| ot4xb_hash(%i,s,%i,@p1,@p2,@p3,@p4,@p5) }" , ot4xb_hash_ns::hash, CALG_SHA     );
      pc->ClassMethod_cbbs("sha1"  , "{|s,p1,p2,p3,p4,p5| ot4xb_hash(%i,s,%i,@p1,@p2,@p3,@p4,@p5) }" , ot4xb_hash_ns::hash, CALG_SHA1    );
      pc->ClassMethod_cbbs("sha256", "{|s,p1,p2,p3,p4,p5| ot4xb_hash(%i,s,%i,@p1,@p2,@p3,@p4,@p5) }" , ot4xb_hash_ns::hash, CALG_SHA_256 );
      pc->ClassMethod_cbbs("sha384", "{|s,p1,p2,p3,p4,p5| ot4xb_hash(%i,s,%i,@p1,@p2,@p3,@p4,@p5) }" , ot4xb_hash_ns::hash, CALG_SHA_384 );
      pc->ClassMethod_cbbs("sha512", "{|s,p1,p2,p3,p4,p5| ot4xb_hash(%i,s,%i,@p1,@p2,@p3,@p4,@p5) }" , ot4xb_hash_ns::hash, CALG_SHA_512 );
      pc->ClassMethod_cbbs("md2"   , "{|s,p1,p2,p3,p4,p5| ot4xb_hash(%i,s,%i,@p1,@p2,@p3,@p4,@p5) }" , ot4xb_hash_ns::hash, CALG_MD2     );
      pc->ClassMethod_cbbs("md4"   , "{|s,p1,p2,p3,p4,p5| ot4xb_hash(%i,s,%i,@p1,@p2,@p3,@p4,@p5) }" , ot4xb_hash_ns::hash, CALG_MD4     );
      pc->ClassMethod_cbbs("md5"   , "{|s,p1,p2,p3,p4,p5| ot4xb_hash(%i,s,%i,@p1,@p2,@p3,@p4,@p5) }" , ot4xb_hash_ns::hash, CALG_MD5     );
      // -----      
      ///////////////////////////////////pc->ClassMethod_cbbs("hmac_sign", "{|s,cSpec,cStr,cPwd,p4,p5| ot4xb_hash(%i,s,__vlower(cSpec,''),%i,@p1,@p2,@p3,@p4,@p5) }" , ot4xb_hash_ns::hash, CALG_MD5     );      

      // -----
      conco = pc->Create();
      delete pc;
      if( conco == NULLCONTAINER )
      {
         _ret(pl);
         return;
      }
   }
   _conReturn(pl,conco);
   _conRelease(conco);
}
// -----------------------------------------------------------------------------------------------------------------
