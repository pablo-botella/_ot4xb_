//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
class patata : public T_ot4xb_base
{
   public:
   
   enum mode_e
   {
      e_status_normal,
      e_status_inside_string_single_quote
      e_status_inside_string_double_quote
      e_status_inside_string_square_bracket
      e_status_inside_comment_asterisk
      e_status_inside_comment_amp
      e_status_inside_comment_slash
      e_status_inside_comment_block
      
      
      
      
      
      e_mode_cbc ,
      e_mode_default = 0
   };
   // ------------------------------            
   enum encode_e
   {
      e_binary    = 0x1000,
      e_hex ,
      e_base64 ,
      e_encode_default = 0      
   };   
   // ------------------------------         
   LONG m_status;   
   // ------------------------------                      

    
   // ------------------------------                         
}