//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#pragma optimize( "t", on )
#include <ot4xb_api.h>
#include <string>
// ----------------------------------------------------------------------------------------------------------------------
#ifndef min
#define min(a, b) ((a) < (b) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) ((a) > (b) ? (a) : (b))
#endif
//----------------------------------------------------------------------------------------------------------------------

namespace base32_ns
{

   static char base32_rfc4648_alphabet[ ] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M','N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '2', '3', '4', '5', '6', '7' };
   static char base32_crockford_alphabet[ ] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J','K', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X', 'Y', 'Z' };
   // --------------------------------------------------------------------------------------------------------------
   int rfc4648_char_to_index( char ch )
   {
      static int t[ 256 ];
      static int b = 0;
      if( !b )
      {
         b = 1;
         for( int i = 0; i < 256; ++i ) t[ i ] = -1; // Inicializar todo a -1
         for( char c = 'A'; c <= 'Z'; ++c ) t[ static_cast<unsigned char>( c ) ] = c - 'A';
         for( char c = '2'; c <= '7'; ++c ) t[ static_cast<unsigned char>( c ) ] = c - '2' + 26;
         t[ static_cast<unsigned char>( '=' ) ] = -2; // Padding

      }
      return t[ static_cast<unsigned char>( ch ) ];
   }


   int crockford_char_to_index( char ch )
   {
      static int t[ 256 ];
      static int b = 0;
      if( !b )
      {
         b = 1;
         for( int i = 0; i < 256; ++i ) t[ i ] = -1; // Inicializar todo a -1

         for( char c = '0'; c <= '9'; ++c ) t[ static_cast<unsigned char>( c ) ] = c - '0';
         for( char c = 'A'; c <= 'H'; ++c ) t[ static_cast<unsigned char>( c ) ] = c - 'A' + 10;
         t[ static_cast<unsigned char>( 'J' ) ] = 18;
         t[ static_cast<unsigned char>( 'K' ) ] = 19;
         t[ static_cast<unsigned char>( 'M' ) ] = 20;
         t[ static_cast<unsigned char>( 'N' ) ] = 21;
         t[ static_cast<unsigned char>( 'P' ) ] = 22;
         t[ static_cast<unsigned char>( 'Q' ) ] = 23;
         t[ static_cast<unsigned char>( 'R' ) ] = 24;
         t[ static_cast<unsigned char>( 'S' ) ] = 25;
         t[ static_cast<unsigned char>( 'T' ) ] = 26;
         t[ static_cast<unsigned char>( 'V' ) ] = 27;
         t[ static_cast<unsigned char>( 'W' ) ] = 28;
         t[ static_cast<unsigned char>( 'X' ) ] = 29;
         t[ static_cast<unsigned char>( 'Y' ) ] = 30;
         t[ static_cast<unsigned char>( 'Z' ) ] = 31;

         // Normalizaciones
         t[ static_cast<unsigned char>( 'O' ) ] = 0;
         t[ static_cast<unsigned char>( 'I' ) ] = 1;
         t[ static_cast<unsigned char>( 'L' ) ] = 1;
         t[ static_cast<unsigned char>( '=' ) ] = -2; // Padding
      }
      return t[ static_cast<unsigned char>( ch ) ];
   }


   // --------------------------------------------------------------------------------------------------------------
   DWORD required_padding( int nBytes )
   {
      return (DWORD) ( "\0\6\4\3\1"[ ( nBytes % 5 ) ] & 0x000F );
   }
   // --------------------------------------------------------------------------------------------------------------
   DWORD encode_required_size( DWORD cb )
   {
      return ( cb * 8 + 4 ) / 5;
   }
   // --------------------------------------------------------------------------------------------------------------
   DWORD decode_required_size( DWORD cb )
   {
      return  ( ( ( cb + 7 ) / 8 ) * 5 ) + 1;
   }
   // --------------------------------------------------------------------------------------------------------------
   DWORD encode_5_bytes_block( LPSTR pDigitTable, LPBYTE& pSource, DWORD& cbSource, LPSTR& pDestination, DWORD& cbMaxDestination, DWORD& output_bytes_written, DWORD flags )
   {
      if( !pDigitTable || !pSource || !pDestination || cbSource == 0 || cbMaxDestination < 8 )
      {
         return 0; // Validación de entrada
      }

      BYTE input_block[ 5 ] = { 0 };
      DWORD input_size = ( cbSource < 5 ) ? cbSource : 5; // Tamaño real del bloque de entrada
      char output_block[ 8 ] = { 0 };

      // Copiar datos de entrada al bloque de trabajo
      memcpy( input_block, pSource, input_size );

      // Codificar a Base32
      output_block[ 0 ] = ( input_size > 0 ) ? pDigitTable[ ( input_block[ 0 ] >> 3 ) & 0x1F ] : '=';
      output_block[ 1 ] = ( input_size > 0 ) ? pDigitTable[ ( ( input_block[ 0 ] << 2 ) & 0x1C ) | ( ( input_block[ 1 ] >> 6 ) & 0x03 ) ] : '=';
      output_block[ 2 ] = ( input_size > 1 ) ? pDigitTable[ ( input_block[ 1 ] >> 1 ) & 0x1F ] : '=';
      output_block[ 3 ] = ( input_size > 1 ) ? pDigitTable[ ( ( input_block[ 1 ] << 4 ) & 0x10 ) | ( ( input_block[ 2 ] >> 4 ) & 0x0F ) ] : '=';
      output_block[ 4 ] = ( input_size > 2 ) ? pDigitTable[ ( ( input_block[ 2 ] << 1 ) & 0x1E ) | ( ( input_block[ 3 ] >> 7 ) & 0x01 ) ] : '=';
      output_block[ 5 ] = ( input_size > 3 ) ? pDigitTable[ ( input_block[ 3 ] >> 2 ) & 0x1F ] : '=';
      output_block[ 6 ] = ( input_size > 3 ) ? pDigitTable[ ( ( input_block[ 3 ] << 3 ) & 0x18 ) | ( ( input_block[ 4 ] >> 5 ) & 0x07 ) ] : '=';
      output_block[ 7 ] = ( input_size > 4 ) ? pDigitTable[ input_block[ 4 ] & 0x1F ] : '=';

      // Manejo de flags para case insensitive
      if( flags & 0x0010 )
      { // Convertir a mayúsculas
         for( int i = 0; i < 8; ++i )
         {
            if( output_block[ i ] >= 'a' && output_block[ i ] <= 'z' )
            {
               output_block[ i ] -= ( 'a' - 'A' );
            }
         }
      }
      else if( flags & 0x0030 )
      { // Convertir a minúsculas
         for( int i = 0; i < 8; ++i )
         {
            if( output_block[ i ] >= 'A' && output_block[ i ] <= 'Z' )
            {
               output_block[ i ] += ( 'a' - 'A' );
            }
         }
      }

      // Copiar al buffer de destino
      memcpy( pDestination, output_block, 8 );
      pDestination += 8; // Avanzar el puntero de destino
      cbMaxDestination -= 8; // Reducir el espacio restante en el destino
      output_bytes_written += 8;

      // Actualizar el origen
      pSource += input_size;
      cbSource -= input_size;

      return input_size; // Retornar el tamaño del bloque procesado
   }

   // --------------------------------------------------------------------------------------------------------------
   DWORD decode_8_chars_block( LPSTR pDigitTable, LPCSTR pSource, LPBYTE pDestination, DWORD flags )
   {
      BYTE output_block[ 5 ];
      ZeroMemory( output_block, sizeof( output_block ) );

      int indexes[ 8 ];
      for( int i = 0; i < 8; i++ )
      {
         char current_char = pSource[ i ];

         // Handle case insensitivity based on flags
         if( flags & 0x0010 )
         {
            current_char = (char) toupper( current_char );
         }
         else if( flags & 0x0030 )
         {
            current_char = (char) tolower( current_char );
         }

         if( current_char == '=' )
         {
            indexes[ i ] = -1; // Padding
         }
         else
         {
            if( ( flags & 0x0001 ) || ( pDigitTable == NULL && !( flags & 0x0002 ) ) )
            {
               indexes[ i ] = crockford_char_to_index( current_char );
            }
            else if( flags & 0x0002 )
            {
               indexes[ i ] = rfc4648_char_to_index( current_char );
            }
            else
            {
               const char* pos = strchr( pDigitTable, current_char );
               if( pos == NULL )
               {
                  return (DWORD)  - 1; // Invalid character for provided table
               }
               indexes[ i ] = pos - pDigitTable;
            }

            if( indexes[ i ] < 0 )
            {
               return (DWORD)  - 1;
            }
         }
      }

      output_block[ 0 ] = (BYTE) (( indexes[ 0 ] << 3 ) | ( indexes[ 1 ] >> 2 )) &  0xFF;
      output_block[ 1 ] = (BYTE) ( ( indexes[ 1 ] << 6 ) | ( indexes[ 2 ] << 1 ) | ( indexes[ 3 ] >> 4 ) ) & 0xFF;
      output_block[ 2 ] = (BYTE) ( ( indexes[ 3 ] << 4 ) | ( indexes[ 4 ] >> 1 ) ) & 0xFF;
      output_block[ 3 ] = (BYTE) ( ( indexes[ 4 ] << 7 ) | ( indexes[ 5 ] << 2 ) | ( indexes[ 6 ] >> 3 ) ) & 0xFF;
      output_block[ 4 ] = (BYTE) ( ( indexes[ 6 ] << 5 ) | indexes[ 7 ] ) & 0xFF;

      DWORD bytes_decoded = 5;
      if( indexes[ 7 ] == -1 ) bytes_decoded--;
      if( indexes[ 6 ] == -1 ) bytes_decoded--;
      if( indexes[ 5 ] == -1 ) bytes_decoded--;
      if( indexes[ 4 ] == -1 ) bytes_decoded--;

      memcpy( pDestination, output_block, bytes_decoded );

      return bytes_decoded;
   }


   // --------------------------------------------------------------------------------------------------------------
   DWORD encode_to_buffer( LPSTR pDigitTable, LPBYTE pSource, DWORD cbSource, LPSTR pDestination, DWORD cbMaxDestination , DWORD flags) // output
   {
      DWORD bytes_written = 0;
      DWORD remaining_space = cbMaxDestination - 1;
      DWORD output_size = 0;
      if( ( flags & 0x0001 ) || ( pDigitTable == NULL && !( flags & 0x0002 ) ) )
      {
         pDigitTable = base32_crockford_alphabet;
      }
      else if( flags & 0x0002 )
      {
         pDigitTable = base32_rfc4648_alphabet;
      }
      while( remaining_space && encode_5_bytes_block( pDigitTable, pSource, cbSource, pDestination, remaining_space, bytes_written , flags) )
      {
         output_size += bytes_written;
         pDestination[ 0 ] = 0;
      }
      return bytes_written;
   }
   // --------------------------------------------------------------------------------------------------------------
   DWORD decode_to_buffer( LPSTR pDigitTable, LPCSTR pSource, DWORD cbSource, LPBYTE pDestination, DWORD cbMaxDestination , DWORD flags )
   {
      DWORD bytes_written = 0;

      // Arreglos de tamaño fijo
      BYTE decoded_block[ 5 ]; // Para almacenar los bytes decodificados
      char input_block[ 8 ];   // Para almacenar un bloque de entrada de 8 caracteres

      DWORD remaining_source = cbSource;
      DWORD remaining_destination = cbMaxDestination;

      if( ( flags & 0x0001 ) || ( pDigitTable == NULL && !( flags & 0x0002 ) ) )
      {
         pDigitTable = base32_crockford_alphabet;
      }
      else if( flags & 0x0002 )
      {
         pDigitTable = base32_rfc4648_alphabet; 
      }

      while( remaining_source > 0 )
      {
         // Inicializar el bloque de entrada
         ZeroMemory( input_block, sizeof( input_block ) );
         DWORD input_size = ( remaining_source < 8 ) ? remaining_source : 8;
         memcpy( input_block, pSource, input_size );

         // Decodificar el bloque de entrada
         ZeroMemory( decoded_block, sizeof( decoded_block ) );
         DWORD decoded_size = decode_8_chars_block( pDigitTable, input_block, decoded_block , flags);

         // Verificar si hay espacio suficiente en el destino
         if( remaining_destination < decoded_size )
         {
            return 0;
         }

         // Copiar los bytes decodificados al buffer de destino
         _bcopy( pDestination, decoded_block, decoded_size );
         pDestination += decoded_size;
         bytes_written += decoded_size;
         remaining_destination -= decoded_size;

         // Mover el puntero de la fuente al siguiente bloque
         pSource += input_size;
         remaining_source -= input_size;
      }

      return bytes_written;
   }

   void EncodeCkf32Ts( int year, int month, int day, int day_milliseconds, BYTE ckf32ts[ 8 ] )
   {
      ckf32ts[ 0 ] = base32_crockford_alphabet[ (year -2020)  & 0x1F ]; 
      ckf32ts[ 1 ] = base32_crockford_alphabet[ month & 0x1F ];
      ckf32ts[ 2 ] = base32_crockford_alphabet[ day & 0x1F ];
      int v = min( max( 0, day_milliseconds ), 86400000 ) / 3;
      ckf32ts[ 7 ] = base32_crockford_alphabet[ v & 0x1F ];
      v >>= 5;
      ckf32ts[ 6 ] = base32_crockford_alphabet[ v & 0x1F ];
      v >>= 5;
      ckf32ts[ 5 ] = base32_crockford_alphabet[ v & 0x1F ];
      v >>= 5;
      ckf32ts[ 4 ] = base32_crockford_alphabet[ v & 0x1F ];
      v >>= 5;
      ckf32ts[ 3 ] = base32_crockford_alphabet[ v & 0x1F ];
   }

   void DecodeCkf32Ts( BYTE ckf32ts[ 8 ], int & year, int & month, int & day, int & day_milliseconds )
   {
      year = crockford_char_to_index( ckf32ts[ 0 ] ) + 2020;
      month = crockford_char_to_index( ckf32ts[ 1 ] );
      day = crockford_char_to_index( ckf32ts[ 2 ] );
      int v =crockford_char_to_index( ckf32ts[ 3 ] ); v <<= 5;
      v |= crockford_char_to_index( ckf32ts[ 3 ] ); v <<= 5;
      v |= crockford_char_to_index( ckf32ts[ 4 ] ); v <<= 5;
      v |= crockford_char_to_index( ckf32ts[ 5 ] ); v <<= 5;
      v |= crockford_char_to_index( ckf32ts[ 6 ] );
      day_milliseconds = max( 0, min( (v * 3) , 86399999 ) );
   }

}
// ------------------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------------
OT4XB_API int ot4xb_base32_encode_required_length( int nSrcLen )
{
   if( nSrcLen < 1 )
   {
      return 0;
   }
   return (int) base32_ns::encode_required_size( (int) nSrcLen );
}
// -------------------------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL ot4xb_base32_encode_with_table( LPSTR pTable, LPBYTE pSrc, int nSrcLen, LPSTR szDest, int* pnDestLen, DWORD flags)
{
   if( nSrcLen < 1 )
   {
      return FALSE;
   }
   if( pnDestLen[ 0 ] < ot4xb_base32_encode_required_length( nSrcLen ) )
   {
      return FALSE;
   }
   pnDestLen[ 0 ] = base32_ns::encode_to_buffer( pTable, pSrc, (DWORD) nSrcLen, szDest, pnDestLen[ 0 ] , flags );
   return TRUE;
}
// -------------------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------------
// Calcula el tamaño requerido para decodificar un texto Base32
OT4XB_API int ot4xb_base32_decode_required_length(int nEncodedLen) 
{
    if (nEncodedLen < 1) {
        return 0; // No hay nada que decodificar
    }
    return (int)base32_ns::decode_required_size((DWORD)nEncodedLen);
}
// -------------------------------------------------------------------------------------------------------------------------------------
// Decodifica un texto Base32 usando una tabla proporcionada
OT4XB_API BOOL ot4xb_base32_decode_with_table(LPSTR pTable, LPCSTR szEncoded, int nEncodedLen, LPBYTE pDest, int* pnDestLen, DWORD flags) {
    if (nEncodedLen < 1 || !szEncoded || !pDest || !pnDestLen) {
        return FALSE; // Parámetros inválidos
    }

    // Verificar si el buffer de destino tiene suficiente espacio
    int requiredLength = ot4xb_base32_decode_required_length(nEncodedLen);
    if (pnDestLen[0] < requiredLength) {
        return FALSE; // Buffer de destino demasiado pequeño
    }

    DWORD decodedLength = base32_ns::decode_to_buffer(
        pTable, szEncoded, (DWORD)nEncodedLen, pDest, (DWORD)pnDestLen[0], flags
    );

    if (decodedLength == 0) {
        return FALSE; // Error durante la decodificación
    }

    pnDestLen[0] = (int)decodedLength; // Actualizar el tamaño real de los datos decodificados
    return TRUE; // Decodificación exitosa
}

