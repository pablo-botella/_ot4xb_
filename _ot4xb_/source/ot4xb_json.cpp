//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#define EXPANDO_FORMAT_DEBUG                         1
#define EXPANDO_FORMAT_FLAT_ARRAY_KV_ITEMS  0x00000010
#define EXPANDO_FORMAT_ENFORCE_FLAT         0x00000020
#define EXPANDO_FORMAT_PRETTY               0x01000000
#define EXPANDO_FORMAT_ND_PRECISSION(x)     ((x & 0x0F) < 16)
#define EXPANDO_FORMAT_ND_FIXED             0x00100000
#define EXPANDO_FORMAT_ND_MINIMAL           0x00200000

#include <ot4xb_api.h>
#pragma warning( disable : 4634)
#include "rapidjson/reader.h"
#include <iostream>

using namespace rapidjson;
using namespace std;
namespace json_ns
{
   
   class json_node_t
   {
      public:
      json_node_t* m_parent;
      json_node_t* m_next;
      ContainerHandle  m_name;
      DWORD            m_type;
      ContainerHandle  m_value;
      DWORD            m_array_size = 0;
      BOOL             m_sealed = FALSE;
      BOOL             m_is_root = FALSE;
      // -----------------------------------------------
      json_node_t( const char* pNodeName = 0, DWORD name_cb = 0 )
      {
         m_parent = 0;
         m_next = 0;
         m_name = 0;
         m_type = 0;
         m_value = 0;
         if( pNodeName && name_cb )
         {
            m_name = _conPutCL( m_name, (char*) pNodeName, name_cb );
         }
      };
      // -----------------------------------------------
      ~json_node_t()
      {
         __cleanup();
      };
      // -----------------------------------------------
      void __cleanup()
      {
         if( m_next )
         {
            delete m_next;
            m_next = 0;
         }
         if( m_parent )
         {
            m_parent->m_next = 0;
         }
         if( m_value ) { _conRelease( m_value ); m_value = 0; }
         if( m_name ) { _conRelease( m_name ); m_name = 0; }
      }
      // -----------------------------------------------

   };
   // -----------------------------------------------------------


   class json_sax_handler_t
   {
      public:
      ContainerHandle m_expando_class_object = 0;
      char m_add_property_method_name[ 260 ] = { 0 };
      json_node_t m_root;
      json_node_t* m_tos_ptr = &m_root;



      json_sax_handler_t( ContainerHandle expando_class_object, char* add_property_method_name)
      {
         m_root.m_is_root = TRUE;
         if( expando_class_object )
         {
            m_expando_class_object = _conPut( m_expando_class_object, expando_class_object );
         }
         else
         {
            m_expando_class_object = _conPut( m_expando_class_object, NULLCONTAINER );
            _conCall( m_expando_class_object, "_OT4XB_EXPANDO_", 0 );
         }
         if( add_property_method_name )
         {
            strncpy_s( m_add_property_method_name, add_property_method_name, sizeof( m_add_property_method_name ) - 1 );
         }
         else
         {
            strncpy_s( m_add_property_method_name, "set_prop", sizeof( m_add_property_method_name ) - 1 );
         }
      };

      ~json_sax_handler_t()
      {
         __cleanup();
      }
      void __cleanup()
      {
         if( m_expando_class_object )
         {
            _conRelease( m_expando_class_object );
            m_expando_class_object = 0;
         }
         m_root.__cleanup();
         m_tos_ptr = 0;
      };

      ContainerHandle detach_root_value()
      {
         if( m_root.m_value )
         {
            ContainerHandle value = m_root.m_value;
            m_root.m_value = NULLCONTAINER;
            return value;
         }
         return NULLCONTAINER;
      };


