//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
#ifdef DEBUG123456
//----------------------------------------------------------------------------------------------------------------------
BEGIN_NAMESPACE( ot4xb_json_parser_ns )
//----------------------------------------------------------------------------------------------------------------------
enum json_state_t
{
       json_none
      ,json_expression
      ,json_text
      ,json_control
      ,json_end
      ,json_error

};
enum json_item_type_t
{
      json_item_null           = 0x0001,
      json_item_numeric        = 0x0004,
      json_item_logical        = 0x0008,
      json_item_expression     = 0x000D,
      json_item_text           = 0x0002,
      json_item_array          = 0x0020,
      json_item_object         = 0x0080,
      json_item_label          = 0x8002,
      json_item_property       = 0x8080,
      json_item_container      = 0x1000, 
      json_item_invalid        = 0xFFFF
};
     
//----------------------------------------------------------------------------------------------------------------------
class OT4XB_API ot4xb_json_item_t  : public T_ot4xb_base
{
   public:
   // ---------------------------------------------------------------------------------
   json_item_type_t m_type;
   ContainerHandle  m_con_name;
   ContainerHandle  m_con_value;
   DWORD            m_child_count;
   BOOL             m_separator;
   BOOL             m_is_array_item;
   // ---------------------------------------------------------------------------------
   ot4xb_json_item_t()
   {
      m_type           = json_item_invalid;
      m_con_name       = NULLCONTAINER;
      m_con_value      = NULLCONTAINER;
      m_child_count    = 0;
      m_separator      = FALSE;
      m_is_array_item  = 0;
   };
   // ---------------------------------------------------------------------------------
   ~ot4xb_json_item_t()
   {
      if( m_con_name )
      {
         _conRelease(m_con_name);
      }
      if( m_con_value )
      {
         _conRelease(m_con_value);
      }
      m_type      = json_item_invalid;
      m_con_name  = NULLCONTAINER;
      m_con_value = NULLCONTAINER;
   };
   // ---------------------------------------------------------------------------------
   BOOL object_add_property( ot4xb_json_item_t * item , BOOL bSep );
   BOOL array_add_element( ot4xb_json_item_t * item , BOOL bSep );
   BOOL set_value_to_array();
   BOOL set_value_to_object();
   BOOL set_value_to_ansi_text( LPSTR p , DWORD cb);
   BOOL set_label( LPSTR p );
   BOOL set_value_to_expression( LPSTR p );
   BOOL set_value_to_int( int v);
   BOOL set_value_to_double( double v);
   BOOL set_value_to_bool( BOOL v);
   BOOL set_value_to_null();
   // ---------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------   
class OT4XB_API ot4xb_json_parser_t  : public T_ot4xb_base
{
   public:
   // ---------------------------------------------------------------------------------


   // ---------------------------------------------------------------------------------
   TByteStream m_str;
   // ---------------------------------------------------------------------------------
   TList * m_pStack;
   BOOL    m_must_destroy_buffer;
   LPBYTE  m_buffer;
   DWORD   m_buffer_size;
   DWORD   m_buffer_pos;
   BOOL    m_escape;
   json_state_t m_state;
   BOOL    m_dwNextCharReady;

   WCHAR   m_wchar[16];
   DWORD   m_wchar_size;

   DWORD   m_ansi_size;
   char    m_ansi[16];

