//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
#include <bcrypt.h>
// -----------------------------------------------------------------------------------------------------------------
BEGIN_NAMESPACE( ot4xb_cng_ns )
//----------------------------------------------------------------------------------------------------------------------
typedef NTSTATUS( __stdcall * ft_BCryptOpenAlgorithmProvider       )(BCRYPT_ALG_HANDLE*,LPCWSTR,LPCWSTR,ULONG);
typedef NTSTATUS( __stdcall * ft_BCryptEnumAlgorithms              )(ULONG,ULONG*,BCRYPT_ALGORITHM_IDENTIFIER**,ULONG);
typedef NTSTATUS( __stdcall * ft_BCryptEnumProviders               )(LPCWSTR,ULONG*,BCRYPT_PROVIDER_NAME**,ULONG);
typedef NTSTATUS( __stdcall * ft_BCryptGetProperty                 )(BCRYPT_HANDLE,LPCWSTR,PUCHAR,ULONG,ULONG*,ULONG);
typedef NTSTATUS( __stdcall * ft_BCryptSetProperty                 )(BCRYPT_HANDLE,LPCWSTR,PUCHAR,ULONG,ULONG);
typedef NTSTATUS( __stdcall * ft_BCryptCloseAlgorithmProvider      )(BCRYPT_ALG_HANDLE,ULONG);
typedef VOID    ( __stdcall * ft_BCryptFreeBuffer                  )(PVOID);
typedef NTSTATUS( __stdcall * ft_BCryptGenerateSymmetricKey        )(BCRYPT_ALG_HANDLE,BCRYPT_KEY_HANDLE*,PUCHAR,ULONG,PUCHAR,ULONG,ULONG);
typedef NTSTATUS( __stdcall * ft_BCryptGenerateKeyPair             )(BCRYPT_ALG_HANDLE,BCRYPT_KEY_HANDLE*,ULONG,ULONG);
typedef NTSTATUS( __stdcall * ft_BCryptEncrypt                     )(BCRYPT_KEY_HANDLE,PUCHAR,ULONG,VOID*,PUCHAR,ULONG,PUCHAR,ULONG,ULONG*,ULONG);
typedef NTSTATUS( __stdcall * ft_BCryptDecrypt                     )(BCRYPT_KEY_HANDLE,PUCHAR,ULONG,VOID*,PUCHAR,ULONG,PUCHAR,ULONG,ULONG*,ULONG);
typedef NTSTATUS( __stdcall * ft_BCryptExportKey                   )(BCRYPT_KEY_HANDLE,BCRYPT_KEY_HANDLE,LPCWSTR,PUCHAR,ULONG,ULONG*,ULONG);
typedef NTSTATUS( __stdcall * ft_BCryptImportKey                   )(BCRYPT_ALG_HANDLE,BCRYPT_KEY_HANDLE,LPCWSTR,BCRYPT_KEY_HANDLE*,PUCHAR,ULONG,PUCHAR,ULONG,ULONG);
typedef NTSTATUS( __stdcall * ft_BCryptImportKeyPair               )(BCRYPT_ALG_HANDLE,BCRYPT_KEY_HANDLE,LPCWSTR,BCRYPT_KEY_HANDLE*,PUCHAR,ULONG,ULONG);
typedef NTSTATUS( __stdcall * ft_BCryptDuplicateKey                )(BCRYPT_KEY_HANDLE,BCRYPT_KEY_HANDLE*,PUCHAR,ULONG,ULONG);
typedef NTSTATUS( __stdcall * ft_BCryptFinalizeKeyPair             )(BCRYPT_KEY_HANDLE,ULONG);
typedef NTSTATUS( __stdcall * ft_BCryptDestroyKey                  )(BCRYPT_KEY_HANDLE);
typedef NTSTATUS( __stdcall * ft_BCryptDestroySecret               )(BCRYPT_SECRET_HANDLE);
typedef NTSTATUS( __stdcall * ft_BCryptSignHash                    )(BCRYPT_KEY_HANDLE,VOID*,PUCHAR,ULONG,PUCHAR,ULONG,ULONG*,ULONG);
typedef NTSTATUS( __stdcall * ft_BCryptVerifySignature             )(BCRYPT_KEY_HANDLE,VOID*,PUCHAR,ULONG,PUCHAR,ULONG,ULONG);
typedef NTSTATUS( __stdcall * ft_BCryptSecretAgreement             )(BCRYPT_KEY_HANDLE);
typedef NTSTATUS( __stdcall * ft_BCryptDeriveKey                   )(BCRYPT_SECRET_HANDLE,LPCWSTR,BCryptBufferDesc*,PUCHAR,ULONG,ULONG*,ULONG);
typedef NTSTATUS( __stdcall * ft_BCryptCreateHash                  )(BCRYPT_ALG_HANDLE,BCRYPT_HASH_HANDLE*,PUCHAR,ULONG,PUCHAR,ULONG,ULONG);
typedef NTSTATUS( __stdcall * ft_BCryptHashData                    )(BCRYPT_HASH_HANDLE,PUCHAR,ULONG,ULONG);
typedef NTSTATUS( __stdcall * ft_BCryptFinishHash                  )(BCRYPT_HASH_HANDLE,PUCHAR,ULONG,ULONG);
typedef NTSTATUS( __stdcall * ft_BCryptDuplicateHash               )(BCRYPT_HASH_HANDLE,BCRYPT_HASH_HANDLE*,PUCHAR,ULONG,ULONG);
typedef NTSTATUS( __stdcall * ft_BCryptDestroyHash                 )(BCRYPT_HASH_HANDLE);
typedef NTSTATUS( __stdcall * ft_BCryptGenRandom                   )(BCRYPT_ALG_HANDLE,PUCHAR,ULONG,ULONG);
typedef NTSTATUS( __stdcall * ft_BCryptDeriveKeyCapi               )(BCRYPT_HASH_HANDLE,BCRYPT_ALG_HANDLE,PUCHAR,ULONG,ULONG);
typedef NTSTATUS( __stdcall * ft_BCryptDeriveKeyPBKDF2             )(BCRYPT_ALG_HANDLE,PUCHAR,ULONG,PUCHAR,ULONG,ULONGLONG,PUCHAR,ULONG,ULONG);
typedef NTSTATUS( __stdcall * ft_BCryptRegisterConfigChangeNotify  )(HANDLE*);
typedef NTSTATUS( __stdcall * ft_BCryptUnregisterConfigChangeNotify)(HANDLE);
typedef NTSTATUS( __stdcall * ft_BCryptResolveProviders            )(LPCWSTR,ULONG,LPCWSTR,LPCWSTR,ULONG,ULONG,ULONG*,PCRYPT_PROVIDER_REFS*);
typedef NTSTATUS( __stdcall * ft_BCryptGetFipsAlgorithmMode        )(BOOLEAN*);
// -----------------------------------------------------------------------------------------------------------------
static ft_BCryptOpenAlgorithmProvider             BCryptOpenAlgorithmProvider        = 0;
static ft_BCryptEnumAlgorithms                    BCryptEnumAlgorithms               = 0;
static ft_BCryptEnumProviders                     BCryptEnumProviders                = 0;
static ft_BCryptGetProperty                       BCryptGetProperty                  = 0;
static ft_BCryptSetProperty                       BCryptSetProperty                  = 0;
static ft_BCryptCloseAlgorithmProvider            BCryptCloseAlgorithmProvider       = 0;
static ft_BCryptFreeBuffer                        BCryptFreeBuffer                   = 0;
static ft_BCryptGenerateSymmetricKey              BCryptGenerateSymmetricKey         = 0;
static ft_BCryptGenerateKeyPair                   BCryptGenerateKeyPair              = 0;
static ft_BCryptEncrypt                           BCryptEncrypt                      = 0;
static ft_BCryptDecrypt                           BCryptDecrypt                      = 0;
static ft_BCryptExportKey                         BCryptExportKey                    = 0;
static ft_BCryptImportKey                         BCryptImportKey                    = 0;
static ft_BCryptImportKeyPair                     BCryptImportKeyPair                = 0;
static ft_BCryptDuplicateKey                      BCryptDuplicateKey                 = 0;
static ft_BCryptFinalizeKeyPair                   BCryptFinalizeKeyPair              = 0;
static ft_BCryptDestroyKey                        BCryptDestroyKey                   = 0;
static ft_BCryptDestroySecret                     BCryptDestroySecret                = 0;
static ft_BCryptSignHash                          BCryptSignHash                     = 0;
static ft_BCryptVerifySignature                   BCryptVerifySignature              = 0;
static ft_BCryptSecretAgreement                   BCryptSecretAgreement              = 0;
static ft_BCryptDeriveKey                         BCryptDeriveKey                    = 0;
static ft_BCryptCreateHash                        BCryptCreateHash                   = 0;
static ft_BCryptHashData                          BCryptHashData                     = 0;
static ft_BCryptFinishHash                        BCryptFinishHash                   = 0;
static ft_BCryptDuplicateHash                     BCryptDuplicateHash                = 0;
static ft_BCryptDestroyHash                       BCryptDestroyHash                  = 0;
static ft_BCryptGenRandom                         BCryptGenRandom                    = 0;
static ft_BCryptDeriveKeyCapi                     BCryptDeriveKeyCapi                = 0;
static ft_BCryptDeriveKeyPBKDF2                   BCryptDeriveKeyPBKDF2              = 0;
static ft_BCryptRegisterConfigChangeNotify        BCryptRegisterConfigChangeNotify   = 0;
static ft_BCryptUnregisterConfigChangeNotify      BCryptUnregisterConfigChangeNotify = 0;
static ft_BCryptResolveProviders                  BCryptResolveProviders             = 0;
static ft_BCryptGetFipsAlgorithmMode              BCryptGetFipsAlgorithmMode         = 0;
//----------------------------------------------------------------------------------------------------------------------
HMODULE init_module()
{

   static BOOL    bInit = 0;
   static HMODULE hDll  = 0;
   if( !bInit )
   {
      hDll = LoadLibrary("ncrypt");
      if( hDll )
      {
         BCryptOpenAlgorithmProvider          = ( ft_BCryptOpenAlgorithmProvider        ) GetProcAddress( hDll , "BCryptOpenAlgorithmProvider"        );
         BCryptEnumAlgorithms                 = ( ft_BCryptEnumAlgorithms               ) GetProcAddress( hDll , "BCryptEnumAlgorithms"               );
         BCryptEnumProviders                  = ( ft_BCryptEnumProviders                ) GetProcAddress( hDll , "BCryptEnumProviders"                );
         BCryptGetProperty                    = ( ft_BCryptGetProperty                  ) GetProcAddress( hDll , "BCryptGetProperty"                  );
         BCryptSetProperty                    = ( ft_BCryptSetProperty                  ) GetProcAddress( hDll , "BCryptSetProperty"                  );
         BCryptCloseAlgorithmProvider         = ( ft_BCryptCloseAlgorithmProvider       ) GetProcAddress( hDll , "BCryptCloseAlgorithmProvider"       );
         BCryptFreeBuffer                     = ( ft_BCryptFreeBuffer                   ) GetProcAddress( hDll , "BCryptFreeBuffer"                   );
         BCryptGenerateSymmetricKey           = ( ft_BCryptGenerateSymmetricKey         ) GetProcAddress( hDll , "BCryptGenerateSymmetricKey"         );
         BCryptGenerateKeyPair                = ( ft_BCryptGenerateKeyPair              ) GetProcAddress( hDll , "BCryptGenerateKeyPair"              );
         BCryptEncrypt                        = ( ft_BCryptEncrypt                      ) GetProcAddress( hDll , "BCryptEncrypt"                      );
         BCryptDecrypt                        = ( ft_BCryptDecrypt                      ) GetProcAddress( hDll , "BCryptDecrypt"                      );
         BCryptExportKey                      = ( ft_BCryptExportKey                    ) GetProcAddress( hDll , "BCryptExportKey"                    );
         BCryptImportKey                      = ( ft_BCryptImportKey                    ) GetProcAddress( hDll , "BCryptImportKey"                    );
         BCryptImportKeyPair                  = ( ft_BCryptImportKeyPair                ) GetProcAddress( hDll , "BCryptImportKeyPair"                );
         BCryptDuplicateKey                   = ( ft_BCryptDuplicateKey                 ) GetProcAddress( hDll , "BCryptDuplicateKey"                 );
         BCryptFinalizeKeyPair                = ( ft_BCryptFinalizeKeyPair              ) GetProcAddress( hDll , "BCryptFinalizeKeyPair"              );
         BCryptDestroyKey                     = ( ft_BCryptDestroyKey                   ) GetProcAddress( hDll , "BCryptDestroyKey"                   );
         BCryptDestroySecret                  = ( ft_BCryptDestroySecret                ) GetProcAddress( hDll , "BCryptDestroySecret"                );
         BCryptSignHash                       = ( ft_BCryptSignHash                     ) GetProcAddress( hDll , "BCryptSignHash"                     );
         BCryptVerifySignature                = ( ft_BCryptVerifySignature              ) GetProcAddress( hDll , "BCryptVerifySignature"              );
         BCryptSecretAgreement                = ( ft_BCryptSecretAgreement              ) GetProcAddress( hDll , "BCryptSecretAgreement"              );
         BCryptDeriveKey                      = ( ft_BCryptDeriveKey                    ) GetProcAddress( hDll , "BCryptDeriveKey"                    );
         BCryptCreateHash                     = ( ft_BCryptCreateHash                   ) GetProcAddress( hDll , "BCryptCreateHash"                   );
         BCryptHashData                       = ( ft_BCryptHashData                     ) GetProcAddress( hDll , "BCryptHashData"                     );
         BCryptFinishHash                     = ( ft_BCryptFinishHash                   ) GetProcAddress( hDll , "BCryptFinishHash"                   );
         BCryptDuplicateHash                  = ( ft_BCryptDuplicateHash                ) GetProcAddress( hDll , "BCryptDuplicateHash"                );
         BCryptDestroyHash                    = ( ft_BCryptDestroyHash                  ) GetProcAddress( hDll , "BCryptDestroyHash"                  );
         BCryptGenRandom                      = ( ft_BCryptGenRandom                    ) GetProcAddress( hDll , "BCryptGenRandom"                    );
         BCryptDeriveKeyCapi                  = ( ft_BCryptDeriveKeyCapi                ) GetProcAddress( hDll , "BCryptDeriveKeyCapi"                );
         BCryptDeriveKeyPBKDF2                = ( ft_BCryptDeriveKeyPBKDF2              ) GetProcAddress( hDll , "BCryptDeriveKeyPBKDF2"              );
         BCryptRegisterConfigChangeNotify     = ( ft_BCryptRegisterConfigChangeNotify   ) GetProcAddress( hDll , "BCryptRegisterConfigChangeNotify"   );
         BCryptUnregisterConfigChangeNotify   = ( ft_BCryptUnregisterConfigChangeNotify ) GetProcAddress( hDll , "BCryptUnregisterConfigChangeNotify" );
         BCryptResolveProviders               = ( ft_BCryptResolveProviders             ) GetProcAddress( hDll , "BCryptResolveProviders"             );
         BCryptGetFipsAlgorithmMode           = ( ft_BCryptGetFipsAlgorithmMode         ) GetProcAddress( hDll , "BCryptGetFipsAlgorithmMode"         );
      }
      bInit = TRUE;
   }
   return hDll;
}
// -----------------------------------------------------------------------------------------------------------------
class cng_helper_t : public T_ot4xb_base
{
   public:
   // ------------------------------            
   enum encode_e
   {
      e_binary    = 0x1000,
      e_hex ,
      e_base64 ,
      e_encode_default = 0      
   };   
   // ------------------------------         
   class buffer_t
   {
      public: 
      // ------------------------------      
      DWORD  m_cb;
      void*  m_p;
      // ------------------------------      
      buffer_t()
      {
         m_cb = 0; m_p = 0;
      };
      // ------------------------------
      ~buffer_t()
      {
         clear();
      };
      // ------------------------------      
      void* detach( DWORD* pcb = 0 )
      {
         void* p  = m_p;
         if( pcb ){ *pcb = m_cb; }         
         m_p = 0; m_cb = 0;
         return p;
      }
      // ------------------------------            
      void clear()
      {
         void* p = detach();
         if( p ){ _xfree(p); }
      }
      // ------------------------------
      void put( void* p , DWORD cb , BOOL bDup = FALSE )
      {
         clear();
         
         if( p && cb )
         {
            m_cb = cb;
            if( bDup )
            {
               m_p = _bdup((LPBYTE) p , cb );
            }
            else
            {
               m_p = p;
            }            
         }
      }
      // ------------------------------            
		void* mem_dup(size_t * pcb)
		{
			if (pcb) { *pcb = 0; }
			if (m_p && m_cb)
			{
				LPBYTE p = _bdup((LPBYTE)m_p, m_cb);
				if (p)
				{
					if (pcb) { *pcb = m_cb; }
					return (void*) p;
				}
			}
			return 0;
		}
		// ------------------------------            
      void alloc(DWORD cb)
      {
         clear();
         if( cb )
         {
            m_cb = cb;
            m_p  = _xgrab( cb);
         }
      }
      // ------------------------------                  
      void set_bytes( ContainerHandle con , encode_e enc = e_binary , BOOL bRelease = FALSE )
      {
         clear();
         if( con )
         {
            if( _conCheckType(con,XPP_CHARACTER) )
            {
               DWORD cbs = 0;
               LPSTR ps  = 0;
               if( _conRLockC(con,&ps,&cbs) == 0 )
               {
                  switch( enc )
                  {
                     case e_binary :
                     {
                        m_p  = _xgrab( cbs + 4 );
                        m_cb = cbs;
                        _bcopy((LPBYTE)m_p,(LPBYTE) ps , cbs );
                        break;
                     }
                     case e_hex:
                     {
                        m_p = (LPBYTE) pHex2Bin( ps , &m_cb);
                        break;
                     } 
                     case e_base64:
                     {
                        int n =  ot4xb_base64_decode_required_length(cbs);
                        if( n > 0 )
                        {
                           m_p = _xgrab( (DWORD) ( n + 4 ) );
                           if( ot4xb_base64_decode(ps,(int)cbs,(LPBYTE)m_p,&n) )
                           {
                              m_cb = (DWORD) n;
                           }
                           else
                           {
                              clear();
                           }
                        }
                        break;
                     }
                  }
                  _conUnlockC(con);
               }
            }
            if( bRelease )
            {
               _conRelease(con);
            }
         }
      };      
      // ------------------------------                        
      void get_bytes( ContainerHandle con , encode_e enc = e_binary )
      {
         if( con )
         {
            if(!m_p )
            {
               _conPut( con,NULLCONTAINER);
               return;
            }
            if(!m_cb )
            {
               _conPutC(con,"");
               return;
            }
            switch( enc )
            {
               case e_binary :
               {
                  _conPutCL(con,(LPSTR) m_p, m_cb);
                  return;
               }
               case e_hex:
               {
                  LPSTR pHex = pBin2Hex((LPBYTE) m_p , m_cb);
                  _conPutC( con , pHex );
                  _xfree( (void*) pHex);
                  return;
               } 
               case e_base64:
               {
                  int n =  ot4xb_base64_encode_required_length(m_cb);
                  if( n > 0 )
                  {
                     LPSTR pBase64 = (LPSTR) _xgrab( (DWORD) ( n + 16 ) );
                     if( ot4xb_base64_encode((LPBYTE) m_p,(int) m_cb,pBase64,&n,2) ) // 2 == ATL_BASE64_FLAG_NOCRLF
                     {
                        _conPutC( con , pBase64 );
                     }
                     else
                     {
                        _conPutC( con , "" );                     
                     }
                     _xfree( (void*) pBase64);                     
                     return;
                  }
                  break;
               }
            }
            _conPut( con,NULLCONTAINER);
         }
      };
      // ------------------------------          
   };
   // ------------------------------                   
   buffer_t  m_out;
   buffer_t  m_in;   
   encode_e  m_encode_input;   
   encode_e  m_encode_output;      
   // ------------------------------
   void __encode_prop_from_flags( ContainerHandle con , encode_e  & e , LPSTR k ) 
   {
      LPSTR p = 0;
      if( k && con ) 
      {
         p = _conMCallLpstr(con,"get_prop",k);
         if( p )
         {
            if( lstrcmpi(p,"bin"   ) == 0 ){  e = e_binary ; goto cleanup; }
            if( lstrcmpi(p,"hex"   ) == 0 ){  e = e_hex    ; goto cleanup; }
            if( lstrcmpi(p,"base64") == 0 ){  e = e_base64 ; goto cleanup; }
            if( lstrcmpi(p,"b64"   ) == 0 ){  e = e_base64 ; goto cleanup; }
         }
      }
      cleanup: ;
      if( p ) _xfree( (void*) p );
   }
   
