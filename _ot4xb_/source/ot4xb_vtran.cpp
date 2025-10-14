//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
extern BYTE _lower_ansi_char_table_[ 256 ];
#define __str4dw(a,b,c,d) ( ((DWORD)(a)) | ((DWORD)(b)<<8) | ((DWORD)(c)<<16) | ((DWORD)(d)<<24) )

//----------------------------------------------------------------------------------------------------------------------
#include <ot4xb_api.h>
#define VCMP_CASE_INSENSITIVE           0x00000001
#define VCMP_NIL_TO_NULL                0x00000002
#define VCMP_IGNORE_MISSING_LEFT        0x00000004 // only for maps   
#define VCMP_IGNORE_MISSING_RIGHT       0x00000008 // only for maps

#define VCMP_LTRIM                      0x00000010
#define VCMP_RTRIM                      0x00000020   
#define VCMP_MISSING_LEFT               0x00000040 // internal ignored if user provide it
#define VCMP_MISSING_RIGHT              0x00000080 // internal ignored if user provide it


#define VCMP_COMPARE_MAP                0x00000100   // when object is expando  or array is k->v pair list  // NOT IMPLEMENTED YET !!!!!!!!
#define VCMP_STRINGIFY_CHANGES          0x00000200  
#define VCMP_JUST_DUMP_VALUES           0x00000400   // internal ignored if user provide it

#define VCMP_USE_PRECISSION_BYTE        0x00001000   
#define VCMP_USE_MINIMAL_REPRESENTATION 0x00002000   
#define VCMP_DOUBLE_PRECISSION_BYTE     0x000F0000   
#define VCMP_GET_PRECISSION(f)  ( ( (f) & VCMP_USE_PRECISSION_BYTE ) ? ( ( (f) & VCMP_DOUBLE_PRECISSION_BYTE ) >> 16 ) : 0x04 )
#define VCMP_SET_PRECISSION(flags, n)   ( (flags) = ( ((flags) & ~VCMP_DOUBLE_PRECISSION_BYTE) | VCMP_USE_PRECISSION_BYTE | (((n) & 0x0F) << 16) ) )

#define VCMP_CAST_BYTE_MASK             0x00F00000   
#define VCMP_CAST_TO_LEFT               0x00100000   
#define VCMP_CAST_TO_RIGHT              0x00200000   
#define VCMP_CAST_TO_STRING             0x00300000   
#define VCMP_CAST_TO_STRING_UPPER       0x00400000   
#define VCMP_CAST_TO_STRING_LOWER       0x00500000   
#define VCMP_CAST_TO_STRING_DATE8       0x00600000   
#define VCMP_CAST_TO_STRING_DATE10      0x00700000   
#define VCMP_CAST_TO_STRING_YES_NO      0x00800000   
#define VCMP_CAST_TO_STRING_TRUE_FALSE  0x00900000   
#define VCMP_CAST_TO_INTEGER            0x00A00000   
#define VCMP_CAST_TO_DOUBLE             0x00B00000   
#define VCMP_CAST_TO_DATE               0x00C00000   
#define VCMP_CAST_TO_LOGICAL            0x00D00000   






namespace vcmp_ns
{
   DWORD __vtran_parse_flags( LPCSTR szFlags );
   DWORD __type_coercion( DWORD * pt1, DWORD * pt2 , DWORD & flags );
   BOOL compare_values( ContainerHandle v1, ContainerHandle v2, DWORD flags );
   BOOL compare_simple_values( ContainerHandle v1, DWORD t1, ContainerHandle v2, DWORD t2, DWORD flags);

   BOOL compare_character_values( ContainerHandle v1, ContainerHandle v2, DWORD flags);
   BOOL compare_numeric_values( ContainerHandle v1, ContainerHandle v2, DWORD flags );
   BOOL compare_logical_values( ContainerHandle v1, ContainerHandle v2);
   BOOL compare_date_values( ContainerHandle v1, ContainerHandle v2 );
   BOOL compare_generic_values( ContainerHandle v1, ContainerHandle v2 );

   void* to_string( ContainerHandle con, DWORD flags, LPSTR& str, DWORD& len, BYTE small_buffer[ 256 ] );
   void* to_date_string( ContainerHandle con, DWORD flags, LPSTR& str, DWORD& len, BYTE small_buffer[ 256 ] );