      bool put_simple_value( ContainerHandle value )
      {
         if( m_tos_ptr )
         {
            if( !m_tos_ptr->m_sealed )
            {
               DWORD t = m_tos_ptr->m_type & 0xFF;

               if( ( t == XPP_ARRAY && m_tos_ptr->m_value ) || ( t == 0 && !m_tos_ptr->m_value ) )
               {
                  if( t == XPP_ARRAY )
                  {
                     m_tos_ptr->m_array_size++;
                     if( !_conResizeA( m_tos_ptr->m_value, m_tos_ptr->m_array_size ) )
                     {
                        _conArrayPut( m_tos_ptr->m_value, value, m_tos_ptr->m_array_size, 0 );
                        _conRelease( value );
                        value = NULLCONTAINER;
                        return true;
                     }
                  }
                  else
                  {
                     json_node_t* item = m_tos_ptr;
                     json_node_t* parent = item->m_parent;
                     item->m_value = value;
                     _conType( value, &item->m_type );
                     value = 0;

                     if( parent )
                     {
                        ULONG err = INFINITE;
                        DWORD tp = parent->m_type & 0xFF;
                        parent->m_next = 0; m_tos_ptr = parent; // pop 
                        if( tp == XPP_OBJECT && item->m_name )
                        {
                           ContainerHandle params[ 3 ] = { parent->m_value,item->m_name,item->m_value };
                           ContainerHandle conr = _conNew( NULLCONTAINER );
                           err = _conCallMethodPa( conr, m_add_property_method_name, 3, params );
                           _conRelease( conr ); conr = 0;
                        }
                        delete item;
                        item = 0;
                        return ( err ? false : true );
                     }
                     else
                     {
                        item->m_sealed = true;
                        return true;
                     }
                  }
               }
            }
         }
         if( value )
         {
            _conRelease( value );
            value = 0;
         }
         return false;
      }

      bool Null()
      {
         ContainerHandle con = _conNew( NULLCONTAINER );
         return put_simple_value( con );
      };

      bool Bool( bool b )
      {
         ContainerHandle con = _conPutL( NULLCONTAINER, ( b ? 1 : 0 ) );
         return put_simple_value( con );
      }
      bool Int( int i )
      {
         ContainerHandle con = _conPutNL( NULLCONTAINER, i );
         return put_simple_value( con );
      }
      bool Uint( unsigned u )
      {
         ContainerHandle con = NULLCONTAINER;
         if( u & 0x8000000 )
         {
            con = _conPutND( con, (double) u );
         }
         else
         {
            con = _conPutNL( con, (int) u );
         }
         return put_simple_value( con );
      }
      bool Int64( int64_t i )
      {
         ContainerHandle con = NULLCONTAINER;

         if( i & 0xFFFFFFFF0000000 )
         {
            con = _conPutND( con, (double) i );
         }
         else
         {
            con = _conPutNL( con, (int) i & 0xFFFFFFFF );
         }
         return put_simple_value( con );
      }
      bool Uint64( uint64_t u )
      {
         ContainerHandle con = NULLCONTAINER;
         if( u & 0xFFFFFFFF8000000 )
         {
            con = _conPutND( con, (double) u );
         }
         else
         {
            con = _conPutNL( con, (int) u & 0xFFFFFFFF );
         }
         return put_simple_value( con );
      }
      bool Double( double d )
      {
         ContainerHandle con = _conPutND( NULLCONTAINER, d );
         return put_simple_value( con );
      }

      bool RawNumber( const char* str, SizeType length, bool copy )
      {
         return String( str, length, copy );
      }
      bool String( const char* str, SizeType length, bool )
      {
         ContainerHandle con = NULLCONTAINER;
         int cb = 0;
         LPSTR pp = mb2mb( (char*) str, length, &cb, 65001, 0 , 0, 0 );
         con = _conPutCL( con, pp, (DWORD) cb );
         _xfree( (void*) pp );
         pp = 0;
         return put_simple_value( con );
      };