   BYTE    m_bytes[16];
   DWORD   m_char_size;
   // ---------------------------------------------------------------------------------
   ot4xb_json_parser_t() : m_str(4096,4096)
                       {
                          m_pStack                = new TList;
                          m_must_destroy_buffer   = FALSE;
                          m_buffer                = 0;
                          m_buffer_size           = 0;
                          m_buffer_pos            = 0;
                          m_state                 = json_error;
                          m_dwNextCharReady       = 0;
                          reset_char();
                       };
   // ---------------------------------------------------------------------------------
   ~ot4xb_json_parser_t();
   // ---------------------------------------------------------------------------------
   BOOL is_last_item_type_text();
   BOOL is_last_item_type_label();
   BOOL is_last_item_type_object();
   BOOL is_last_item_type_array();
   BOOL is_last_item_parent_type_object();
   BOOL is_last_item_parent_type_array();
   // ---------------------------------------------------------------------------------
   ot4xb_json_item_t * push_new_item();
   ot4xb_json_item_t * pop_item();
   ot4xb_json_item_t * last_item();
   DWORD item_count();
   void reset_char();
   BOOL NextChar();
   BOOL IsWhiteSpace();
   int ReadChar();
   BOOL read_escape_sequence();
   void skip_white_space();
   BOOL pop_and_append_item( BOOL bSep );
   void read_expression();
   void read_text();
   BOOL read_control();
   BOOL step();
   // ---------------------------------------------------------------------------------

};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
ot4xb_json_parser_t::~ot4xb_json_parser_t()
{
   if( m_pStack )
   {
      while( m_pStack->Count() )
      {
         ot4xb_json_item_t * item = pop_item();
         if( item )
         {
            delete item;
         }
      }
      delete m_pStack;
      m_pStack = 0;
   }
   if( m_buffer && m_must_destroy_buffer )
   {
      _xfree( (void*) m_buffer );
      m_buffer = 0;
   }
   m_must_destroy_buffer   = FALSE;
   m_buffer_size           = 0;
   m_buffer_pos            = 0;
   m_dwNextCharReady       = 0;

   reset_char();
}
//----------------------------------------------------------------------------------------------------------------------
BOOL ot4xb_json_parser_t::is_last_item_type_text()
{
   ot4xb_json_item_t * item = last_item();
   if( item )
   {
      return (BOOL) (item->m_type == json_item_text);
   }
   return FALSE;
}
//----------------------------------------------------------------------------------------------------------------------
BOOL ot4xb_json_parser_t::is_last_item_type_label()
{
   ot4xb_json_item_t * item = last_item();
   if( item )
   {
      return (BOOL) (item->m_type == json_item_label );
   }
   return FALSE;
}
//----------------------------------------------------------------------------------------------------------------------
BOOL ot4xb_json_parser_t::is_last_item_type_object()
{
   ot4xb_json_item_t * item = last_item();
   if( item )
   {
      return (BOOL) (item->m_type == json_item_object );
   }
   return FALSE;
}
//----------------------------------------------------------------------------------------------------------------------
BOOL ot4xb_json_parser_t::is_last_item_type_array()
{
   ot4xb_json_item_t * item = last_item();
   if( item )
   {
      return (BOOL) (item->m_type == json_item_array);
   }
   return FALSE;
}
//----------------------------------------------------------------------------------------------------------------------
BOOL ot4xb_json_parser_t::is_last_item_parent_type_object()
{
   if( m_pStack )
   {
      if( m_pStack->Count() > 1 )
      {
         return (BOOL) (static_cast<ot4xb_json_item_t *>( m_pStack->Get( m_pStack->Count() - 2))->m_type == json_item_object );
      }
   }
   return FALSE;
}
//----------------------------------------------------------------------------------------------------------------------
BOOL ot4xb_json_parser_t::is_last_item_parent_type_array()
{
   if( m_pStack )
   {
      if( m_pStack->Count() > 1 )
      {
         return (BOOL) (static_cast<ot4xb_json_item_t *>( m_pStack->Get( m_pStack->Count() - 2))->m_type == json_item_array);
      }
   }
   return FALSE;
}
//----------------------------------------------------------------------------------------------------------------------
ot4xb_json_item_t * ot4xb_json_parser_t::push_new_item()
{
   if( m_pStack )
   {
      ot4xb_json_item_t * item = new ot4xb_json_item_t;
      item->m_is_array_item = is_last_item_type_array();
      m_pStack->Add( (void*) item );
      return item;
   }
   return 0;
}
// ---------------------------------------------------------------------------------
ot4xb_json_item_t * ot4xb_json_parser_t::pop_item()
{
   if( m_pStack )
   {
      ot4xb_json_item_t * item = (ot4xb_json_item_t *) m_pStack->Pop() ;
      return item;
   }
   return 0;
}
// ---------------------------------------------------------------------------------
ot4xb_json_item_t * ot4xb_json_parser_t::last_item()
{
   if( m_pStack )
   {
      ot4xb_json_item_t * item = (ot4xb_json_item_t *) m_pStack->Tail() ;
      return item;
   }
   return 0;
}
// ---------------------------------------------------------------------------------
DWORD ot4xb_json_parser_t::item_count()
{
   if( m_pStack )
   {
      return m_pStack->Count() ;
   }
   return 0;
}
// ---------------------------------------------------------------------------------
void ot4xb_json_parser_t::reset_char()
{
   m_char_size  = 0; ZeroMemory( m_bytes , sizeof(m_bytes));
   m_ansi_size  = 0; ZeroMemory( m_ansi  , sizeof(m_bytes));
   m_wchar_size = 0; ZeroMemory( m_wchar , sizeof(m_bytes));
   m_escape = FALSE;
}
// ---------------------------------------------------------------------------------


// ---------------------------------------------------------------------------------
BOOL ot4xb_json_parser_t::NextChar()
{
   DWORD save_pos = m_buffer_pos;
   int   result   = ReadChar();
   m_dwNextCharReady  = m_buffer_pos - save_pos;
   m_buffer_pos = save_pos;
   return result > 0;
}
// ---------------------------------------------------------------------------------
BOOL ot4xb_json_parser_t::IsWhiteSpace()
{
   if( m_ansi_size == 1 )
   {
      switch( m_ansi[0] ){ case 0x20: case 0x09: case 0x0A: case 0x0B: return TRUE; }
   }
   return FALSE;
}
// ---------------------------------------------------------------------------------
int ot4xb_json_parser_t::ReadChar()
{
   if( m_dwNextCharReady )
   {
      m_buffer_pos += m_dwNextCharReady;
      m_dwNextCharReady = 0;
      return m_char_size;
   }
   reset_char();
   if( !m_buffer ){ return -1; }
   if( m_buffer_pos >= m_buffer_size ){return 0;}
   DWORD remaining_bytes = ( m_buffer_size - m_buffer_pos );
   DWORD dw;

   m_bytes[0] = m_buffer[m_buffer_pos];
   if((m_bytes[0] & 0x80) == 0)
   {
      m_char_size = 1;
      if( (m_bytes[0] == (BYTE) '\\') )
      {
         if( read_escape_sequence() )
         {
            if( !m_char_size )
            {
               return -1;
            }
            return m_char_size;
         }
      }
   }
   else if ( (m_bytes[0] & 0xE0) == 0xC0 )
   {
      m_char_size = 2;
   }
   else if ( (m_bytes[0] & 0xF0) == 0xE0 )
   {
      m_char_size = 3;
   }
   else if ( (m_bytes[0] & 0xF8) == 0xF0 )
   {
      m_char_size = 4;
   }
   else
   {
      return -1; // invalid utf8 character sequence
   }
   if( remaining_bytes < m_char_size )
   {
      return -1; // expected at least  m_char_size bytes
   }
   for( dw = 1; dw < m_char_size; dw++ )
   {
      m_bytes[dw] = m_buffer[m_buffer_pos + dw];
      if( !((m_bytes[dw] & 0xC0) == 0x80) )
      {
         return -1; // invalid continuation byte
      }
   }

   m_buffer_pos += m_char_size;
   m_wchar_size = MultiByteToWideChar( CP_UTF8 ,0,(LPSTR)m_bytes,(int) m_char_size,m_wchar,sizeof(m_wchar)/2);
   m_ansi_size  = WideCharToMultiByte( CP_ACP ,0,m_wchar,m_wchar_size,(LPSTR) m_ansi,sizeof(m_ansi),0,0);
   return m_char_size;
}
// ---------------------------------------------------------------------------------
BOOL ot4xb_json_parser_t::read_escape_sequence()
{

   if( !( m_state == json_text ) )
   {
      return FALSE;
   }
   DWORD remaining_bytes = ( m_buffer_size - m_buffer_pos );
   if( remaining_bytes < 2 )
   {
      return FALSE;
   }
   if( !( m_buffer[m_buffer_pos] == (BYTE) '\\') )
   {
      return FALSE;
   }
   char ch = (char) m_buffer[m_buffer_pos + 1];

   switch( ch )
   {
      case 'u':
      {
         m_char_size = 0; // invalid escape sequence
         if( remaining_bytes > 5 )
         {
            DWORD dw = 0;
            int n;
            for( n = 0; n < 4; n++ )
            {
               if( !bIsNibble( (char) m_buffer[m_buffer_pos + 2 + n],&dw,3 - n ) )
               {
                  return TRUE;
               }
            }
            reset_char();
            _bcopy( m_bytes , _mk_ptr_(LPBYTE,m_buffer,m_buffer_pos),6);

            m_escape      =  TRUE;
            m_wchar[0]    =  (WCHAR) (dw & 0xFFFF);
            m_char_size   =  6;
            m_buffer_pos  += 6;
            m_wchar_size  =  1;
            m_ansi_size = WideCharToMultiByte( CP_ACP ,0,m_wchar,1,(LPSTR) m_ansi,sizeof(m_ansi),0,0);
         }
         return TRUE;
      }
      case '"': case '\\': case '/': { break; }
      case 'b': {ch = '\b'; break; }
      case 'f': {ch = '\f'; break; }
      case 'n': {ch = '\n'; break; }
      case 'r': {ch = '\r'; break; }
      case 't': {ch = '\t'; break; }
      default :
      {
         m_char_size = 0; // invalid escape sequence
         return TRUE;
      }
   }

   reset_char();
   m_char_size  = 2;
   m_buffer_pos += 2;
   m_bytes[0]   = m_ansi[0] = (BYTE) ch;
   m_ansi_size = 1;
   m_wchar_size = MultiByteToWideChar( CP_UTF8 ,0,&ch,1,m_wchar,1);
   return TRUE;
}
// ---------------------------------------------------------------------------------
void ot4xb_json_parser_t::skip_white_space()
{
   if( m_state == json_text )
   {
      return;
   }
   for(;IsWhiteSpace(); NextChar())
   {
      ReadChar();
   }
   if( m_buffer_pos >= m_buffer_size )
   {
      if( m_state != json_end )
      {
         m_state = json_error;
      }
      return;
   }
   if( !( m_ansi_size == 1 ) )
   {
      m_state = json_error;
      return;
   }
   switch( m_ansi[0] )
   {
      case '"':
      {
         m_state = json_text;
         break;
      }
      case ':': case '{' : case '}':case '[' : case ']': case ',':
      {
         m_state = json_control;
         break;
      }
      case 'n': case 't': case 'f':
      {
         m_state = json_expression;
         break;
      }
      case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '.': case '-':
      {
         m_state = json_expression;
         break;
      }
      default:
      {
         m_state = json_error;
         break;
      }
   }
}
// ---------------------------------------------------------------------------------
BOOL ot4xb_json_parser_t::pop_and_append_item( BOOL bSep )
{
   ot4xb_json_item_t * item = 0;
   BOOL result = FALSE;
   if( item_count() > 1 )
   {
      item = pop_item();
      
      if( item )
      {
         ot4xb_json_item_t * parent = last_item();
         if( parent )
         { 
            switch( parent->m_type )
            {
               case json_item_object:
               {
                  result = last_item()->object_add_property(item,bSep);
                  break;
               }
               case json_item_array:
               {
                  result = last_item()->array_add_element(item,bSep);
                  break;
               }
            }
         }
         delete item; item = 0;
      }
   }
   return result;
}
// ---------------------------------------------------------------------------------
//////////////void ot4xb_json_parser_t::read_expression();
// ---------------------------------------------------------------------------------
///////////////void ot4xb_json_parser_t::read_text();
// ---------------------------------------------------------------------------------
BOOL ot4xb_json_parser_t::read_control()
{
   ReadChar();
   char ch = m_ansi[0];
   NextChar();
   skip_white_space();
   switch( ch )
   {
      case ':':
      {
         if( ! is_last_item_type_label() )
         {
            m_state = json_error;
            return FALSE;
         }
         last_item()->m_type = json_item_property;
         return TRUE;
      }
      case '[':
      {
         push_new_item()->set_value_to_array();
         m_state = json_none;
         return TRUE;
      }
      case '{':
      {
         push_new_item()->set_value_to_object();
         m_state = json_none;
         return TRUE;
      }
      case ',':
      {
         if( !pop_and_append_item( TRUE ) )
         {
            m_state = json_error;
            return FALSE;
         }
         skip_white_space();
         return TRUE;
      }
      case ']':
      {
         if( is_last_item_type_array() )
         {
            last_item()->m_type = json_item_container;
            skip_white_space();
            return TRUE;
         }
         if( !is_last_item_parent_type_array() )
         {
            m_state = json_error;
            return FALSE;
         }
         if( !pop_and_append_item( FALSE ) )
         {
            m_state = json_error;
            return FALSE;
         }
         last_item()->m_type = json_item_container;
         skip_white_space();
         return TRUE;
      }
      case '}':
      {
         if( is_last_item_type_object() )
         {
            last_item()->m_type = json_item_container;
            skip_white_space();
            return TRUE;
         }
         if( !is_last_item_parent_type_object() )
         {
            m_state = json_error;
            return FALSE;
         }
         if( !pop_and_append_item( FALSE ) )
         {
            m_state = json_error;
            return FALSE;
         }
         last_item()->m_type = json_item_container;
         skip_white_space();
         return TRUE;
      }
   }
   m_state = json_error;
   return FALSE;
}
// ---------------------------------------------------------------------------------
BOOL ot4xb_json_parser_t::step()
{

   switch( m_state )
   {
      case json_none :
      {
         NextChar();
         skip_white_space();
         break;
      }
      case json_expression :
      {

         ot4xb_json_item_t * item = push_new_item();
         item->m_type = json_item_expression;
         read_expression();
         skip_white_space();
         break;
      }
      case json_text :
      {
         ot4xb_json_item_t * item = push_new_item();
         item->m_type = ( is_last_item_type_object() ? json_item_label : json_item_text );
         read_text();
         skip_white_space();
         break;
      }
      case json_control       :
      {
         return read_control();
      }
      case json_end : 
      {
         skip_white_space();
         break;
      }
   }      
   return !( json_error == m_state );
}
// ---------------------------------------------------------------------------------------------------------------------
BOOL ot4xb_json_item_t::object_add_property( ot4xb_json_item_t * item , BOOL bSep )
{
   if( (m_type == json_item_object) && item && m_con_value )
   {
      if( bSep && (m_child_count == 0) )
      {
         return FALSE;
      }
      if( item->m_con_name && item->m_con_value )
      {
         ContainerHandle pcon[4] = { m_con_value , item->m_con_name , item->m_con_value , 0 };
         ContainerHandle conr  = _conNew(0);
         ULONG result = _conCallMethodPa(conr,"set_prop",3,pcon);
         _conRelease(conr); conr = 0;
         m_separator = bSep;  
         return (BOOL) ( result == 0 );
      }
   }
   return FALSE;
}
// ---------------------------------------------------------------------------------------------------------------------
BOOL ot4xb_json_item_t::array_add_element( ot4xb_json_item_t * item , BOOL bSep )
// ---------------------------------------------------------------------------------------------------------------------
BOOL ot4xb_json_item_t::set_value_to_array()
{
   if( m_con_value )
   {
      _conRelease( m_con_value );
      m_con_value = 0;
   }
   m_con_value = _conNewArray(1,0);
   m_child_count = 0;
   m_separator   = 0;
   m_type        = json_item_array;
   return TRUE;
}
// ---------------------------------------------------------------------------------------------------------------------
BOOL ot4xb_json_item_t::set_value_to_object()
{
   m_con_value   = _conPutNewObj(m_con_value,"_ot4xb_expando_",0);
   m_child_count = 0;
   m_separator   = 0;
   if( !m_con_value )
   {
      m_type = json_item_invalid;
      return FALSE;
   }
   m_type        = json_item_object;
   return TRUE;
}
// ---------------------------------------------------------------------------------------------------------------------
BOOL ot4xb_json_item_t::set_label( LPSTR p )
{
   if( p )
   {
      m_con_name = _conPutC( m_con_name , p );
      return TRUE;
   }
   if( m_con_name )
   {
      _conRelease( m_con_name );
      m_con_name = 0;
   }
   m_type        = json_item_label;
   return FALSE;
}
// ---------------------------------------------------------------------------------------------------------------------
BOOL ot4xb_json_item_t::set_value_to_ansi_text( LPSTR p , DWORD cb)
{
   if( p && cb )
   {
      m_con_value = _conPutCL( m_con_value , p , cb );
   }
   else
   {
      m_con_value = _conPutC( m_con_value , "");
   }
   m_type        = json_item_text;
   return TRUE;
}
// ---------------------------------------------------------------------------------------------------------------------
BOOL ot4xb_json_item_t::set_value_to_expression( LPSTR p )
{
   LONG   n;
   DWORD  dw = 0; 
   DWORD  cb = _xstrlen(p);

   if( bStrWildCmpI("true" , p ) )
   {
      return set_value_to_bool(TRUE);
   }
   if( bStrWildCmpI("false" , p ) )
   {
      return set_value_to_bool(FALSE);
   }
   if( bStrWildCmpI("null" , p ) )
   {
      return set_value_to_null();
   }
   for( n= 0; n < (LONG) cb ; n++ )
   {
      switch( p[n] )
      {
         case ' ': break;
         case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': dw |= 0x01; break;
         case '-': dw |= 0x02; break;
         case '.': dw |= 0x04; break;
         case '+': dw |= 0x08; break;
         case 'e': case 'E': dw |= 0x10; break;
         default: return FALSE;
      }
   }
   
   if( !(dw & 0x01) ){ return FALSE; } // no digits
   if( dw & 0x10 )
   {
      return set_value_to_double( atof(p) );
   }
   if( dw & 0x08 ){ return FALSE; } // + only accepted for exponential numbers
   if( dw & 0x04 )
   {
      return set_value_to_double( atof(p) );
   }
   if( dw & 0x02 )
   {
      return set_value_to_int( atol(p) );
   }
   n = atol(p);
   if( n < 0  )
   {
      return set_value_to_double( atof(p) );
   }
   return set_value_to_int( atol(p) );
}
// ---------------------------------------------------------------------------------------------------------------------
BOOL ot4xb_json_item_t::set_value_to_int( int v)
{
   m_con_value = _conPutNL( m_con_value , v ); 
   m_type        = json_item_numeric;
   return TRUE;
}
// ---------------------------------------------------------------------------------------------------------------------
BOOL ot4xb_json_item_t::set_value_to_double( double v)
{
   m_con_value = _conPutND( m_con_value , v ); 
   m_type        = json_item_numeric;
   return TRUE;
}
// ---------------------------------------------------------------------------------------------------------------------
BOOL ot4xb_json_item_t::set_value_to_bool( BOOL v)
{
   m_con_value = _conPutL( m_con_value , v ); 
   m_type        = json_item_logical;
   return TRUE;
}
// ---------------------------------------------------------------------------------------------------------------------
BOOL ot4xb_json_item_t::set_value_to_null()                                                                                
{
   m_con_value = _conPut( m_con_value , NULLCONTAINER ); 
   m_type        = json_item_null;
   return TRUE;
}
//----------------------------------------------------------------------------------------------------------------------
END_NAMESPACE()
//----------------------------------------------------------------------------------------------------------------------
#endif