   inline static double get_precission_epsilon( DWORD flags )
   {
      static const double eps[ ] = { 1.0,1e-1,1e-2,1e-3,1e-4,1e-5,1e-6,1e-7,1e-8,1e-9,1e-10,1e-11,1e-12,1e-13,1e-14,1e-15 };
      return eps[ VCMP_GET_PRECISSION( flags ) ];
   }
   inline static const char* get_precission_template( DWORD flags )
   {
      static const char* tpl[ ] = { "%.0f", "%.1f", "%.2f", "%.3f", "%.4f", "%.5f", "%.6f", "%.7f","%.8f", "%.9f", "%.10f", "%.11f", "%.12f", "%.13f", "%.14f", "%.15f" };
      if( flags & VCMP_USE_MINIMAL_REPRESENTATION )
      {
         return "%.15g";
      }
      return tpl[ VCMP_GET_PRECISSION( flags ) ];
   }





}
// --------------------------------------------------------------------------------------------------------------------
void* vcmp_ns::to_string( ContainerHandle con, DWORD flags, LPSTR& str, DWORD& len, BYTE small_buffer[ 256 ] )
{
   DWORD t;
   _conType( con, &t );
   void* buffer = 0;
   switch( t & 0xFF )
   {
      case XPP_CHARACTER:
      {
         DWORD cb = 0;
         LPBYTE p = 0;
         if( _conRLockC( con, (LPSTR*) &p, &cb ) == 0 )
         {
            if( flags & VCMP_LTRIM )
            {
               ByteMapTable_RO_LtrimEx( 0, p, cb, p, cb );
            }
            if( flags & VCMP_RTRIM )
            {
               ByteMapTable_RO_RtrimEx( 0, p, cb, p, cb );
            }
            len = cb;
            if( cb < sizeof( small_buffer ) )
            {
               _bcopy( small_buffer, p, cb );
               small_buffer[ cb ] = 0;
               str = (LPSTR) small_buffer;
            }
            else
            {
               buffer = _xgrab( cb + 1 );
               _bcopy( (LPBYTE) buffer, p, cb );
               str = (LPSTR) buffer;
            }
            _conRUnlockC( con );
         }
         else
         {
            len = 0;
            small_buffer[ 0 ] = 0;
            str = (LPSTR) small_buffer;
         }
         return buffer;
      }
      case XPP_NUMERIC:
      {
         str = (LPSTR) small_buffer;
         len = 0;
         if( t & _xpp_DOUBLE )
         {
            double nd = 0.0;
            _conGetND( con, &nd );
            len = sprintf_s( str, sizeof( small_buffer ), "%.15g", nd );
         }
         else
         {
            LONG nl = 0;
            _conGetNL( con, &nl );
            len = sprintf_s( str, sizeof( small_buffer ), "%i", nl );
         }
         return buffer;
      }
      case XPP_LOGICAL:
      {
         str = (LPSTR) small_buffer;
         len = 0;
         BOOL  b = 0;
         _conGetL( con, &b );
         len = sprintf_s( str, sizeof( small_buffer ), "%s", ( b ? ".T." : ".F." ) );
         return buffer;
      }
      case XPP_DATE:
      {
         return to_date_string( con, flags, str, len, small_buffer );
      }
      default:
      {
         ContainerHandle cc = _conPutC( NULLCONTAINER, "" );
         _conCallPa( cc, "var2char", 1, &con );
         DWORD tt;
         _conType( cc, &tt );
         if( tt & XPP_CHARACTER )
         {
            buffer = to_string( cc, flags, str, len, small_buffer );
         }
         else
         {
            str = (LPSTR) small_buffer;
            len = 0;
            len = sprintf_s( str, sizeof( small_buffer ), "Error converting value" );
         }
         _conRelease( cc );
         return buffer;
      }
   }
}
// --------------------------------------------------------------------------------------------------------------------
void* vcmp_ns::to_date_string( ContainerHandle con, DWORD, LPSTR& str, DWORD& len, BYTE small_buffer[ 256 ] )
{
   DWORD t;
   _conType( con, &t );
   ZeroMemory( small_buffer, 9 );
   str = (LPSTR) small_buffer;
   len = 0;
   switch( t & 0xFF )
   {
      case XPP_CHARACTER:
      {
         DWORD cb = 0;
         LPBYTE p = 0;
         if( _conRLockC( con, (LPSTR*) &p, &cb ) == 0 )
         {
            LPSTR pd = str;
            DWORD cbd = 0;
            for( ; *p && cbd < 9; p++ )
            {
               if( *p >= '0' && *p <= '9' )
               {
                  *pd = *p; pd++; *pd = 0; cbd++;
               }
            }
            _conUnlockC( con ); p = 0;

            if( cbd == 8 )
            {
               ContainerHandle cond = _conPutDS( NULLCONTAINER, str );
               len = ( !_conGetDS( cond, str ) && str[ 0 ] >= '0' && str[ 0 ] <= '9' ) ? 8 : 0;
               str[ len ] = 0;
               _conRelease( cond );
               return 0;
            }
         }
         len = 8; str[ len ] = 0;
         return 0;
      }
      case XPP_DATE:
      {
         len = ( !_conGetDS( con, str ) && str[ 0 ] >= '0' && str[ 0 ] <= '9' ) ? 8 : 0;
         str[ len ] = 0;
         return 0;
      }
      default:
      {
         small_buffer[ 0 ] = 0;
         str = (LPSTR) small_buffer;
         len = 0;
         return 0;
      }
   }
}