      bool StartObject()
      {

         if( m_tos_ptr )
         {
            if( !( m_tos_ptr->m_sealed || m_tos_ptr->m_next ) )
            {
               json_node_t* item = new json_node_t();
               item->m_parent = m_tos_ptr;
               item->m_value = _conNew( NULLCONTAINER );
               _conCallMethodPa( item->m_value, "new", 1, &m_expando_class_object );
               _conType( item->m_value, &item->m_type );
               if( item->m_type & XPP_OBJECT )
               {
                  m_tos_ptr->m_next = item; m_tos_ptr = item; // push
                  return true;
               }
               else
               {
                  delete item; item = 0;
                  return false;
               }
            }
         }
         return false;
      }
      bool Key( const char* str, SizeType length, bool )
      {
         if( m_tos_ptr )
         {
            DWORD t = m_tos_ptr->m_type & 0xFF;
            if( t == XPP_OBJECT && !m_tos_ptr->m_sealed && !m_tos_ptr->m_next )
            {
               json_node_t* item = new json_node_t( str, length );
               item->m_parent = m_tos_ptr;
               m_tos_ptr->m_next = item;
               m_tos_ptr = item;
               return true;
            }
         }
         return false;
      }
      bool EndObject( SizeType )
      {

         if( m_tos_ptr )
         {

            json_node_t* item = m_tos_ptr;
            json_node_t* parent = item->m_parent;
            DWORD t = item->m_type & 0xFF;

            if( parent && t == XPP_OBJECT )
            {
               ContainerHandle value = item->m_value;
               item->m_value = NULLCONTAINER;
               parent->m_next = 0; m_tos_ptr = parent; // pop 
               delete item;
               item = 0;
               return put_simple_value( value );
            }
         }
         return false;
      }

      bool StartArray()
      {
         if( m_tos_ptr )
         {
            if( !( m_tos_ptr->m_sealed || m_tos_ptr->m_next ) )
            {
               json_node_t* item = new json_node_t();
               item->m_parent = m_tos_ptr;
               item->m_value = _conNewArray( 1, 0 );
               _conType( item->m_value, &item->m_type );
               m_tos_ptr->m_next = item; m_tos_ptr = item; // push
               return true;
            }
         }
         return false;
      }
      bool EndArray( SizeType )
      {

         if( m_tos_ptr )
         {

            json_node_t* item = m_tos_ptr;
            json_node_t* parent = item->m_parent;
            DWORD t = item->m_type & 0xFF;

            if( parent && t == XPP_ARRAY )
            {
               ContainerHandle value = item->m_value;
               item->m_value = NULLCONTAINER;
               parent->m_next = 0; m_tos_ptr = parent; // pop 
               delete item;
               item = 0;
               return put_simple_value( value );
            }
         }
         return false;
      };
   };
   // ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
   OT4XB_API ContainerHandle parse_string_utf8( LPSTR source_string, ContainerHandle expando_class_object = 0, char* add_property_method_name = 0 )
   {

      ContainerHandle value = NULLCONTAINER;
      json_ns::json_sax_handler_t handler( expando_class_object, add_property_method_name );
      Reader reader;
      StringStream ss( source_string );
      if( reader.Parse( ss, handler ) )
      {
         value = handler.detach_root_value();
      }
      handler.__cleanup();
      return value;
   }
   OT4XB_API ContainerHandle parse_string_ansi( LPSTR source_string, ContainerHandle expando_class_object = 0, char* add_property_method_name = 0 )
   {
      int utf8_cb = 0;
      LPSTR uft8_str = mb2mb( source_string, -1, &utf8_cb, 0, 65001, 0, 0 );
      ContainerHandle result = parse_string_utf8( uft8_str, expando_class_object, add_property_method_name );
      _xfree( (void*) uft8_str ); uft8_str = 0;
      return result;
   }

