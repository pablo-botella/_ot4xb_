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
_XPP_REG_FUN_( ARGON2_HASH )
{
   TXppParamList xpp( pl, 7 );

   LPSTR password = xpp[ 1 ]->LockStrEx();
   uint32_t password_cb = xpp[ 1 ]->ExLen();

   LPSTR salt = xpp[ 2 ]->LockStrEx();
   uint32_t salt_cb = xpp[ 2 ]->ExLen();

   uint32_t flags = ( xpp[ 4 ]->CheckType( XPP_NUMERIC ) ? xpp[ 4 ]->GetDWord() : 0x20 );

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
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// argon2_verify( 1 pwd , 2 hash ,3 @error_code,  4 flags 0x02 ) -> lOk | NIL
_XPP_REG_FUN_( ARGON2_VERIFY )
{
   TXppParamList xpp( pl, 7 );

   LPSTR password = xpp[ 1 ]->LockStrEx();
   uint32_t password_cb = xpp[ 1 ]->ExLen();

   LPSTR hash = xpp[ 2 ]->LockStrEx();
   uint32_t hash_cb = xpp[ 2 ]->ExLen();

   uint32_t flags = ( xpp[ 4 ]->CheckType( XPP_NUMERIC ) ?  xpp[ 4 ]->GetDWord() : 0x20 );

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