// --------------------------------------------------------------------------------------------------------------------
// -> lMatch
BOOL vcmp_ns::compare_character_values( ContainerHandle v1, ContainerHandle v2, DWORD flags)
{
   LPSTR s1, s2;
   DWORD cb1, cb2;
   BYTE small1[ 256 ];
   BYTE small2[ 256 ];

   void* buffer_1 = to_string( v1, flags, s1, cb1, small1 );
   void* buffer_2 = to_string( v2, flags, s2, cb2, small2 );
   BOOL match = FALSE;
   if( s1 && s2 && cb1 && cb2 && cb1 == cb2 )
   {
      match = TRUE;
      if( flags & VCMP_CASE_INSENSITIVE )
      {
         for( DWORD dw = 0; match && dw < cb1; dw++ )
         {
            if( _lower_ansi_char_table_[ (BYTE) s1[ dw ] ] != _lower_ansi_char_table_[ (BYTE) s2[ dw ] ] )
            {
               match = FALSE;
            }
         }
      }
      else
      {
         for( DWORD dw = 0; match && dw < cb1; dw++ )
         {
            if( (BYTE) s1[ dw ] != (BYTE) s2[ dw ] )
            {
               match = FALSE;
            }
         }

      }
   }
   if( buffer_1 )
   {
      _xfree( buffer_1 );
      buffer_1 = 0;
   }
   if( buffer_2 )
   {
      _xfree( buffer_2 );
      buffer_1 = 0;
   }
   return  match;
}
// --------------------------------------------------------------------------------------------------------------------
BOOL vcmp_ns::compare_numeric_values( ContainerHandle v1, ContainerHandle v2, DWORD flags)
{
   DWORD t1, t2;
   BOOL match = FALSE;
   double epsilon = get_precission_epsilon( flags );
   // LPCSTR tpl = get_precission_template( flags );

   _conType( v1, &t1 );
   _conType( v2, &t2 );
   if( ( t1 & XPP_NUMERIC ) && ( t2 & XPP_NUMERIC ) && ( ( t1 | t2 ) & _xpp_DOUBLE ) )
   {
      double nd1, nd2;

      // char precission_template[ 8 ] = "";
      _conGetND( v1, &nd1 );
      _conGetND( v2, &nd2 );
      match = fabs( nd1 - nd2 ) < epsilon;
      return match;
   }

   if( ( t1 & ( XPP_NUMERIC | XPP_LOGICAL ) ) && ( t2 & ( XPP_NUMERIC | XPP_LOGICAL ) ) )
   {
      LONG n1, n2;

      _conGetLongOrBool( v1, &n1 );
      _conGetLongOrBool( v2, &n2 );
      match = ( n1 == n2 );
      return match;
   }
   return match;
}
// --------------------------------------------------------------------------------------------------------------------

BOOL vcmp_ns::compare_logical_values( ContainerHandle v1, ContainerHandle v2)
{
   DWORD t1, t2;
   BOOL match = FALSE;
   _conType( v1, &t1 );
   _conType( v2, &t2 );

   if( ( t1 & ( XPP_NUMERIC | XPP_LOGICAL ) ) && ( t2 & ( XPP_NUMERIC | XPP_LOGICAL ) ) )
   {
      LONG n1, n2;
      _conGetLongOrBool( v1, &n1 );
      _conGetLongOrBool( v2, &n2 );
      match = ( n1 == n2 );
      return match;
   }
   return match;
}
BOOL vcmp_ns::compare_date_values( ContainerHandle v1, ContainerHandle v2)
{
   char s1[16]; ZeroMemory( s1,sizeof(s1));
   char s2[16]; ZeroMemory( s2,sizeof(s2));
   _conGetDS( v1, s1 );
   _conGetDS( v2, s2 );
   for( DWORD i = 0; i < 8; i++ )
   {
      if( s1[ i ] != s2[ i ] )
      {
         return FALSE;
      }
   }
   return TRUE;
}
BOOL vcmp_ns::compare_generic_values( ContainerHandle v1, ContainerHandle v2)
{
   LONG n = 0;
   if( !_conCompare( &n, v1, v2 ) )
   {
      return ( n == 0 );
   }
   return FALSE;
}



