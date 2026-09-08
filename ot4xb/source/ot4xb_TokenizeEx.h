//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-class}}*/
/*{{cpp-class_: TokenizeEx_t
   | parent: {{ilink: <cpp-class T_ot4xb_base> T_ot4xb_base}}
   | category: c-api/classes , string
   | desc: Splits a byte buffer by literal separators of any length: the buffer is copied in, the separators
     registered, and run() leaves in **m_item_list** one item per token (start and length inside the copy),
     empty tokens included. At every position the separators are tried in registration order and the first
     that matches is consumed. It is the engine of the Xbase++ function
     {{ilink: <function TokenizeEx> TokenizeEx}}, which run_xbase() implements end to end.
   | example:
     TokenizeEx_t k;
     k.SetBuffer( (LPBYTE) "a, b;c", 6 );
     k.AddSeparator( (LPBYTE) ", ", 2 );
     k.AddSeparator( (LPBYTE) ";", 1 );
     k.run();                        // three items: "a", "b", "c"
     for( UINT i = 0; i < k.m_item_list->Count(); i++ )
     {
        TokenizeEx_t::item_t* it = (TokenizeEx_t::item_t*) k.m_item_list->Get( i );
        use( it->m_start, it->m_cb );
     }
     | _kw_: TokenizeEx_t, Class }}*/
class OT4XB_API TokenizeEx_t : public T_ot4xb_base
{
   public:
      // ---------------------------------------------------------------------------------
      /*{{|member_: `class separator_t` | desc_: One separator: its own copy of the bytes (**m_str**,
         **m_cb**) and `test( p, cb )`, TRUE when the bytes at p start with it. }}*/
      class separator_t : public T_ot4xb_base
      {
         public:
         LPBYTE m_str;
         int    m_cb;
         // ---------------------------------------------------------------------------------
         separator_t( LPBYTE str = 0,  int cb = 0);
         ~separator_t(void);
         // ---------------------------------------------------------------------------------
         BOOL test(LPBYTE p , int cb );
         // ---------------------------------------------------------------------------------
      };
      // ---------------------------------------------------------------------------------
      /*{{|member_: `class item_t` | desc_: One token: **m_start** points inside the buffer copy and **m_cb**
         is its length (0 for an empty token). }}*/
      class item_t : public T_ot4xb_base
      {
         public:
         LPBYTE m_start;
         int    m_cb;
         // ---------------------------------------------------------------------------------
         item_t( LPBYTE start = 0,  int cb = 0);
         // ---------------------------------------------------------------------------------
      };
      // ---------------------------------------------------------------------------------
      /*{{|member_: `TList* m_sep_list` | desc_: The separators, in registration order. }}*/
      TList* m_sep_list;
      /*{{|member_: `TList* m_item_list` | desc_: The tokens found by the last run(). }}*/
      TList* m_item_list;
      /*{{|member_: `LPBYTE m_buffer` | desc_: The copy of the text being split. }}*/
      LPBYTE m_buffer;
      /*{{|member_: `int m_cb` | desc_: Its length. }}*/
      int    m_cb;
      // ---------------------------------------------------------------------------------
      /*{{|method_: `TokenizeEx_t( void )` | desc_: Empty lists, no buffer. }}*/
      TokenizeEx_t(void);
      /*{{|method_: `~TokenizeEx_t( void )` | desc_: Frees the separators, the tokens and the buffer. }}*/
      ~TokenizeEx_t(void);
      // ---------------------------------------------------------------------------------
      /*{{|method_: `void ClearItemList( void )` | desc_: Deletes the tokens of the last run. }}*/
      void ClearItemList(void);
      /*{{|method_: `void FreeBuffer( void )` | desc_: Deletes the tokens and frees the buffer. }}*/
      void FreeBuffer(void);
      /*{{|method_: `void SetBuffer( LPBYTE buffer, int cb )` | desc_: Copies **cb** bytes in as the text to
         split (replacing the previous one). }}*/
      void SetBuffer( LPBYTE buffer , int cb );
      /*{{|method_: `void SetBuffer( XppParamList pl, ULONG nParam )` | desc_: Copies the Character parameter
         **nParam** in as the text to split. }}*/
      void SetBuffer( XppParamList pl , ULONG nParam);
      /*{{|method_: `void AddSeparator( LPBYTE s, int cb )` | desc_: Registers a separator of **cb** bytes
         (copied); an empty one is ignored. }}*/
      void AddSeparator( LPBYTE s , int cb );
      // ---------------------------------------------------------------------------------
      /*{{|method_: `int test_sep( LPBYTE p, int cb )` | desc_: The length of the first separator found at
         **p**, 0 when none starts there. }}*/
      int test_sep( LPBYTE p , int cb ); // separator size or 0 if not sep
      // ---------------------------------------------------------------------------------
      /*{{|method_: `void run( void )` | desc_: Splits the buffer: **m_item_list** gets one token per stretch
         between separators, so a buffer with n separators gives n + 1 tokens (an empty buffer gives none). }}*/
      void run(void);
      /*{{|method_: `void run_xbase( XppParamList pl )` | desc_: The whole Xbase++ function: parameter 1 is the
         text, parameter 2 one separator or an array of them, and the tokens are returned as an array of
         Character values. }}*/
      void run_xbase( XppParamList pl );
      // ---------------------------------------------------------------------------------
};
/*{{end-cpp-class}}*/
//----------------------------------------------------------------------------------------------------------------------








