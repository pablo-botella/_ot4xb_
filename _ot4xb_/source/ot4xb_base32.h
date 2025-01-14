#pragma once
namespace base32_ns
{
   int rfc4648_char_to_index( char ch );
   int crockford_char_to_index( char ch );
   DWORD required_padding( int nBytes );
   DWORD encode_required_size( DWORD cb );
   DWORD decode_required_size( DWORD cb );
   DWORD encode_5_bytes_block( LPSTR pDigitTable, LPBYTE& pSource, DWORD& cbSource, LPSTR& pDestination, DWORD& cbMaxDestination, DWORD& output_bytes_written, DWORD flags );
   DWORD decode_8_chars_block( LPSTR pDigitTable, LPCSTR pSource, LPBYTE pDestination, DWORD flags );
   DWORD encode_to_buffer( LPSTR pDigitTable, LPBYTE pSource, DWORD cbSource, LPSTR pDestination, DWORD cbMaxDestination, DWORD flags );
   DWORD decode_to_buffer( LPSTR pDigitTable, LPCSTR pSource, DWORD cbSource, LPBYTE pDestination, DWORD cbMaxDestination, DWORD flags );
   void EncodeCkf32Ts( int year, int month, int day, int day_milliseconds, BYTE ckf32ts[ 8 ] );
   void DecodeCkf32Ts( BYTE ckf32ts[ 8 ], int& year, int& month, int& day, int& day_milliseconds );
   
}