// --------------------------------------------------------------------------------------------------------------------
BOOL vcmp_ns::compare_simple_values( ContainerHandle v1, DWORD t1, ContainerHandle v2, DWORD t2, DWORD flags)
{


   if( ( flags & VCMP_MISSING_LEFT ) && ( flags & VCMP_MISSING_RIGHT ) )
   {
      return TRUE;
   }
   if( ( flags & VCMP_MISSING_LEFT ) && ( flags & VCMP_IGNORE_MISSING_LEFT ) )
   {
      return TRUE;
   }
   if( ( flags & VCMP_MISSING_RIGHT ) && ( flags & VCMP_IGNORE_MISSING_RIGHT ) )
   {
      return TRUE;
   }
   if( ( t1 & XPP_UNDEF ) && ( t2 & XPP_UNDEF ) )
   {
      return TRUE;
   }

   switch( ( flags & VCMP_CAST_BYTE_MASK ) )
   {
      case VCMP_CAST_TO_LEFT:
      {
         t2 = t1;
         break;
      }
      case VCMP_CAST_TO_RIGHT:
      {
         t1 = t2;
         break;
      }
      case VCMP_CAST_TO_STRING:
      {
         t1 = t2 = XPP_CHARACTER;
         break;
      }
      case VCMP_CAST_TO_STRING_UPPER:
      {
         t1 = t2 = XPP_CHARACTER;
         flags |= VCMP_CASE_INSENSITIVE;
         break;
      }
      case VCMP_CAST_TO_STRING_LOWER:
      {
         t1 = t2 = XPP_CHARACTER;
         flags |= VCMP_CASE_INSENSITIVE;
         break;
      }
      case VCMP_CAST_TO_STRING_DATE8:
      {
         t1 = t2 = XPP_CHARACTER;
         break;
      }
      case VCMP_CAST_TO_STRING_DATE10:
      {
         t1 = t2 = XPP_CHARACTER;
         break;
      }
      case VCMP_CAST_TO_STRING_YES_NO:
      {
         t1 = t2 = XPP_CHARACTER;
         break;
      }
      case VCMP_CAST_TO_STRING_TRUE_FALSE:
      {
         t1 = t2 = XPP_CHARACTER;
         break;
      }
      case VCMP_CAST_TO_INTEGER:
      {
         t1 = t2 = XPP_NUMERIC;
         break;
      }
      case VCMP_CAST_TO_DOUBLE:
      {
         t1 = t2 = XPP_NUMERIC | _xpp_DOUBLE;
         break;
      }
      case VCMP_CAST_TO_DATE:
      {
         t1 = t2 = XPP_DATE;
         break;
      }

      case VCMP_CAST_TO_LOGICAL:
      {
         t1 = t2 = XPP_CHARACTER;
         break;
      }
   }

   if( flags & VCMP_NIL_TO_NULL )
   {
      t1 = ( t1 & XPP_UNDEF ) ? ( t2 & 0xFF ) : t1;
      t2 = ( t2 & XPP_UNDEF ) ? ( t1 & 0xFF ) : t2;
   }


   if( ( t1 & 0xFF ) != ( t2 & 0xFF ) )
   { // diferent types and no possible casting
         return FALSE;
   }

   switch( t1 & 0xFF )
   {
      case XPP_CHARACTER:
      {
         return compare_character_values( v1, v2, flags);
      }
      case XPP_NUMERIC:
      {
         return compare_numeric_values( v1, v2, flags);
      }
      case XPP_LOGICAL:
      {
         return compare_logical_values( v1, v2);
      }
      case XPP_DATE:
      {
         return compare_date_values( v1, v2);
      }
      default:
      {
         return compare_generic_values( v1, v2 );
      }
   }
}

// --------------------------------------------------------------------------------------------------------------------
BOOL vcmp_ns::compare_values( ContainerHandle v1, ContainerHandle v2, DWORD flags)   // -> lMatch
{
   BOOL match = FALSE;
   DWORD t1, t2;

   flags &= ~( VCMP_MISSING_LEFT | VCMP_MISSING_RIGHT | VCMP_JUST_DUMP_VALUES );  // internal use so clear if provided directly 

   _conType( v1, &t1 );
   _conType( v2, &t2 );

   if( ( flags & VCMP_COMPARE_MAP ) && ( ( t1 | t2 ) & ( XPP_ARRAY | XPP_OBJECT ) ) )
   {
      return FALSE;
      // TO-DO: traverse internal elements 

   }
   flags &= ~VCMP_COMPARE_MAP;

   match = compare_simple_values( v1, t1, v2, t2, flags );

   return match;
}
// --------------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_( __VCMP )	 // __vcmp( 1 v1 , 2 v2 , 3 flags  ) ->  lMatch
{
   TXppParamList xpp( pl, 4 );
   ContainerHandle v1 = xpp[ 1 ]->con();
   ContainerHandle v2 = xpp[ 2 ]->con();
   DWORD flags = 0;
   if( xpp[ 3 ]->CheckType( XPP_NUMERIC | XPP_CHARACTER ) )
   {
      if( xpp[ 3 ]->CheckType( XPP_CHARACTER ) )
      {
         LPCSTR pflags = (LPCSTR) xpp[ 3 ]->LockStr();
         flags = vcmp_ns::__vtran_parse_flags( pflags );

      }
      else
      {
         flags = xpp[ 3 ]->GetDWord();
      }
   }
   BOOL result = vcmp_ns::compare_values( v1, v2, flags);
   xpp[ 0 ]->PutBool( result );
}



