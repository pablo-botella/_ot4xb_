//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
// ---------------------------------------------------------------------------------------------------------------------------

// Declaración del puntero a la función SystemFunction036
typedef BOOL( WINAPI* SystemFunction036_t )( BYTE* data, DWORD dataSize );
SystemFunction036_t SystemFunction036 = nullptr;
// ---------------------------------------------------------------------------------------------------------------------------
enum class rg_encoding_e : int
{
   invalid_e = -1,
   default_e = 0,
   hex2bin_e,
   bin2hex_e,
   b642bin_e,
   bin2b64_e,
   random_binary_e,
   random_base64_e,
   random_hex_e,
   decimal_e,
   hex_e
};

static BOOL InitializeSystemFunction036()
{
   if( SystemFunction036 ) { return TRUE; }

   HMODULE hAdvapi32 = GetModuleHandleA( "advapi32.dll" );
   if( hAdvapi32 )
   {
      SystemFunction036 = (SystemFunction036_t) GetProcAddress( hAdvapi32, "SystemFunction036" );
   }
   if( SystemFunction036 ) { return TRUE; }
   return FALSE;
}
// ---------------------------------------------------------------------------------------------------------------------------

static DWORD get_key_type_by_name( LPSTR key_type )
{
   if( key_type == nullptr ) { return 0; }
   if( _xstrcmpi( key_type, "SZ" ) == 0 ) { return REG_SZ; }
   else if( _xstrcmpi( key_type, "EXPAND_SZ" ) == 0 ) { return REG_EXPAND_SZ; }
   else if( _xstrcmpi( key_type, "BINARY" ) == 0 ) { return REG_BINARY; }
   else if( _xstrcmpi( key_type, "DWORD" ) == 0 ) { return REG_DWORD; }
   else if( _xstrcmpi( key_type, "DWORD_LITTLE_ENDIAN" ) == 0 ) { return REG_DWORD_LITTLE_ENDIAN; }
   else if( _xstrcmpi( key_type, "DWORD_BIG_ENDIAN" ) == 0 ) { return REG_DWORD_BIG_ENDIAN; }
   else if( _xstrcmpi( key_type, "LINK" ) == 0 ) { return REG_LINK; }
   else if( _xstrcmpi( key_type, "MULTI_SZ" ) == 0 ) { return REG_MULTI_SZ; }
   else if( _xstrcmpi( key_type, "RESOURCE_LIST" ) == 0 ) { return REG_RESOURCE_LIST; }
   else if( _xstrcmpi( key_type, "FULL_RESOURCE_DESCRIPTOR" ) == 0 ) { return REG_FULL_RESOURCE_DESCRIPTOR; }
   else if( _xstrcmpi( key_type, "RESOURCE_REQUIREMENTS_LIST" ) == 0 ) { return REG_RESOURCE_REQUIREMENTS_LIST; }
   else if( _xstrcmpi( key_type, "QWORD" ) == 0 ) { return REG_QWORD; }
   else if( _xstrcmpi( key_type, "QWORD_LITTLE_ENDIAN" ) == 0 ) { return REG_QWORD_LITTLE_ENDIAN; }
   return 0;
}


// ---------------------------------------------------------------------------------------------------------------------------
static rg_encoding_e get_registry_value_as_string_encoding_type( LPSTR encoding, BOOL bRead )