   // ------------------------------                         
   cng_helper_t( ContainerHandle con_in , ContainerHandle con_flags )
   {
      m_encode_input   = e_binary;
      m_encode_output  = e_binary;
      if( con_flags )
      {
         if(  _conCheckType( con_flags , XPP_OBJECT ) )
         {
            __encode_prop_from_flags( con_flags, m_encode_input  , "encode_input"  );
            __encode_prop_from_flags( con_flags, m_encode_output , "encode_output" );
         }
      }
      if( _conCheckType(con_in ,XPP_CHARACTER) )
      {
         m_in.set_bytes( con_in ,  m_encode_input , FALSE );
      }      
      
   };
   // ------------------------------                
   ~cng_helper_t()
   {
      m_out.clear();
      m_in.clear();
   };   
   // ------------------------------                   
};
// -----------------------------------------------------------------------------------------------------------------
class aes_helper_t : public cng_helper_t
{
   public:

   enum mode_e
   {
      e_mode_ecb = 0x1000 ,
      e_mode_cbc ,
      e_mode_default = 0
   };
   // ------------------------------
   buffer_t  m_chaining_mode;
   buffer_t  m_iv_bytes;
   buffer_t  m_key_bytes;
   buffer_t  m_key_object;
   mode_e    m_mode;
   encode_e  m_encode_iv;
   encode_e  m_encode_key;
   BOOL      m_aes_block_padding;
   // ------------------------------
   LONG m_status;
   // ------------------------------
   BCRYPT_ALG_HANDLE m_hAlg;
   BCRYPT_KEY_HANDLE m_hKey;
   // ------------------------------
   aes_helper_t( ContainerHandle con_in , ContainerHandle con_flags ) : cng_helper_t( con_in ,con_flags )
   {
      m_mode = e_mode_default;
      m_encode_iv      = e_binary;
      m_encode_key     = e_binary;
      m_aes_block_padding  = FALSE;
      m_hAlg = 0;
      m_hKey = 0;
      m_status = 0;
      if( con_flags )
      {
         if(  _conCheckType( con_flags , XPP_OBJECT ) )
         {
            LPSTR p = _conMCallLpstr(con_flags,"get_prop","mode");
            if( p )
            {
               if( lstrcmpi(p,"ebc") == 0 ){  m_mode = e_mode_ecb; }
               else if( lstrcmpi(p,"cbc") == 0 ){  m_mode = e_mode_cbc; }
               _xfree((void*)p); p = 0;
            }
            __encode_prop_from_flags( con_flags, m_encode_iv     , "encode_iv"     );
            __encode_prop_from_flags( con_flags, m_encode_key    , "encode_key"    );

            m_key_bytes.set_bytes( _conMCallCon(con_flags,"get_prop","key") ,  m_encode_key  , TRUE );
            m_iv_bytes.set_bytes(  _conMCallCon(con_flags,"get_prop","iv" ) ,  m_encode_iv   , TRUE );

            if( _conMCallBool(con_flags,"get_prop","aes_block_padding") )
            {
               m_aes_block_padding = TRUE;
            }

         }
      }

      if( m_mode == e_mode_default )
      {
         if( m_iv_bytes.m_p )
         {
            m_mode =  e_mode_cbc;
         }
         else
         {
            m_mode =  e_mode_ecb;
         }
      }
      switch( m_mode )
      {
         case e_mode_ecb :
         {
            m_iv_bytes.clear();
            m_chaining_mode.put( (void*)  BCRYPT_CHAIN_MODE_ECB , sizeof(BCRYPT_CHAIN_MODE_ECB ) , TRUE );
            break;
         }
         case e_mode_cbc :
         {
            m_chaining_mode.put( (void*)  BCRYPT_CHAIN_MODE_CBC , sizeof(BCRYPT_CHAIN_MODE_CBC) , TRUE );
            break;
         }
      }
   };
   // ------------------------------
   ~aes_helper_t()
   {
      if( m_hKey )
      {
         BCryptDestroyKey(m_hKey);
         m_hKey = 0;
      }
      if( m_hAlg )
      {
         BCryptCloseAlgorithmProvider(m_hAlg,0);
         m_hAlg = 0;
      }
      m_chaining_mode.clear();
      m_iv_bytes.clear();
      m_key_bytes.clear();
      m_key_object.clear();
   };
   // ------------------------------
   BOOL prepare_key()
   {

      if( m_hAlg ){ BCryptCloseAlgorithmProvider(m_hAlg,0); m_hAlg = 0; }
      if( m_hKey ){ BCryptDestroyKey(m_hKey); m_hKey = 0; }

      DWORD bytes_written = 0;
      if( !( (m_key_bytes.m_cb == 16) || (m_key_bytes.m_cb == 24) ||   (m_key_bytes.m_cb == 32) ) ){ return FALSE; }
      if( !m_chaining_mode.m_cb ){ return FALSE; }


      m_status = BCryptOpenAlgorithmProvider( &m_hAlg, BCRYPT_AES_ALGORITHM,0,0);
      if( m_status < 0 ){ return FALSE; }

      DWORD dw = 0;

      m_status = BCryptGetProperty(m_hAlg,BCRYPT_OBJECT_LENGTH, (LPBYTE) &dw , sizeof(DWORD), &bytes_written,0);
      if( m_status < 0 ){ return FALSE; }
      m_key_object.alloc(dw);

      if( m_iv_bytes.m_p )
      {
         m_status = BCryptGetProperty(m_hAlg,BCRYPT_BLOCK_LENGTH, (LPBYTE) &dw , sizeof(DWORD), &bytes_written,0);
         if( m_status < 0 ){ return FALSE; }
         if( dw > m_iv_bytes.m_cb ){ return FALSE; }
         m_iv_bytes.m_cb = dw;
      }

      m_status = BCryptSetProperty(m_hAlg,BCRYPT_CHAINING_MODE,(LPBYTE) m_chaining_mode.m_p, m_chaining_mode.m_cb, 0);
      if( m_status < 0 ){ return FALSE; }

      m_status = BCryptGenerateSymmetricKey(m_hAlg,&m_hKey,(LPBYTE) m_key_object.m_p , m_key_object.m_cb,(LPBYTE) m_key_bytes.m_p , m_key_bytes.m_cb,0);
      if( m_status < 0 ){ return FALSE; }

      return TRUE;
   };
   // ------------------------------
   BOOL encrypt(ContainerHandle con_out)
   {
      DWORD dwFlags = 0;

      if(  m_aes_block_padding )
      {
         dwFlags |= BCRYPT_BLOCK_PADDING;
      }

      DWORD cbo = 0;
      m_status = BCryptEncrypt(m_hKey,(LPBYTE)m_in.m_p,m_in.m_cb,0,(LPBYTE)m_iv_bytes.m_p,m_iv_bytes.m_cb,0,0,&cbo,dwFlags);
      if( m_status < 0 ){ return FALSE; }
      if( cbo  < 1 ){ return FALSE; }
      m_out.alloc(cbo);

      m_status = BCryptEncrypt(m_hKey,(LPBYTE)m_in.m_p,m_in.m_cb,0,(LPBYTE)m_iv_bytes.m_p,m_iv_bytes.m_cb,(LPBYTE)m_out.m_p,m_out.m_cb,&cbo,dwFlags);
      if( m_status < 0 ){ return FALSE; }
      if( cbo  < 1 ){ return FALSE; }
      if( cbo  > m_out.m_cb ){ return FALSE; }
      m_out.m_cb = cbo;

      m_out.get_bytes(con_out,m_encode_output);

      return TRUE;
   };
   // ------------------------------
   BOOL decrypt(ContainerHandle con_out)
   {
      DWORD dwFlags = 0;

      if(  m_aes_block_padding )
      {
         dwFlags |= BCRYPT_BLOCK_PADDING;
      }

      DWORD cbo = 0;
      m_status = BCryptDecrypt(m_hKey,(LPBYTE)m_in.m_p,m_in.m_cb,0,(LPBYTE)m_iv_bytes.m_p,m_iv_bytes.m_cb,0,0,&cbo,dwFlags);
      if( m_status < 0 ){ return FALSE; }
      if( cbo  < 1 ){ return FALSE; }
      m_out.alloc(cbo);

      m_status = BCryptDecrypt(m_hKey,(LPBYTE)m_in.m_p,m_in.m_cb,0,(LPBYTE)m_iv_bytes.m_p,m_iv_bytes.m_cb,(LPBYTE)m_out.m_p,m_out.m_cb,&cbo,dwFlags);
      if( m_status < 0 ){ return FALSE; }
      if( cbo  < 1 ){ return FALSE; }
      if( cbo  > m_out.m_cb ){ return FALSE; }
      m_out.m_cb = cbo;

      m_out.get_bytes(con_out,m_encode_output);

      return TRUE;
   };
   // ------------------------------
};
// -----------------------------------------------------------------------------------------------------------------
class rc4_helper_t : public cng_helper_t
{
	public:

	// ------------------------------
	class ctx_t : public T_ot4xb_base
	{
		public:
		DWORD  i;
		DWORD  j;
		BYTE   s[256];
		// -----------------------
		void init(BYTE* key, size_t cb)
		{
			DWORD  ii;
			DWORD  jj;
			BYTE   tmp;
			i = 0; j = 0;
			for (ii = 0; ii < 256; ii++){ s[ii] = ii & 0xFF; }
			for (ii = 0, jj = 0; ii < 256; ii++)
			{
				jj = (jj + s[ii] + key[ii % cb]) & 0xFF;
				tmp = s[ii]; s[ii] = s[jj];s[jj] = tmp;
			}
		};
		
	};
	// ------------------------------
	enum status_e
	{
		e_status_error   = -1,
		e_status_invalid =  0,
		e_status_init    =  1,
		e_status_done 
	};
	// ------------------------------
	ctx_t      m_ctx ;
	buffer_t   m_key_bytes;
	encode_e   m_encode_key;
	// ------------------------------
	status_e m_status = e_status_invalid ;
	// ------------------------------

	// ------------------------------
	rc4_helper_t(ContainerHandle con_in, ContainerHandle con_flags) : cng_helper_t(con_in, con_flags)
	{
		if (con_flags)
		{
			if (_conCheckType(con_flags, XPP_OBJECT) && m_in.m_cb )
			{
				__encode_prop_from_flags(con_flags, m_encode_key, "encode_key");
				m_key_bytes.set_bytes(_conMCallCon(con_flags, "get_prop", "key"), m_encode_key, TRUE);
				if( m_key_bytes.m_cb )
				{
					m_ctx.init((LPBYTE)m_key_bytes.m_p, m_key_bytes.m_cb);
					m_status = e_status_init;
					m_key_bytes.clear();
				}
			}
		}
	};
	// ------------------------------
	~rc4_helper_t()
	{
		m_key_bytes.clear();
	};
	// ------------------------------
	void cipher(ctx_t* ctx, LPBYTE src, LPBYTE dst, size_t cb)
	{
		BYTE t;
		BYTE   i = ctx->i & 0xFF;
		BYTE   j = ctx->j & 0xFF;
		LPBYTE s = ctx->s;

		while (cb > 0)
		{
			i = (i + 1) & 0xFF; j = (j + s[i]) & 0xFF;

			t = s[i]; s[i] = s[j]; s[j] = t;
			if (src != NULL && dst != NULL)
			{
				*dst = *src ^ s[(s[i] + s[j]) % 256];
				src++; dst++;
			}
			cb--;
		}
		ctx->i = i; ctx->j = j;
	};
	// ------------------------------
	BOOL encrypt_or_decrypt(ContainerHandle con_out)
	{
		if (m_status == e_status_init)
		{
			size_t buffer_cb = 0;
			LPBYTE buffer = (LPBYTE) m_in.mem_dup(&buffer_cb);
			if (buffer)
			{
				cipher(&m_ctx, (LPBYTE)m_in.m_p, buffer, buffer_cb);
				m_out.put((void*)buffer, buffer_cb, FALSE);
				m_status = e_status_done;
				if (con_out)
				{
					m_out.get_bytes(con_out, m_encode_output);
				}
				return TRUE;
			}
		}
		m_status = e_status_error;
		return FALSE;
	};
	// ------------------------------
};




// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
#if 0
class triple_des_helper_t : public cng_helper_t
{
   public:

   enum mode_e
   {
      e_mode_ecb = 0x1000 ,
      e_mode_cbc ,
      e_mode_default = 0
   };
   // ------------------------------
   buffer_t  m_chaining_mode;
   buffer_t  m_iv_bytes;
   buffer_t  m_key_bytes;
   buffer_t  m_key_object;
   mode_e    m_mode;
   encode_e  m_encode_iv;
   encode_e  m_encode_key;
   BOOL      m_triple_des_block_padding;
   // ------------------------------
   LONG m_status;
   // ------------------------------
   BCRYPT_ALG_HANDLE m_hAlg;
   BCRYPT_KEY_HANDLE m_hKey;
   // ------------------------------
   triple_des_helper_t( ContainerHandle con_in , ContainerHandle con_flags ) : cng_helper_t( con_in ,con_flags )
   {
      m_mode = e_mode_default;
      m_encode_iv      = e_binary;
      m_encode_key     = e_binary;
      m_triple_des_block_padding  = FALSE;
      m_hAlg = 0;
      m_hKey = 0;
      m_status = 0;
      if( con_flags )
      {
         if(  _conCheckType( con_flags , XPP_OBJECT ) )
         {
            LPSTR p = _conMCallLpstr(con_flags,"get_prop","mode");
            if( p )
            {
               if( lstrcmpi(p,"ebc") == 0 ){  m_mode = e_mode_ecb; }
               else if( lstrcmpi(p,"cbc") == 0 ){  m_mode = e_mode_cbc; }
               _xfree((void*)p); p = 0;
            }
            __encode_prop_from_flags( con_flags, m_encode_iv     , "encode_iv"     );
            __encode_prop_from_flags( con_flags, m_encode_key    , "encode_key"    );

            m_key_bytes.set_bytes( _conMCallCon(con_flags,"get_prop","key") ,  m_encode_key  , TRUE );
            m_iv_bytes.set_bytes(  _conMCallCon(con_flags,"get_prop","iv" ) ,  m_encode_iv   , TRUE );

            if( _conMCallBool(con_flags,"get_prop","triple_des_block_padding") )
            {
               m_triple_des_block_padding = TRUE;
            }

         }
      }

      if( m_mode == e_mode_default )
      {
         if( m_iv_bytes.m_p )
         {
            m_mode =  e_mode_cbc;
         }
         else
         {
            m_mode =  e_mode_ecb;
         }
      }
      switch( m_mode )
      {
         case e_mode_ecb :
         {
            m_iv_bytes.clear();
            m_chaining_mode.put( (void*)  BCRYPT_CHAIN_MODE_ECB , sizeof(BCRYPT_CHAIN_MODE_ECB ) , TRUE );
            break;
         }
         case e_mode_cbc :
         {
            m_chaining_mode.put( (void*)  BCRYPT_CHAIN_MODE_CBC , sizeof(BCRYPT_CHAIN_MODE_CBC) , TRUE );
            break;
         }
      }
   };
   // ------------------------------
   ~triple_des_helper_t()
   {
      if( m_hKey )
      {
         BCryptDestroyKey(m_hKey);
         m_hKey = 0;
      }
      if( m_hAlg )
      {
         BCryptCloseAlgorithmProvider(m_hAlg,0);
         m_hAlg = 0;
      }
      m_chaining_mode.clear();
      m_iv_bytes.clear();
      m_key_bytes.clear();
      m_key_object.clear();
   };
   // ------------------------------
   BOOL prepare_key()
   {

      if( m_hAlg ){ BCryptCloseAlgorithmProvider(m_hAlg,0); m_hAlg = 0; }
      if( m_hKey ){ BCryptDestroyKey(m_hKey); m_hKey = 0; }

      DWORD bytes_written = 0;
      if( !( (m_key_bytes.m_cb == 16) || (m_key_bytes.m_cb == 24) ||   (m_key_bytes.m_cb == 32) ) ){ return FALSE; }
      if( !m_chaining_mode.m_cb ){ return FALSE; }


      m_status = BCryptOpenAlgorithmProvider( &m_hAlg, BCRYPT_triple_des_ALGORITHM,0,0);
      if( m_status < 0 ){ return FALSE; }

      DWORD dw = 0;

      m_status = BCryptGetProperty(m_hAlg,BCRYPT_OBJECT_LENGTH, (LPBYTE) &dw , sizeof(DWORD), &bytes_written,0);
      if( m_status < 0 ){ return FALSE; }
      m_key_object.alloc(dw);

      if( m_iv_bytes.m_p )
      {
         m_status = BCryptGetProperty(m_hAlg,BCRYPT_BLOCK_LENGTH, (LPBYTE) &dw , sizeof(DWORD), &bytes_written,0);
         if( m_status < 0 ){ return FALSE; }
         if( dw > m_iv_bytes.m_cb ){ return FALSE; }
         m_iv_bytes.m_cb = dw;
      }

      m_status = BCryptSetProperty(m_hAlg,BCRYPT_CHAINING_MODE,(LPBYTE) m_chaining_mode.m_p, m_chaining_mode.m_cb, 0);
      if( m_status < 0 ){ return FALSE; }

      m_status = BCryptGenerateSymmetricKey(m_hAlg,&m_hKey,(LPBYTE) m_key_object.m_p , m_key_object.m_cb,(LPBYTE) m_key_bytes.m_p , m_key_bytes.m_cb,0);
      if( m_status < 0 ){ return FALSE; }

      return TRUE;
   };
   // ------------------------------
   BOOL encrypt(ContainerHandle con_out)
   {
      DWORD dwFlags = 0;

      if(  m_triple_des_block_padding )
      {
         dwFlags |= BCRYPT_BLOCK_PADDING;
      }

      DWORD cbo = 0;
      m_status = BCryptEncrypt(m_hKey,(LPBYTE)m_in.m_p,m_in.m_cb,0,(LPBYTE)m_iv_bytes.m_p,m_iv_bytes.m_cb,0,0,&cbo,dwFlags);
      if( m_status < 0 ){ return FALSE; }
      if( cbo  < 1 ){ return FALSE; }
      m_out.alloc(cbo);

      m_status = BCryptEncrypt(m_hKey,(LPBYTE)m_in.m_p,m_in.m_cb,0,(LPBYTE)m_iv_bytes.m_p,m_iv_bytes.m_cb,(LPBYTE)m_out.m_p,m_out.m_cb,&cbo,dwFlags);
      if( m_status < 0 ){ return FALSE; }
      if( cbo  < 1 ){ return FALSE; }
      if( cbo  > m_out.m_cb ){ return FALSE; }
      m_out.m_cb = cbo;

      m_out.get_bytes(con_out,m_encode_output);

      return TRUE;
   };
   // ------------------------------
   BOOL decrypt(ContainerHandle con_out)
   {
      DWORD dwFlags = 0;

      if(  m_triple_des_block_padding )
      {
         dwFlags |= BCRYPT_BLOCK_PADDING;
      }

      DWORD cbo = 0;
      m_status = BCryptDecrypt(m_hKey,(LPBYTE)m_in.m_p,m_in.m_cb,0,(LPBYTE)m_iv_bytes.m_p,m_iv_bytes.m_cb,0,0,&cbo,dwFlags);
      if( m_status < 0 ){ return FALSE; }
      if( cbo  < 1 ){ return FALSE; }
      m_out.alloc(cbo);

      m_status = BCryptDecrypt(m_hKey,(LPBYTE)m_in.m_p,m_in.m_cb,0,(LPBYTE)m_iv_bytes.m_p,m_iv_bytes.m_cb,(LPBYTE)m_out.m_p,m_out.m_cb,&cbo,dwFlags);
      if( m_status < 0 ){ return FALSE; }
      if( cbo  < 1 ){ return FALSE; }
      if( cbo  > m_out.m_cb ){ return FALSE; }
      m_out.m_cb = cbo;

      m_out.get_bytes(con_out,m_encode_output);

      return TRUE;
   };
   // ------------------------------
};
#endif
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------
void __cdecl aes_encrypt( XppParamList pl ) // aes_encrypt(plain,key,flags)
{
   TXppParamList xpp(pl,2);
   
   ContainerHandle con_out = xpp[0]->con();
   
   if( con_out ) // closure to make the aes helper release first
   {
      aes_helper_t aes(xpp[1]->con(),xpp[2]->con());
      if( aes.prepare_key() )
      {
         aes.encrypt(con_out);
      }
   }
}
// -----------------------------------------------------------------------------------------------------------------
void __cdecl aes_decrypt( XppParamList pl ) // aes_decrypt(encr,key,flags)
{
   TXppParamList xpp(pl,2);
   
   ContainerHandle con_out = xpp[0]->con();
   
   if( con_out ) // closure to make the aes helper release first
   {
      aes_helper_t aes(xpp[1]->con(),xpp[2]->con());
      if( aes.prepare_key() )
      {
         aes.decrypt(con_out);
      }
   }
}
// ---------------------------------------------------------------------------------------------------------------------
void __cdecl rc4_encrypt_decrypt(XppParamList pl) // rc4_encrypt_decrypt(input,key,flags)
{
	TXppParamList xpp(pl, 2);

	ContainerHandle con_out = xpp[0]->con();

	if (con_out) // closure to make the rc4 helper release first
	{
		rc4_helper_t rc4(xpp[1]->con(), xpp[2]->con());
		if (rc4.m_status == rc4_helper_t::e_status_init )
		{
			rc4.encrypt_or_decrypt(con_out);
		}
	}
}
// -----------------------------------------------------------------------------------------------------------------
END_NAMESPACE() // ot4xb_cng_ns
// ---------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_( OT4XB_CNG )
{
   if( ! ot4xb_cng_ns::init_module() )
   {
      _ret(pl);
      return;
   }

   ContainerHandle conco = _conClsObj("OT4XB_CNG");
   if( conco == NULLCONTAINER )
   {

      TXbClass * pc = new TXbClass;pc->ClassName("OT4XB_CNG");
      pc->EXPORTED();
      pc->ClassVar( "__mc__ht" );
      // -----
      pc->ClassMethod_cbbs("aes_encrypt" , "{|s,plain,flags| XbFpCall(%i,plain,flags) }" , ot4xb_cng_ns::aes_encrypt );
      pc->ClassMethod_cbbs("aes_decrypt" , "{|s,encr,flags| XbFpCall(%i,encr,flags) }"   , ot4xb_cng_ns::aes_decrypt ); 
		// ----- 
		pc->ClassMethod_cbbs("rc4_encrypt", "{|s,plain,flags| XbFpCall(%i,plain,flags) }", ot4xb_cng_ns::rc4_encrypt_decrypt );
		pc->ClassMethod_cbbs("rc4_decrypt", "{|s,encr,flags| XbFpCall(%i,encr,flags) }", ot4xb_cng_ns::rc4_encrypt_decrypt   );
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