// -----------------------------------------------------------------------------------------------------------------
// __vtran( v , flags )
_XPP_REG_FUN_( __VTRAN )
{
   TXppParamList xpp( pl, 4 );
   ContainerHandle v1 = xpp[ 1 ]->con();
   DWORD flags = 0;
   if( xpp[ 2 ]->CheckType( XPP_NUMERIC | XPP_CHARACTER ) )
   {
      if( xpp[ 2 ]->CheckType( XPP_CHARACTER ) )
      {
         LPCSTR pflags = (LPCSTR) xpp[ 2 ]->LockStr();
         flags = vcmp_ns::__vtran_parse_flags( pflags );
      }
      else
      {
         flags = xpp[ 2 ]->GetDWord();
      }
   }
   LPSTR p = 0;
   DWORD cb = 0;
   BYTE small_buffer[ 256 ];
   void* buffer = vcmp_ns::to_string( v1, flags, p, cb, small_buffer );
   if( p && cb )
   {
      xpp[ 0 ]->PutStrLen( p, cb );
   }
   else 
   {
      xpp[ 0 ]->PutStr("");
   }
   if( buffer )
   {
      _xfree( buffer );
   }


}
// --------------------------------------------------------------------------------------------------------------------

DWORD vcmp_ns::__vtran_parse_flags( LPCSTR p )
{
   DWORD flags = 0;
   DWORD cast = 0;

   if( !p )
   {
      return 0;
   }
   while( *p )
   {
      char buffer[ 256 ] = { 0 };
      DWORD cb = 0;
      for( ; ( cb < ( sizeof( buffer ) - 1 ) ) && *p && *p != ',' && *p != ';' && *p != '|'; p++ )
      {
         char ch = _lower_ansi_char_table_[ (BYTE) *p ];
         if( ( ch >= 'a' && ch <= 'z' ) || ( ch >= '0' && ch <= '9' ) )
         {
            buffer[ cb ] = ch;
            cb++;
         }
      }
      if( *p == ',' || *p == ';' || *p == '|' )
      {
         p++;
      }
      if( cb )
      {
         DWORD prefix = 0;
         _bcopy( (LPBYTE) &prefix, (LPBYTE) buffer, sizeof( prefix ) );
         switch( prefix )
         {
            case __str4dw( 'a', 'l', 'l', 't' ):
            {
               flags |= VCMP_LTRIM | VCMP_RTRIM;
               break;
            }
            case __str4dw( 'l', 't', 'r', 'i' ):
            {
               flags |= VCMP_LTRIM;
               break;
            }
            case __str4dw( 'r', 't', 'r', 'i' ):
            {
               flags |= VCMP_RTRIM;
               break;
            }
            case __str4dw( 'c', 0, 0, 0 ):
            case __str4dw( 'm', 0, 0, 0 ):
            case __str4dw( 's', 't', 'r', 0 ):
            case __str4dw( 's', 't', 'r', 'i' ):
            case __str4dw( 't', 'o', 's', 't' ):
            case __str4dw( 'c', 'h', 'a', 'r' ):
            case __str4dw( 't', 'o', 'c', 'h' ):
            {
               if( ( cast & 0xFF ) != XPP_CHARACTER ) { cast = XPP_CHARACTER; }
               break;
            }
            case __str4dw( 'l', 'o', 'w', 'e' ):
            case __str4dw( 't', 'o', 'l', 'o' ):
            {
               cast = VCMP_CAST_TO_STRING_LOWER | XPP_CHARACTER;
               break;
            }
            case __str4dw( 'u', 'p', 'p', 'e' ):
            case __str4dw( 't', 'o', 'u', 'p' ):
            {
               cast = VCMP_CAST_TO_STRING_UPPER | XPP_CHARACTER;
               break;
            }
            case __str4dw( 'n', 0, 0, 0 ):
            case __str4dw( 'n', 'u', 'm', 0 ):
            case __str4dw( 'n', 'u', 'm', 'e' ):
            case __str4dw( 't', 'o', 'n', 'u' ):
            {
               if( ( cast & 0xFF ) != XPP_NUMERIC ) { cast = XPP_NUMERIC; }
               break;
            }
            case __str4dw( 'i', 'n', 't', 0 ):
            case __str4dw( 'i', 'n', 't', 'e' ):
            {
               cast = VCMP_CAST_TO_INTEGER | XPP_NUMERIC;
               break;
            }
            case __str4dw( 'd', 'o', 'u', 'b' ):
            case __str4dw( 'd', 'e', 'c', 'i' ):
            case __str4dw( 'f', 'l', 'o', 'a' ):
            {
               cast = VCMP_CAST_TO_DOUBLE | XPP_NUMERIC;
               break;
            }
            case __str4dw( 'l', 0, 0, 0 ):
            case __str4dw( 'b', 'o', 'o', 'l' ):
            case __str4dw( 'l', 'o', 'g', 'i' ):
            {
               cast = VCMP_CAST_TO_LOGICAL | XPP_LOGICAL;
               break;

            }
            case __str4dw( 'y', 'n', 0, 0 ):
            case __str4dw( 'y', 'e', 's', 0 ):
            case __str4dw( 'y', 'e', 's', 'n' ):
            {
               cast = VCMP_CAST_TO_STRING_YES_NO | XPP_CHARACTER;
               break;
            }

            case __str4dw( 't', 'f', 0, 0 ):
            case __str4dw( 't', 'r', 'u', 'e' ):
            {
               cast = VCMP_CAST_TO_STRING_TRUE_FALSE | XPP_CHARACTER;
               break;
            }

            case __str4dw( 'd', 0, 0, 0 ):
            case __str4dw( 's', 't', 'o', 'd' ):
            {
               cast = VCMP_CAST_TO_DATE | XPP_DATE;
               break;
            }
            case __str4dw( 'd', 't', 'o', 's' ):
            {
               cast = VCMP_CAST_TO_STRING_DATE8 | XPP_CHARACTER;
               break;
            }
            case __str4dw( 'd', 'a', 't', 'e' ):
            {
               if( _xstrcmp( buffer, "date8" ) == 0 )
               {
                  cast = VCMP_CAST_TO_STRING_DATE8 | XPP_CHARACTER;
                  break;
               }
               if( _xstrcmp( buffer, "date10" ) == 0 )
               {
                  cast = VCMP_CAST_TO_STRING_DATE10 | XPP_CHARACTER;
                  break;
               }
               cast = VCMP_CAST_TO_DATE | XPP_DATE;
               break;
            }

            default:
            {
               LPSTR tk = _mk_ptr_( LPSTR, buffer, ( prefix == __str4dw( 'v', 'c', 'm', 'p' ) ) ? 0 : 4 );

               if( ( _xstrcmp( tk, "caseinsensitive" ) == 0 ) || ( _xstrcmp( tk, "nocase" ) == 0 ) )
               {
                  flags |= VCMP_CASE_INSENSITIVE;
                  break;
               }
               if( _xstrcmp( tk, "niltonull" ) == 0 )
               {
                  flags |= VCMP_NIL_TO_NULL;
                  break;
               }
               if( _xstrcmp( tk, "ignoremissingleft" ) == 0 )
               {
                  flags |= VCMP_IGNORE_MISSING_LEFT;
                  break;
               }
               if( _xstrcmp( tk, "ignoremissingright" ) == 0 )
               {
                  flags |= VCMP_IGNORE_MISSING_RIGHT;
                  break;
               }
               if( prefix == __str4dw( 'v', 'c', 'm', 'p' ) )
               {
                  if( _xstrcmp( tk, "ltrim" ) == 0 )
                  {
                     flags |= VCMP_LTRIM;
                     break;
                  }
                  if( _xstrcmp( tk, "rtrim" ) == 0 )
                  {
                     flags |= VCMP_RTRIM;
                     break;
                  }
               }
               if( _xstrcmp( tk, "comparemap" ) == 0 )
               {
                  flags |= VCMP_COMPARE_MAP;
                  break;
               }
               if( _xstrcmp( tk, "stringifychanges" ) == 0 )
               {
                  flags |= VCMP_STRINGIFY_CHANGES;
                  break;
               }
               if( _xstrcmp( tk, "useprecissionbyte" ) == 0 )
               {
                  flags |= VCMP_USE_PRECISSION_BYTE; break;
               }
               if( _xstrcmp( tk, "useminimalrepresentation" ) == 0 )
               {
                  flags |= VCMP_USE_MINIMAL_REPRESENTATION;
                  break;
               }
               if( _xstrcmp( tk, "casttoleft" ) == 0 )
               {
                  cast = VCMP_CAST_TO_LEFT;
                  break;
               }
               if( _xstrcmp( tk, "casttoright" ) == 0 )
               {
                  cast = VCMP_CAST_TO_RIGHT;
                  break;
               }
               if( _xstrcmp( tk, "casttostring" ) == 0 )
               {
                  cast = VCMP_CAST_TO_STRING | XPP_CHARACTER;
                  break;
               }
               if( _xstrcmp( tk, "casttostringupper" ) == 0 )
               {
                  cast = VCMP_CAST_TO_STRING_UPPER | XPP_CHARACTER;
                  break;
               }
               if( _xstrcmp( tk, "casttostringlower" ) == 0 )
               {
                  cast = VCMP_CAST_TO_STRING_LOWER | XPP_CHARACTER;
                  break;
               }
               if( _xstrcmp( tk, "casttostringdate8" ) == 0 )
               {
                  cast = VCMP_CAST_TO_STRING_DATE8 | XPP_CHARACTER;
                  break;
               }
               if( _xstrcmp( tk, "casttostringdate10" ) == 0 )
               {
                  cast = VCMP_CAST_TO_STRING_DATE10 | XPP_CHARACTER;
                  break;
               }
               if( _xstrcmp( tk, "casttostringyesno" ) == 0 )
               {
                  cast = VCMP_CAST_TO_STRING_YES_NO | XPP_CHARACTER;
                  break;
               }
               if( _xstrcmp( tk, "casttostringtruefalse" ) == 0 )
               {
                  cast = VCMP_CAST_TO_STRING_TRUE_FALSE | XPP_CHARACTER;
                  break;
               }
               if( _xstrcmp( tk, "casttointeger" ) == 0 )
               {
                  cast = VCMP_CAST_TO_INTEGER | XPP_NUMERIC;
                  break;
               }
               if( _xstrcmp( tk, "casttodouble" ) == 0 )
               {
                  cast = VCMP_CAST_TO_DOUBLE | XPP_NUMERIC;
                  break;
               }
               if( _xstrcmp( tk, "casttodate" ) == 0 )

               {
                  cast = VCMP_CAST_TO_DATE | XPP_DATE;
                  break;
               }
               if( _xstrcmp( tk, "casttological" ) == 0 )

               {
                  cast = VCMP_CAST_TO_LOGICAL | XPP_LOGICAL;
                  break;
               }
               
               if( __str4dw( tk[ 0 ], tk[ 1 ], tk[ 2 ], tk[ 3 ] )  == __str4dw( 's', 'e', 't', 'p' ) &&
                   __str4dw( tk[ 4 ], tk[ 5 ], tk[ 6 ], tk[ 7 ] )  == __str4dw( 'r', 'e', 'c', 'i' ) && 
                   __str4dw( tk[ 8 ], tk[ 9 ], tk[ 10 ], tk[11 ] ) == __str4dw( 's', 's', 'i', 'o' ) &&
                   tk[12] == 'n' )
               {
                  DWORD nn = _mk_ptr_( LPDWORD, tk, 13 )[ 0 ];
                  if( nn == __str4dw('0',0,0,0) || nn ==  __str4dw( '0', 'x', '0', '0' ) || nn == __str4dw( '0', '0', 0, 0 ) )
                  {
                     VCMP_SET_PRECISSION( flags, 0x00 );
                     break;
                  }
                  if( nn == __str4dw( '1', 0, 0, 0 ) || nn == __str4dw( '0', 'x', '0', '1' ) || nn == __str4dw( '0', '1', 0, 0 ) )
                  {
                     VCMP_SET_PRECISSION( flags, 0x01 );
                     break;
                  }
                  if( nn == __str4dw( '2', 0, 0, 0 ) || nn == __str4dw( '0', 'x', '0', '2' ) || nn == __str4dw( '0', '2', 0, 0 ) )
                  {
                     VCMP_SET_PRECISSION( flags, 0x02 );
                     break;
                  }
                  if( nn == __str4dw( '3', 0, 0, 0 ) || nn == __str4dw( '0', 'x', '0', '3' ) || nn == __str4dw( '0', '3', 0, 0 ) )
                  {
                     VCMP_SET_PRECISSION( flags, 0x03 );
                     break;
                  }
                  if( nn == __str4dw( '4', 0, 0, 0 ) || nn == __str4dw( '0', 'x', '0', '4' ) || nn == __str4dw( '0', '4', 0, 0 ) )
                  {
                     VCMP_SET_PRECISSION( flags, 0x04 );
                     break;
                  }
                  if( nn == __str4dw( '5', 0, 0, 0 ) || nn == __str4dw( '0', 'x', '0', '5' ) || nn == __str4dw( '0', '5', 0, 0 ) )
                  {
                     VCMP_SET_PRECISSION( flags, 0x05 );
                     break;
                  }
                  if( nn == __str4dw( '6', 0, 0, 0 ) || nn == __str4dw( '0', 'x', '0', '6' ) || nn == __str4dw( '0', '6', 0, 0 ) )
                  {
                     VCMP_SET_PRECISSION( flags, 0x06 );
                     break;
                  }
                  if( nn == __str4dw( '7', 0, 0, 0 ) || nn == __str4dw( '0', 'x', '0', '7' ) || nn == __str4dw( '0', '7', 0, 0 ) )
                  {
                     VCMP_SET_PRECISSION( flags, 0x07 );
                     break;
                  }
                  if( nn == __str4dw( '8', 0, 0, 0 ) || nn == __str4dw( '0', 'x', '0', '8' ) || nn == __str4dw( '0', '8', 0, 0 ) )
                  {
                     VCMP_SET_PRECISSION( flags, 0x08 );
                     break;
                  }
                  if( nn == __str4dw( '9', 0, 0, 0 ) || nn == __str4dw( '0', 'x', '0', '9' ) || nn == __str4dw( '0', '9', 0, 0 ) )
                  {
                     VCMP_SET_PRECISSION( flags, 0x09 );
                     break;
                  }
                  if( nn == __str4dw( '1', '0', 0, 0 ) || nn == __str4dw( '0', 'x', '0', 'A' ) || nn == __str4dw( '0', 'A', 0, 0 ) )
                  {
                     VCMP_SET_PRECISSION( flags, 0x0A );
                     break;
                  }
                  if( nn == __str4dw( '1', '1', 0, 0 ) || nn == __str4dw( '0', 'x', '0', 'B' ) || nn == __str4dw( '0', 'B', 0, 0 ) )
                  {
                     VCMP_SET_PRECISSION( flags, 0x0B );
                     break;
                  }
                  if( nn == __str4dw( '1', '2', 0, 0 ) || nn == __str4dw( '0', 'x', '0', 'C' ) || nn == __str4dw( '0', 'C', 0, 0 ) )
                  {
                     VCMP_SET_PRECISSION( flags, 0x0C );
                     break;
                  }
                  if( nn == __str4dw( '1', '3', 0, 0 ) || nn == __str4dw( '0', 'x', '0', 'D' ) || nn == __str4dw( '0', 'D', 0, 0 ) )
                  {
                     VCMP_SET_PRECISSION( flags, 0x0D );
                     break;
                  }
                  if( nn == __str4dw( '1', '4', 0, 0 ) || nn == __str4dw( '0', 'x', '0', 'E' ) || nn == __str4dw( '0', 'E', 0, 0 ) )
                  {
                     VCMP_SET_PRECISSION( flags, 0x0E );
                     break;
                  }
                  if( nn == __str4dw( '1', '5', 0, 0 ) || nn == __str4dw( '0', 'x', '0', 'F' ) || nn == __str4dw( '0', 'F', 0, 0 ) )
                  {
                     VCMP_SET_PRECISSION( flags, 0x0F );
                     break;
                  }
                  break;
               }
            }
         }
      }
   }
   switch( cast & 0xFF )
   {
      case XPP_CHARACTER:
      {
         if( !( cast & VCMP_CAST_BYTE_MASK ) )
         {
            cast = VCMP_CAST_TO_STRING;
         }
         break;
      }
      case XPP_NUMERIC:
      {
         if( !( cast & VCMP_CAST_BYTE_MASK ) )
         {
            cast = VCMP_CAST_TO_DOUBLE;
         }
         break;
      }
      case XPP_LOGICAL:
      {
         if( !( cast & VCMP_CAST_BYTE_MASK ) )
         {
            cast = VCMP_CAST_TO_LOGICAL;
         }
         break;
      }
      case XPP_DATE:
      {
         if( !( cast & VCMP_CAST_BYTE_MASK ) )
         {
            cast = VCMP_CAST_TO_DATE;
         }
         break;
      }
   }
   cast &= VCMP_CAST_BYTE_MASK;
   flags = ( flags & ~VCMP_CAST_BYTE_MASK ) | cast;
   return flags;
}
// ---------------------------------------------------------------------------------------------------------------------------------
DWORD vcmp_ns::__type_coercion(DWORD* pt1, DWORD* pt2, DWORD& flags)
{
   DWORD t1, t2;
   if( pt1 ) 
   {
      t1 = *pt1;
   } 
   else 
   {
      t1 = 0; pt1 = &t1;
   }
   if( pt2 )
   {
      t2 = *pt2;
   }
   else
   {
      t2 = 0;
      pt2 = &t2;
   }
   switch( ( flags & VCMP_CAST_BYTE_MASK ) )
   {
      case VCMP_CAST_TO_LEFT:
      {
         t2 = t1;
         break;
      }
      case VCMP_CAST_TO_RIGHT:
      {
         t1 = t2;
         break;
      }
      case VCMP_CAST_TO_STRING:
      {
         t1 = t2 = XPP_CHARACTER;
         break;
      }
      case VCMP_CAST_TO_STRING_UPPER:
      {
         t1 = t2 = XPP_CHARACTER;
         flags |= VCMP_CASE_INSENSITIVE;
         break;
      }
      case VCMP_CAST_TO_STRING_LOWER:
      {
         t1 = t2 = XPP_CHARACTER;
         flags |= VCMP_CASE_INSENSITIVE;
         break;
      }
      case VCMP_CAST_TO_STRING_DATE8:
      {
         t1 = t2 = XPP_CHARACTER;
         break;
      }
      case VCMP_CAST_TO_STRING_DATE10:
      {
         t1 = t2 = XPP_CHARACTER;
         break;
      }
      case VCMP_CAST_TO_STRING_YES_NO:
      {
         t1 = t2 = XPP_CHARACTER;
         break;
      }
      case VCMP_CAST_TO_STRING_TRUE_FALSE:
      {
         t1 = t2 = XPP_CHARACTER;
         break;
      }
      case VCMP_CAST_TO_INTEGER:
      {
         t1 = t2 = XPP_NUMERIC;
         break;
      }
      case VCMP_CAST_TO_DOUBLE:
      {
         t1 = t2 = XPP_NUMERIC | _xpp_DOUBLE;
         break;
      }
      case VCMP_CAST_TO_DATE:
      {
         t1 = t2 = XPP_DATE;
         break;
      }

      case VCMP_CAST_TO_LOGICAL:
      {
         t1 = t2 = XPP_LOGICAL;
         break;
      }
   }
   *pt1 = t1;
   *pt2 = t2;
   return t1 == t2 ? t1 : 0; 
}