{

   // Process the value according to the encoding
   if( encoding == nullptr ) return rg_encoding_e::default_e;
   if( bRead )
   {
      if( _xstrcmpi( encoding, "decimal" ) == 0 ) return rg_encoding_e::decimal_e;
      if( _xstrcmpi( encoding, "hex" ) == 0 ) return rg_encoding_e::hex_e;
   }
   else
   {
      if( _xstrcmpi( encoding, "random_binary" ) == 0 ) return rg_encoding_e::random_binary_e;
      if( _xstrcmpi( encoding, "random_base64" ) == 0 ) return rg_encoding_e::random_base64_e;
      if( _xstrcmpi( encoding, "random_hex" ) == 0 ) return rg_encoding_e::random_hex_e;
   }
   if( _xstrcmpi( encoding, "hex2bin" ) == 0 ) return rg_encoding_e::hex2bin_e;
   if( _xstrcmpi( encoding, "bin2hex" ) == 0 ) return rg_encoding_e::bin2hex_e;
   if( _xstrcmpi( encoding, "b642bin" ) == 0 ) return rg_encoding_e::b642bin_e;
   if( _xstrcmpi( encoding, "bin2b64" ) == 0 ) return rg_encoding_e::bin2b64_e;

   return rg_encoding_e::invalid_e;
}
// ---------------------------------------------------------------------------------------------------------------------------
static HKEY ot4xb_get_open_hkey_name( LPSTR key_name, BOOL bCreate )
{
   HKEY hKey = 0;
   char key_name_buffer[ 1024 ] = { 0 };
   char* key = key_name_buffer;
   strncpy_s( key_name_buffer, key_name,sizeof( key_name_buffer ) - 2 );

   // Determine the main key
   if( strncmp( key, "HKLM\\", 5 ) == 0 ) { hKey = HKEY_LOCAL_MACHINE; key += 5; }
   else if( strncmp( key, "HKCC\\", 5 ) == 0 ) { hKey = HKEY_CURRENT_CONFIG; key += 5; }
   else if( strncmp( key, "HKCR\\", 5 ) == 0 ) { hKey = HKEY_CLASSES_ROOT; key += 5; }
   else if( strncmp( key, "HKCU\\", 5 ) == 0 ) { hKey = HKEY_CURRENT_USER; key += 5; }
   else if( strncmp( key, "HKU\\", 4 ) == 0 ) { hKey = HKEY_USERS; key += 4; }
   else { return 0; } // Unrecognized main key

   HKEY hSubkey = 0;

   // Split the string into subkeys and create them if they do not exist
   char* context = nullptr;
   char* token = strtok_s( key, "\\", &context );
   HKEY hCurrentKey = 0;
   while( token != NULL )
   {
      // Intentar abrir la clave existente
      LSTATUS result = RegOpenKeyExA( ( hCurrentKey ? hCurrentKey : hKey ), token, 0, KEY_WRITE, &hSubkey );
      if( result == ERROR_FILE_NOT_FOUND && bCreate )
      {
         result = RegCreateKeyExA( ( hCurrentKey ? hCurrentKey : hKey ), token, 0, NULL, 0, KEY_WRITE, NULL, &hSubkey, NULL );
      }
      if( hCurrentKey ) { RegCloseKey( hCurrentKey ); hCurrentKey = 0; }
      if( result != ERROR_SUCCESS ) { return 0; }
      hCurrentKey = hSubkey;
      token = strtok_s( NULL, "\\", &context );
   }
   return hSubkey;
}
// ---------------------------------------------------------------------------------------------------------------------------
// ot4xb_set_registry_value_as_string( LPSTR key, LPSTR valueName, LPSTR value, size_t value_cb, LPSTR encoding, LPSTR key_type )
_XPP_REG_FUN_( OT4XB_SET_REGISTRY_VALUE_AS_STRING )
{
   TXppParamList xpp( pl, 6 );
   LPSTR key = xpp[ 1 ]->LockStr();
   LPSTR valueName = xpp[ 2 ]->LockStr();
   LPSTR value = xpp[ 3 ]->LockStr();
   size_t value_cb = xpp[ 4 ]->CheckType( XPP_NUMERIC ) ? xpp[ 4 ]->GetDWord() : (DWORD) -1;
   LPSTR encoding = xpp[ 5 ]->LockStr();
   LPSTR key_type = xpp[ 6 ]->LockStr();
   BOOL result = ot4xb_set_registry_value_as_string( key, valueName, value, value_cb, encoding, key_type );
   xpp[ 0 ]->PutBool( result );
}
// ---------------------------------------------------------------------------------------------------------------------------
// ot4xb_get_registry_value_as_string( LPSTR key, LPSTR valueName, DWORD* value_cb, LPSTR encoding )
_XPP_REG_FUN_( OT4XB_GET_REGISTRY_VALUE_AS_STRING )
{
   TXppParamList xpp( pl, 3 );
   LPSTR key = xpp[ 1 ]->LockStr();
   LPSTR valueName = xpp[ 2 ]->LockStr();
   LPSTR encoding = xpp[ 3 ]->LockStr();
   DWORD value_cb = 0;
   LPSTR result = ot4xb_get_registry_value_as_string( key, valueName, value_cb, encoding );
   xpp[ 0 ]->PutStrLen( result, value_cb );
   _xfree( result );
}
// ---------------------------------------------------------------------------------------------------------------------------