   OT4XB_API  void serialize_value( TZString& z, ContainerHandle con_value, DWORD pStack, DWORD nMoreFlags, DWORD nDepth )
   {
      ULONG ulType = 0;
      DWORD bCute = nMoreFlags & EXPANDO_FORMAT_PRETTY;

      _conType( con_value, &ulType );


      switch( ulType & 0xFF )
      {
         case  XPP_CHARACTER:
         {
            if( nMoreFlags & EXPANDO_FORMAT_DEBUG ) { z += "[\"C\","; }
            z += "\"";
            DWORD cb = 0;
            LPSTR p = 0;
            if( _conRLockC( con_value, &p, &cb ) == 0 )
            {
               z.Add_to_json( p, (int) cb );
               _conUnlockC( con_value );
            }
            p = 0; cb = 0;
            z += "\"";
            if( nMoreFlags & EXPANDO_FORMAT_DEBUG ) { z += "]"; }
            return;
         }
         case  XPP_DATE:
         {
            if( nMoreFlags & EXPANDO_FORMAT_DEBUG ) { z += "[\"D\","; }
            char sz[ 9 ]; ZeroMemory( sz, sizeof( sz ) );
            _conGetDS( con_value, sz );
            z += "\"";
            z += sz;
            z += "\"";
            if( nMoreFlags & EXPANDO_FORMAT_DEBUG ) { z += "]"; }
            return;
         }
         case  XPP_NUMERIC:
         {
            if( nMoreFlags & EXPANDO_FORMAT_DEBUG ) { z += "[\"N\","; }
            if( ulType & _xpp_DOUBLE )
            {
               double nd = 0.00;
               char format[ 64 ];
               _conGetND( con_value, &nd );
               _snprintf_c( format, sizeof( format ), "%%f" );

               DWORD ndf = ( ( nMoreFlags >> 20 ) & 0x0F );
               DWORD precission = ( nMoreFlags >> 16 ) & 0x0F;
               if( precission && !( ndf & 3 ) )
               {
                  ndf = 1;
               }
               if( ( ndf & 3 ) && !precission )
               {
                  precission = 15;
               }
               switch( ndf )
               {
                  case 1:
                  {
                     _snprintf_c( format, sizeof( format ), "%%.%if", precission );
                     break;
                  }
                  case 2:
                  {
                     _snprintf_c( format, sizeof( format ), "%%.%ig", precission );
                     break;
                  }
               }
               z.printf( format, nd );
            }
            else
            {
               LONG nl = 0;
               _conGetNL( con_value, &nl );
               z.printf( "%i", nl );
            }
            if( nMoreFlags & EXPANDO_FORMAT_DEBUG ) { z += "]"; }
            return;
         }
         case  XPP_LOGICAL:
         {

            BOOL b = 0;
            if( nMoreFlags & EXPANDO_FORMAT_DEBUG ) { z += "[\"L\","; }
            _conGetL( con_value, &b );
            z += ( b ? "true" : "false" );
            if( nMoreFlags & EXPANDO_FORMAT_DEBUG ) { z += "]"; }
            return;
         }
         case  XPP_OBJECT:
         {
            LPSTR p = 0;
            if( nMoreFlags & EXPANDO_FORMAT_DEBUG )
            {
               z += "[\"O";
               p = _pszGetClassName( con_value );
               if( p )
               {
                  z += " (  ";
                  z += p;
                  _xfree( p );
                  p = 0;
                  z += " )";
               }
               z += "\",";
            }
            p = _conMCallLpstr( con_value, "json_escape_self", (LONG) nMoreFlags, (LONG) nDepth, (LONG) pStack );
            if( p )
            {
               z += p;
               _xfree( p );
            }
            else
            {
               z += "null";
            }
            if( nMoreFlags & EXPANDO_FORMAT_DEBUG ) { z += "]"; }
            return;
         }
         case XPP_ARRAY:
         {
            DWORD nCount = _conGetArrayLen( con_value );
            DWORD n;
            DWORD item_array_flags = nMoreFlags;
            if( nMoreFlags & EXPANDO_FORMAT_FLAT_ARRAY_KV_ITEMS )
            {
               item_array_flags = nMoreFlags & ( ~( EXPANDO_FORMAT_PRETTY ) );
            }
            if( nMoreFlags & EXPANDO_FORMAT_DEBUG ) { z.printf( "[\"A (%i) \",", nCount ); }
            if( bCute || ( nMoreFlags & EXPANDO_FORMAT_FLAT_ARRAY_KV_ITEMS ) ) { DWORD ddd;  z += "\r\n"; for( ddd = 0;  ddd < nDepth; ddd++ ) { z += "   "; } }
            z += "[";
            nDepth++;
            for( n = 1; n <= nCount; n++ )
            {
               ContainerHandle con = _conNew( NULLCONTAINER );
               DWORD item_type = 0;
               _conArrayGet( con_value, con, n, 0 );
               if( nMoreFlags & EXPANDO_FORMAT_FLAT_ARRAY_KV_ITEMS )
               {
                  _conType( con, &item_type );
               }
               if( n > 1 ) { z.AddChar( ',' ); }
               serialize_value( z, con, pStack, ( item_type & XPP_ARRAY ? item_array_flags : nMoreFlags ), nDepth );
               _conReleaseM( con, 0 );
            }
            nDepth--;
            if( bCute ) { DWORD ddd;  z += "\r\n"; for( ddd = 0;  ddd < nDepth; ddd++ ) { z += "   "; } }
            z += "]";
            if( nMoreFlags & EXPANDO_FORMAT_DEBUG ) { z += "]"; }
            return;
         }
         default:
         {

            if( nMoreFlags & EXPANDO_FORMAT_DEBUG ) { z += "[\"U\","; }
            z += "null";
            if( nMoreFlags & EXPANDO_FORMAT_DEBUG ) { z += "]"; }
            return;
         }
      }
   }
   // ---------------------------------------------------------------------------------
   OT4XB_API void serialize( XppParamList pl )
   {
      TXppParamList xpp( pl, 4 );
      TList* pStack = (TList*) xpp[ 4 ]->GetDWord();
      TZString z( 4096 );
      serialize_value( z, xpp[ 1 ]->con(), (DWORD) pStack, xpp[2]->CheckType(XPP_NUMERIC) ? xpp[ 2 ]->GetDWord() : 0x00200000 , xpp[ 3 ]->GetDWord() );
      // delete pStack;
      // pStack = 0;
      xpp[ 0 ]->PutStrLen( z._pt_(), z.len() );
   }




















}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ot4xb_json_parse_string( 1str ,  2 src_cp = 65001 ,  3expando_class_object = _ot4xb_expando_()  , 4 add_property_method_name = "set_prop" ) -> value or NIL
_XPP_REG_FUN_( OT4XB_JSON_PARSE )
{
   TXppParamList xpp( pl, 4 );
   ContainerHandle result = NULLCONTAINER;
   LPSTR source_string = xpp[ 1 ]->LockStr();
   DWORD src_cp = ( xpp[ 2 ]->CheckType( XPP_NUMERIC ) ? xpp[ 2 ]->GetDWord() : 65001 );
   if( source_string )
   {
      ContainerHandle expando_class_object = ( xpp[ 3 ]->CheckType( XPP_OBJECT ) ? xpp[ 3 ]->con() : NULLCONTAINER );
      char* add_property_method_name = xpp[ 4 ]->LockStr();
      if( src_cp == 65001 )
      {
         result = json_ns::parse_string_utf8( source_string, expando_class_object, add_property_method_name );
      }
      else
      {
         result = json_ns::parse_string_ansi( source_string, expando_class_object, add_property_method_name );
      }
   }
   if( result )
   {
      xpp[ 0 ]->Put( result );
      _conRelease( result );
      result = NULLCONTAINER;
   }
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------