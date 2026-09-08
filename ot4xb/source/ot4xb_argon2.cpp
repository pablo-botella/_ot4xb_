#include <ot4xb_api.h>
#include <argon2.h>

// -----------------------------------------------------------------------------------------------------------------
// flags 
// 0x0000  base64   // default
// 0x0010  raw      // not supported for verify 
// 0x0000  Argon2_d = 0,
// 0x0001  Argon2_i = 1,
// 0x0002  Argon2_id = 2 // default

// argon2_hash( 1 pwd , 2 salt , 3 @error_code, 4 flags = 0x02  , 5 size_in_bytes   = 32 ,  6 time_cost = 3 , 7 memory_cost =0x10000 ) -> hash_str | NIL
// argon2_verify( 1 pwd , 2 hash ,3 @error_code,  4 flags 0x02 ) -> lOk | NIL

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: argon2_hash
            | syntax_: ```
                 argon2_hash( cPassword, cSalt, @nErrorCode, nFlags, [nSize := 32], [nTimeCost := 3], [nMemoryCost := 0x10000] )
              ```
            | category: crypto/password
            | _kw_: argon2_hash, Function
   }}*/
/*{{|desc: Computes an Argon2 password hash using the bundled Argon2 implementation. The result can be an
      encoded Argon2 string or raw hash bytes depending on nFlags.
    | params:
    - `cPassword` character - Password bytes.
    - `cSalt` character - Salt bytes.
    - `nErrorCode` numeric by reference - Receives the Argon2 result code. 0 means success.
    - `nFlags` numeric - Algorithm and output selector. Pass this explicitly.
    - `nSize` numeric - Hash size in bytes.
    - `nTimeCost` numeric - Argon2 time cost.
    - `nMemoryCost` numeric - Argon2 memory cost. The default value represents 64 MB.
    | flags:
    - `0x0000` Argon2d encoded output.
    - `0x0001` Argon2i encoded output.
    - `0x0002` Argon2id encoded output. Recommended default for new code.
    - `0x0010` Argon2d raw output.
    - `0x0011` Argon2i raw output.
    - `0x0012` Argon2id raw output.

    Returns character / NIL - Hash string or raw hash bytes on success; NIL when the hash cannot be produced.

    |note: Always pass nFlags explicitly in current builds. Encoded output is suitable for argon2_verify(); raw
      output is binary bytes and is not accepted by argon2_verify(). }}*/
_XPP_REG_FUN_( ARGON2_HASH )
{
   TXppParamList xpp( pl, 7 );

   LPSTR password = xpp[ 1 ]->LockStrEx();
   uint32_t password_cb = xpp[ 1 ]->ExLen();

   LPSTR salt = xpp[ 2 ]->LockStrEx();
   uint32_t salt_cb = xpp[ 2 ]->ExLen();

   uint32_t flags = ( xpp[ 4 ]->CheckType( XPP_NUMERIC ) ? xpp[ 4 ]->GetDWord() : 0x02 );

   uint32_t size_in_bytes = ( xpp[ 5 ]->CheckType( XPP_NUMERIC ) ? xpp[ 5 ]->GetDWord() : 32 );
   uint32_t time_cost = ( xpp[ 6 ]->CheckType( XPP_NUMERIC ) ? xpp[ 6 ]->GetDWord() : 3 );
   uint32_t memory_cost = ( xpp[ 7 ]->CheckType( XPP_NUMERIC ) ? xpp[ 7 ]->GetDWord() : 0x10000 ); // 64MB

   int32_t result = ARGON2_MISSING_ARGS;




   if( password && password_cb && salt && salt_cb && size_in_bytes > 3 )
   {

      switch( flags )
      {
         case 0x0000: // Argon2_d.base64
         {
            size_t encoded_len = argon2_encodedlen( time_cost, memory_cost, 1, salt_cb, size_in_bytes, Argon2_d );
            void* buffer = _xgrab( encoded_len + 1 );
            if( buffer )
            {

               result = argon2d_hash_encoded( time_cost, memory_cost, 1, password, password_cb, salt, salt_cb, size_in_bytes, (char*) buffer, encoded_len );
               if( result == 0 )
               {
                  xpp[ 0 ]->PutStr( (char*) buffer );
               }
               _xfree( buffer );
               buffer = 0;
            }
            else
            {
               result = -256;
            }
            break;
         }
         case 0x0010: // Argon2_d.raw
         {
            void* buffer = _xgrab( size_in_bytes + 1 );
            if( buffer )
            {

               result = argon2d_hash_raw( time_cost, memory_cost, 1, password, password_cb, salt, salt_cb, (char*) buffer, size_in_bytes );
               if( result == 0 )
               {
                  xpp[ 0 ]->PutStrLen( (char*) buffer, size_in_bytes );
               }
               _xfree( buffer );
               buffer = 0;
            }
            else
            {
               result = -256;
            }
            break;
         }
         case 0x0001: // Argon2_i.base64
         {
            size_t encoded_len = argon2_encodedlen( time_cost, memory_cost, 1, salt_cb, size_in_bytes, Argon2_i );
            void* buffer = _xgrab( encoded_len + 1 );
            if( buffer )
            {

               result = argon2i_hash_encoded( time_cost, memory_cost, 1, password, password_cb, salt, salt_cb, size_in_bytes, (char*) buffer, encoded_len );
               if( result == 0 )
               {
                  xpp[ 0 ]->PutStr( (char*) buffer );
               }
               _xfree( buffer );
               buffer = 0;
            }
            else
            {
               result = -256;
            }
            break;
         }
         case 0x0011: // Argon2_i.raw
         {
            void* buffer = _xgrab( size_in_bytes + 1 );
            if( buffer )
            {

               result = argon2i_hash_raw( time_cost, memory_cost, 1, password, password_cb, salt, salt_cb, (char*) buffer, size_in_bytes );
               if( result == 0 )
               {
                  xpp[ 0 ]->PutStrLen( (char*) buffer, size_in_bytes );
               }
               _xfree( buffer );
               buffer = 0;
            }
            else
            {
               result = -256;
            }
            break;
         }
         case 0x0002: // Argon2_id.base64
         {
            size_t encoded_len = argon2_encodedlen( time_cost, memory_cost, 1, salt_cb, size_in_bytes, Argon2_id );
            void* buffer = _xgrab( encoded_len + 1 );
            if( buffer )
            {

               result = argon2id_hash_encoded( time_cost, memory_cost, 1, password, password_cb, salt, salt_cb, size_in_bytes, (char*) buffer, encoded_len );
               if( result == 0 )
               {
                  xpp[ 0 ]->PutStr( (char*) buffer );
               }
               _xfree( buffer );
               buffer = 0;
            }
            else
            {
               result = -256;
            }
            break;
         }
         case 0x0012: // Argon2_id.raw
         {
            void* buffer = _xgrab( size_in_bytes + 1 );
            if( buffer )
            {

               result = argon2id_hash_raw( time_cost, memory_cost, 1, password, password_cb, salt, salt_cb, (char*) buffer, size_in_bytes );
               if( result == 0 )
               {
                  xpp[ 0 ]->PutStrLen( (char*) buffer, size_in_bytes );
               }
               _xfree( buffer );
               buffer = 0;
            }
            else
            {
               result = -256;
            }
            break;
         }
         default:
         {
            result = ARGON2_INCORRECT_TYPE;
            break;
         }
      }
   }
   xpp[ 3 ]->PutLong( result );
}
/*{{end-function}}*/
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: argon2_verify
            | syntax_: `argon2_verify( cPassword, cEncodedHash, @nErrorCode, nFlags )`
            | category: crypto/password
            | _kw_: argon2_verify, Function
   }}*/