OT4XB_API BOOL ot4xb_set_registry_value_as_string( LPSTR key_name, LPSTR valueName, LPSTR value, size_t value_cb, LPSTR encoding, LPSTR key_type )
{

   if( !InitializeSystemFunction036() ) { return FALSE; }

   rg_encoding_e enc = get_registry_value_as_string_encoding_type( encoding, 0 );
   if( enc == rg_encoding_e::invalid_e ) { return FALSE; }

   DWORD dwType = get_key_type_by_name( key_type );
   if( enc == rg_encoding_e::random_binary_e || enc == rg_encoding_e::random_base64_e || enc == rg_encoding_e::random_hex_e )
   {
      dwType = REG_SZ;
   }
   if( !dwType )
   {
      return FALSE;
   }

   HKEY hSubKey = ot4xb_get_open_hkey_name( key_name, TRUE );
   if( !hSubKey )
   {
      return FALSE;
   }

   LONG result = -1;
   void* buffer = 0;
   BYTE* data = 0;
   DWORD dataSize = 0;
   BYTE empty_value[ 8 ] = { 0 };
   switch( enc )
   {
      case rg_encoding_e::default_e:
      {
         switch( dwType )
         {
            case REG_DWORD:
            case REG_DWORD_BIG_ENDIAN:
            {
               DWORD dwValue = value ? strtoul( value, nullptr, 0 ) : 0;
               data = reinterpret_cast<BYTE*>( &dwValue );
               dataSize = sizeof( DWORD );
               break;
            }
            case REG_QWORD:
            {
               ULONGLONG qwValue = value ? strtoull( value, nullptr, 0 ) : 0;
               data = reinterpret_cast<BYTE*>( &qwValue );
               dataSize = sizeof( ULONGLONG );
               break;
            }
            default:
            {
               if( value == nullptr )
               {
                  value = (LPSTR) empty_value;
               }
               else if( value_cb == -1 )
               {
                  value_cb = _xstrlen( value );
               }
               data = reinterpret_cast<BYTE*>( value );
               dataSize = strlen( value ) + 1;
               break;
            }
         }
         break;
      }
      case rg_encoding_e::hex2bin_e:
      {
         if( value == nullptr ) { value = (LPSTR) empty_value; }
         DWORD cb = 0;
         buffer = (void*) pHex2Bin( (LPSTR) value, &cb );
         dataSize = cb;
         data = static_cast<BYTE*>( buffer );
         break;
      }
      case rg_encoding_e::bin2hex_e:
      {
         if( value == nullptr ) { value = (LPSTR) empty_value; value_cb = 0; }
         buffer = (void*) pBin2Hex( (LPBYTE) value, value_cb );
         dataSize = _xstrlen( (LPSTR) buffer );
         data = (BYTE*) buffer;
         break;
      }
      case rg_encoding_e::b642bin_e:
      {
         int cb = ot4xb_base64_decode_required_length( value_cb );
         buffer = _xgrab( cb );
         data = static_cast<BYTE*>( buffer );
         if( !ot4xb_base64_decode( value, strlen( value ), data, &cb ) )
         {
            dataSize = cb;

         }
         else
         {
            dataSize = 0;
            data = nullptr;
         }
         break;
      }
      case rg_encoding_e::bin2b64_e:
      {
         if( value == nullptr ) { value = (LPSTR) empty_value; }
         int len = ot4xb_base64_encode_required_length( value_cb );
         buffer = _xgrab( len );
         data = static_cast<BYTE*>( buffer );
         if( !ot4xb_base64_encode( reinterpret_cast<BYTE*>( value ), strlen( value ), reinterpret_cast<char*>( data ), &len, 0 ) )
         {
            dataSize = 0;
            data = nullptr;
         }
         else
         {
            dataSize = len;
         }
         break;
      }
      case rg_encoding_e::random_binary_e:
      {
         dwType = REG_BINARY;
         dataSize = value_cb > 0 ? value_cb : 16; // Default size of 16 bytes if not specified
         buffer = _xgrab( dataSize );
         data = static_cast<BYTE*>( buffer );
         if( !SystemFunction036( data, dataSize ) )
         {
            dataSize = 0;
            data = nullptr;
         }
         break;
      }
      case rg_encoding_e::random_base64_e:
      case rg_encoding_e::random_hex_e:
      {
         dwType = REG_SZ;
         DWORD raw_buffer_size = value_cb > 0 ? value_cb : 16; // Default size of 16 bytes if not specified
         void* raw_buffer = _xgrab( raw_buffer_size + 1 );
         if( SystemFunction036( (BYTE*) raw_buffer, raw_buffer_size ) )
         {
            switch( enc )
            {
               case rg_encoding_e::random_base64_e:
               {
                  int len = ot4xb_base64_encode_required_length( raw_buffer_size );
                  buffer = _xgrab( len );
                  if( ot4xb_base64_encode( reinterpret_cast<BYTE*>( raw_buffer ), raw_buffer_size, reinterpret_cast<char*>( buffer ), &len, 0 ) )
                  {
                     data = static_cast<BYTE*>( buffer );
                     dataSize = len;
                  }
                  break;
               }
               case rg_encoding_e::random_hex_e:
               {
                  buffer = pBin2Hex( reinterpret_cast<BYTE*>( raw_buffer ), raw_buffer_size );
                  data = static_cast<BYTE*>( buffer );
                  dataSize = _xstrlen( reinterpret_cast<char*>( data ) );
                  break;
               }
            }
         }
         _xfree( raw_buffer ); raw_buffer = nullptr;
         break;
      }
   }
   if( data )
   {
      result = RegSetValueExA( hSubKey, valueName, 0, dwType, data, dataSize );
   }
   if( buffer )
   {
      _xfree( buffer );
   }
   RegCloseKey( hSubKey );
   return result == ERROR_SUCCESS;
}

