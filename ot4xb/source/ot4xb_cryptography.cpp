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

/*{{begin-note-id}}*/
/*{{note-id: ot4xb-hash-methods
            | title_: OT4XB_HASH method arguments and flags }}*/
/*{{|:
   Every OT4XB_HASH hash method is a class method with the same argument list, called directly on the class
   object with no instance needed:

   `OT4XB_HASH():<method>( uInput, [nFlags := 0], [nOffset], [nBytes], [nGranularity] ) -> cHash`

   uInput is the data to hash. What it holds, and how the hash value is returned, is selected with nFlags, a
   combination (nOr) of:

   - 0x00000000 : uInput is a Character value and its bytes are hashed as-is. Default input mode.
   - 0x00000010 : uInput is a file name. The file is opened read-only, hashed and closed internally.
   - 0x00000020 : uInput is an already open Windows file handle, given as a Numeric. The handle is left open
                  and hashing starts at the current file position.
   - 0x00000100 : hashing starts at file position nOffset, in bytes from the beginning of the file.
   - 0x00000200 : at most nBytes bytes are hashed. Without this flag the file is hashed up to the end.
   - 0x00001000 : the original file position is restored after hashing an already open handle.
   - 0x00010000 : nGranularity sets the file read buffer size in bytes, clamped between 64 KB (the default)
                  and 8 MB.
   - 0x00000000 : the hash is returned as an uppercase hexadecimal Character string. Default output mode.
   - 0x00000001 : the hash is returned as its raw binary bytes in a Character string.

   nOffset, nBytes and nGranularity are read only when the matching flag is set, and they only apply to file
   input. On any failure - the file cannot be opened, the handle is not usable, a read fails, or the
   CryptoAPI reports an error - the method returns NIL instead of a Character value.
}}*/
/*{{end-note-id}}*/

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
            max_bytes.QuadPart = xpp[7]->GetQWord();
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
/*{{begin-class}}*/
/*{{class-name_: OT4XB_HASH
            | _slug_: ot4xb_hash
            | class-function: OT4XB_HASH
            | category: crypto/hash
            | desc: Hashing class over the Windows CryptoAPI. All hash methods (md2, md4, md5, sha, sha1, sha256,
              sha384, sha512) are class methods, called directly on the class object with no instance needed, for
              example OT4XB_HASH():sha256( cData ). Each method hashes a Character value, a file given by name, or
              an open file handle, selected with nFlags, and returns the hash value as a hex Character string, or
              as raw binary bytes when output flag 0x01 is set. For file input, nFlags can also select a start
              offset, a maximum byte count and the read buffer size. sha and sha1 are the same algorithm (SHA-1).
   | _kw_: OT4XB_HASH, Class
   }}*/
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
      /*{{|:**BEGIN CLASS  OT4XB_HASH** }}*/
      pc->EXPORTED();
      /*{{|ivar_: - VAR __m_v0
               | desc_: Internal variable; no method of the class uses it.
               | note: Internal state, not meant to be manipulated outside the class.
      }}*/
      pc->Var( "__m_v0" );
      /*{{|ivar_: - VAR __m_v1
               | desc_: Internal variable; no method of the class uses it.
               | note: Internal state, not meant to be manipulated outside the class.
      }}*/
      pc->Var( "__m_v1" );
      // -----
	  //...(  p1 input , 5 p2 nFlags , 6 p3 qwOffsetFrom , 7 dwBytes , 8 granularity )
	  // hash(1 pt , 2 Self , 3 dwAlgorithm , 4 p1 input , 5 p2 nFlags , 6 p3 qwOffsetFrom , 7 dwBytes , 8 granularity )
      /*{{|class-method_: - CLASS METHOD sha( uInput, [nFlags], [nOffset], [nBytes], [nGranularity] )
               | return: cHash / NIL
               | desc_: SHA-1 hash of uInput: 40 hexadecimal characters, or 20 raw bytes with output flag 0x01.
                 ::sha and ::sha1 run the same algorithm.
      }}*/
      pc->ClassMethod_cbbs("sha"   , "{|s,p1,p2,p3,p4,p5| ot4xb_hash(%i,s,%i,@p1,@p2,@p3,@p4,@p5) }" , ot4xb_hash_ns::hash, CALG_SHA     );
      /*{{|class-method_: - CLASS METHOD sha1( uInput, [nFlags], [nOffset], [nBytes], [nGranularity] )
               | return: cHash / NIL
               | desc_: SHA-1 hash of uInput: 40 hexadecimal characters, or 20 raw bytes with output flag 0x01.
                 Same algorithm as ::sha.
      }}*/
      pc->ClassMethod_cbbs("sha1"  , "{|s,p1,p2,p3,p4,p5| ot4xb_hash(%i,s,%i,@p1,@p2,@p3,@p4,@p5) }" , ot4xb_hash_ns::hash, CALG_SHA1    );
      /*{{|class-method_: - CLASS METHOD sha256( uInput, [nFlags], [nOffset], [nBytes], [nGranularity] )
               | return: cHash / NIL
               | desc_: SHA-256 hash of uInput: 64 hexadecimal characters, or 32 raw bytes with output flag 0x01.
      }}*/
      pc->ClassMethod_cbbs("sha256", "{|s,p1,p2,p3,p4,p5| ot4xb_hash(%i,s,%i,@p1,@p2,@p3,@p4,@p5) }" , ot4xb_hash_ns::hash, CALG_SHA_256 );
      /*{{|class-method_: - CLASS METHOD sha384( uInput, [nFlags], [nOffset], [nBytes], [nGranularity] )
               | return: cHash / NIL
               | desc_: SHA-384 hash of uInput: 96 hexadecimal characters, or 48 raw bytes with output flag 0x01.
      }}*/
      pc->ClassMethod_cbbs("sha384", "{|s,p1,p2,p3,p4,p5| ot4xb_hash(%i,s,%i,@p1,@p2,@p3,@p4,@p5) }" , ot4xb_hash_ns::hash, CALG_SHA_384 );
      /*{{|class-method_: - CLASS METHOD sha512( uInput, [nFlags], [nOffset], [nBytes], [nGranularity] )
               | return: cHash / NIL
               | desc_: SHA-512 hash of uInput: 128 hexadecimal characters, or 64 raw bytes with output flag 0x01.
      }}*/
      pc->ClassMethod_cbbs("sha512", "{|s,p1,p2,p3,p4,p5| ot4xb_hash(%i,s,%i,@p1,@p2,@p3,@p4,@p5) }" , ot4xb_hash_ns::hash, CALG_SHA_512 );
      /*{{|class-method_: - CLASS METHOD md2( uInput, [nFlags], [nOffset], [nBytes], [nGranularity] )
               | return: cHash / NIL
               | desc_: MD2 hash of uInput: 32 hexadecimal characters, or 16 raw bytes with output flag 0x01.
      }}*/
      pc->ClassMethod_cbbs("md2"   , "{|s,p1,p2,p3,p4,p5| ot4xb_hash(%i,s,%i,@p1,@p2,@p3,@p4,@p5) }" , ot4xb_hash_ns::hash, CALG_MD2     );
      /*{{|class-method_: - CLASS METHOD md4( uInput, [nFlags], [nOffset], [nBytes], [nGranularity] )
               | return: cHash / NIL
               | desc_: MD4 hash of uInput: 32 hexadecimal characters, or 16 raw bytes with output flag 0x01.
      }}*/
      pc->ClassMethod_cbbs("md4"   , "{|s,p1,p2,p3,p4,p5| ot4xb_hash(%i,s,%i,@p1,@p2,@p3,@p4,@p5) }" , ot4xb_hash_ns::hash, CALG_MD4     );
      /*{{|class-method_: - CLASS METHOD md5( uInput, [nFlags], [nOffset], [nBytes], [nGranularity] )
               | return: cHash / NIL
               | desc_: MD5 hash of uInput: 32 hexadecimal characters, or 16 raw bytes with output flag 0x01.
      }}*/
      /*{{|:**END CLASS** }}*/
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
/*{{include-note-id: ot4xb-hash-methods}}*/
/*{{include-note-id: hash-flags}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