/*{{|desc: Verifies a password against an encoded Argon2 hash.
    | params:
    - `cPassword` character - Password bytes to verify.
    - `cEncodedHash` character - Encoded Argon2 hash string.
    - `nErrorCode` numeric by reference - Receives the Argon2 result code. 0 means success.
    - `nFlags` numeric - Algorithm selector. Use 0x0000 for Argon2d, 0x0001 for Argon2i or 0x0002 for
      Argon2id.
    | flags:
    - `0x0000` Argon2d encoded output.
    - `0x0001` Argon2i encoded output.
    - `0x0002` Argon2id encoded output. Recommended default for new code.

    Returns logical - .T. when the password verifies; .F. otherwise. }}*/
_XPP_REG_FUN_( ARGON2_VERIFY )
{
   TXppParamList xpp( pl, 7 );

   LPSTR password = xpp[ 1 ]->LockStrEx();
   uint32_t password_cb = xpp[ 1 ]->ExLen();

   LPSTR hash = xpp[ 2 ]->LockStrEx();
   uint32_t hash_cb = xpp[ 2 ]->ExLen();

   uint32_t flags = ( xpp[ 4 ]->CheckType( XPP_NUMERIC ) ?  xpp[ 4 ]->GetDWord() : 0x02 );

   int32_t result = ARGON2_MISSING_ARGS;




   if( password && password_cb && hash && hash_cb )
   {

      switch( flags )
      {
         case 0x0000: // Argon2_d.base64
         {
            result = argon2d_verify( (const char*) hash, (const void*) password, (const size_t) password_cb );
            break;
         }
         case 0x0001: // Argon2_i.base64
         {
            result = argon2i_verify( (const char*) hash, (const void*) password, (const size_t) password_cb );
            break;
         }
         case 0x0002: // Argon2_id.base64
         {
            result = argon2id_verify( (const char*) hash, (const void*) password, (const size_t) password_cb );
            break;
         }
         default:
         {
            result = ARGON2_INCORRECT_TYPE;
            break;
         }
      }
   }
   xpp[ 3 ]->PutLong( result );
   xpp[ 0 ]->PutBool( result ? 0 : 1 );
}
/*{{end-function}}*/
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------



/*




ARGON2_PUBLIC int argon2i_verify( const char* encoded, const void* pwd,
                                  const size_t pwdlen );

ARGON2_PUBLIC int argon2d_verify( const char* encoded, const void* pwd,
                                  const size_t pwdlen );

ARGON2_PUBLIC int argon2id_verify( const char* encoded, const void* pwd,
                                   const size_t pwdlen );

ARGON2_PUBLIC int argon2_verify( const char* encoded, const void* pwd,
                                 const size_t pwdlen, argon2_type type );


ARGON2_PUBLIC const char* argon2_error_message( int error_code );

ARGON2_PUBLIC size_t argon2_encodedlen( uint32_t t_cost, uint32_t m_cost,
                                        uint32_t parallelism, uint32_t saltlen,
                                        uint32_t hashlen, argon2_type type );
*/