// ---------------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR ot4xb_get_registry_value_as_string( LPSTR key_name, LPSTR valueName, DWORD& value_cb, LPSTR encoding )
{
   value_cb = 0;
   rg_encoding_e enc = get_registry_value_as_string_encoding_type( encoding, 1 );
   if( enc == rg_encoding_e::invalid_e ) { return FALSE; }

   HKEY hSubKey = ot4xb_get_open_hkey_name( key_name, FALSE );
   if( !hSubKey ) { return FALSE; }
   LONG result = -1;
   DWORD dwType = 0;
   DWORD dataSize = 0;
   BYTE* data = nullptr;
   LPSTR resultString = nullptr;


   result = RegQueryValueExA( hSubKey, valueName, NULL, &dwType, NULL, &dataSize );
   if( result == ERROR_SUCCESS )
   {
      data = (BYTE*) _xgrab( dataSize );
      result = RegQueryValueExA( hSubKey, valueName, NULL, &dwType, data, &dataSize );
   }
   RegCloseKey( hSubKey );
   if( result == ERROR_SUCCESS && data )
   {

      switch( enc )
      {
         case rg_encoding_e::default_e:
         case rg_encoding_e::decimal_e:
         {
            switch( dwType )
            {
               case REG_DWORD:
               {
                  DWORD dwValue = *reinterpret_cast<DWORD*>( data );
                  resultString = (LPSTR) _xgrab( 12 ); // Max length for DWORD in decimal
                  value_cb = sprintf_s( resultString, 12, "%lu", dwValue );
                  break;
               }
               case REG_QWORD:
               {
                  ULONGLONG qwValue = *reinterpret_cast<ULONGLONG*>( data );
                  resultString = (LPSTR) _xgrab( 21 ); // Max length for ULONGLONG in decimal
                  value_cb = sprintf_s( resultString, 21, "%llu", qwValue );
                  break;
               }
               default:
               {
                  resultString = (LPSTR) _xgrab( dataSize + 1 );
                  memcpy( resultString, data, dataSize );
                  resultString[ dataSize ] = '\0';
                  value_cb = dataSize;
                  break;
               }
            }
            break;
         }
         case rg_encoding_e::hex_e:

         {
            switch( dwType )
            {
               case REG_DWORD:
               {
                  DWORD dwValue = *reinterpret_cast<DWORD*>( data );
                  resultString = (LPSTR) _xgrab( 11 ); // Max length for DWORD in hex
                  value_cb = sprintf_s( resultString, 11, "0x%08X", dwValue );
                  break;
               }
               case REG_QWORD:
               {
                  ULONGLONG qwValue = *reinterpret_cast<ULONGLONG*>( data );
                  resultString = (LPSTR) _xgrab( 19 ); // Max length for ULONGLONG in hex
                  value_cb = sprintf_s( resultString, 19, "0x%016llX", qwValue );
                  break;
               }
            }
            break;
         }
         case rg_encoding_e::hex2bin_e:
         {
            resultString = (LPSTR) pHex2Bin( (LPSTR) data, &value_cb );
            break;
         }
         case rg_encoding_e::bin2hex_e:
         {
            resultString = pBin2Hex( data, dataSize );
            value_cb = dataSize * 2;
            break;
         }
         case rg_encoding_e::b642bin_e:
         {
            int cb = ot4xb_base64_decode_required_length( dataSize );
            resultString = (LPSTR) _xgrab( cb + 1 );
            if( ot4xb_base64_decode( reinterpret_cast<char*>( data ), dataSize, reinterpret_cast<BYTE*>( resultString ), &cb ) )
            {
               resultString[ cb ] = '\0';
               value_cb = cb;

            }
            else
            {
               _xfree( resultString );
               resultString = 0;
            }
            break;
         }
         case rg_encoding_e::bin2b64_e:
         {
            int len = ot4xb_base64_encode_required_length( dataSize );
            resultString = (LPSTR) _xgrab( len + 1 );
            if( ot4xb_base64_encode( data, dataSize, resultString, &len, 0 ) )
            {
               resultString[ len ] = '\0';
            }
            else
            {
               _xfree( resultString );
               resultString = 0;
            }
            break;
         }
      }
   }
   if( data )
   {
      _xfree( data );
      data = 0;
   }
   return resultString;
}