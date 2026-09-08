//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#ifdef __cplusplus
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-class}}*/
/*{{cpp-class_: T_ot4xb_base
   | category: c-api/classes
   | desc: Root of the ot4xb C++ classes: it only redefines the allocation operators, so an object of any class
     derived from it lives in the ot4xb heap whichever module (the DLL, an executable, another DLL) creates or
     deletes it. It has no data members and no virtual functions: deriving from it costs nothing.
     | _kw_: T_ot4xb_base, Class }}*/
class OT4XB_API T_ot4xb_base
{
   public:
       /*{{|method_: `void* operator new( unsigned int )` | desc_: Takes the bytes from the ot4xb heap with
          {{ilink: <c-function _xgrab> _xgrab}}. }}*/
       void * operator new( unsigned int );
       /*{{|method_: `void operator delete( void* )` | desc_: Returns the bytes to the ot4xb heap with
          {{ilink: <c-function _xfree> _xfree}}. }}*/
       void operator delete( void * );
};
/*{{end-cpp-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-class}}*/
/*{{cpp-class_: T_ot4xb_base_with_vheap
   | parent: {{ilink: <cpp-class T_ot4xb_base> T_ot4xb_base}}
   | category: c-api/classes
   | desc: Base of the classes that allocate many small blocks (lists, tables) and can do it from a private heap
     (an OT4XB_VHEAP): the object itself still lives in the ot4xb heap, its items go wherever **m_vheap_flags**
     says. A derived class calls vheap_on_init() when it is built, vheap_on_destroy() when it dies, and
     alloc_bytes() / free_bytes() for every item in between.
     | _kw_: T_ot4xb_base_with_vheap, Class }}*/
class OT4XB_API T_ot4xb_base_with_vheap : public T_ot4xb_base
{
	public:
	/*{{|member_: `OT4XB_VHEAP* m_vheap` | desc_: The private heap in use, 0 when the items go to the ot4xb heap. }}*/
	OT4XB_VHEAP *	m_vheap;
	/*{{|member_: `enum vheap_flags m_vheap_flags` | desc_: How the items are allocated:
	   - `e_zero`: the ot4xb heap, no private heap.
	   - `e_use_custom_heap`: the items come from **m_vheap**.
	   - `e_create_new_heap`: a new private heap is created at init (implies e_use_custom_heap and
	     e_destroy_heap_on_release).
	   - `e_destroy_heap_on_release`: the private heap is destroyed by vheap_on_destroy(). }}*/
	enum vheap_flags
	{
		e_zero = 0x00000000,
		e_use_custom_heap = 0x00000800,
		e_create_new_heap = 0x00000100,
		e_destroy_heap_on_release = 0x00000200
	} m_vheap_flags;
	// ---------------------------------------------------------------------------------
	/*{{|method_: `void vheap_on_init( vheap_flags dw, OT4XB_VHEAP* vheap )`
	   | desc_: Sets up the heap from the flags: with `e_create_new_heap` a new private heap is created and owned
	     (destroyed on release); with `e_use_custom_heap` and a **vheap** the given heap is adopted and never
	     destroyed here; with `e_use_custom_heap` and no vheap a private heap is created and owned as well; with
	     `e_zero` nothing is created and the items go to the ot4xb heap. }}*/
	void vheap_on_init( vheap_flags dw, OT4XB_VHEAP* vheap );
	/*{{|method_: `void vheap_on_destroy( void )`
	   | desc_: Destroys the private heap, and with it every item still allocated in it, when the flags say
	     `e_destroy_heap_on_release`; an adopted heap is left alone. }}*/
	void vheap_on_destroy(void);
	// ---------------------------------------------------------------------------------
	/*{{|method_: `void* alloc_bytes( UINT nBytes )`
	   | desc_: A block of nBytes from the private heap when `e_use_custom_heap` is set (0 when there is no heap),
	     from the ot4xb heap otherwise. }}*/
	void* alloc_bytes( UINT nBytes );
	/*{{|method_: `void free_bytes( void* p )` | desc_: Releases a block obtained with alloc_bytes(). }}*/
	void  free_bytes( void* );
	// ---------------------------------------------------------------------------------
};
/*{{end-cpp-class}}*/

//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-class}}*/
/*{{cpp-class_: TStdCtxCbk
   | category: c-api/classes , runtime/callback
   | desc: A callback thunk with a context: the object **is** 12 bytes of x86 code, and its address can be
     handed to Windows (or to any caller of a `__stdcall` function) as if it were a function. When it is called
     it inserts the context DWORD as the first parameter and jumps to the real function, so a plain C function
     `LRESULT __stdcall f( DWORD* ctx, HWND, UINT, WPARAM, LPARAM )` can be registered as a WNDPROC, and the
     same function can serve any number of windows or objects, each one with its own context. The same trick
     as the window-procedure thunk of ATL (`_stdcallthunk`), in a home-made 12-byte version.
   | note: The bytes are `pop eax` (the return address), `push ctx`, `push eax`, `jmp fp`: nothing is
     executed on return, the real function returns straight to the caller with the stack it expects. The
     object is allocated in the executable heap of ot4xb ({{ilink: <c-function _exec_m_grab> _exec_m_grab}}),
     which is why it can be run, and lives until it is deleted: delete it only when no more calls can arrive.
   | see_also: the macros `_TSTDCTXCBK_PROXI_WNDPROC_` and `_TSTDCTXCBK_SUBCLASS_` of ot4xb_api.h, which use
     it to subclass a window with a C++ method as window procedure.
   | _kw_: TStdCtxCbk, Class }}*/
class OT4XB_API TStdCtxCbk
{
   public:
   /*{{|member_: `WORD m_pw[8]` | desc_: The machine code and its two operands, filled by the constructor. }}*/
   WORD  m_pw[8];
   /*{{|method_: `void* operator new( unsigned int )` | desc_: From the executable heap of ot4xb
      ({{ilink: <c-function _exec_m_grab> _exec_m_grab}}), never from the ordinary heap. }}*/
   void * operator new( unsigned int );
   /*{{|method_: `void operator delete( void* )` | desc_: Back to the executable heap
      ({{ilink: <c-function _exec_m_free> _exec_m_free}}). }}*/
   void operator delete( void * );
   /*{{|method_: `TStdCtxCbk( DWORD dwCtx, DWORD dwFp )`
      | desc_: Builds the thunk: **dwCtx** is the context pushed as first parameter (any DWORD: a pointer to a
        struct, a `this`), **dwFp** the address of the real `__stdcall` function, whose first parameter must be
        that DWORD. The address of the object is the callable function from this moment on. }}*/
   TStdCtxCbk(DWORD dwCtx,DWORD dwFp );
   /*{{|method_: `~TStdCtxCbk( void )` | desc_: Nothing to undo; the code goes away with the object. }}*/
   ~TStdCtxCbk(void);
   /*{{|method_: `DWORD GetCtx( void )` | desc_: The context given to the constructor. }}*/
   DWORD GetCtx(void);
};
/*{{end-cpp-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-class}}*/
/*{{cpp-class_: x_www_form_cp1252_KeyVal_t
   | parent: {{ilink: <cpp-class T_ot4xb_base> T_ot4xb_base}}
   | category: c-api/classes , string/encoding
   | desc: One key=value item of a decoded application/x-www-form-urlencoded string, as laid out by
     {{ilink: <c-function x_www_form_urlencoded_to_cp1252> x_www_form_urlencoded_to_cp1252}}: the key and the
     value are zero-terminated strings inside the decoded block, and the items sit one after another right
     after the {{ilink: <cpp-class x_www_form_cp1252_Header_t> x_www_form_cp1252_Header_t}}. Nothing here is
     allocated on its own: the whole block is released with the string returned by the decoder.
     | _kw_: x_www_form_cp1252_KeyVal_t, Class }}*/
class OT4XB_API x_www_form_cp1252_KeyVal_t : public T_ot4xb_base
{
   public:
   /*{{|member_: `LPSTR m_pKey` | desc_: The decoded key, zero-terminated; an empty string for a value with no
      '=' before it. }}*/
   LPSTR m_pKey;
   /*{{|member_: `UINT m_cbKey` | desc_: Length of the key in bytes, without the terminator. }}*/
   UINT  m_cbKey;
   /*{{|member_: `LPSTR m_pVal` | desc_: The decoded value, zero-terminated; an empty string when there is
      none. }}*/
   LPSTR m_pVal;
   /*{{|member_: `UINT m_cbVal` | desc_: Length of the value in bytes, terminator included (0 when there is
      no value). }}*/
   UINT  m_cbVal;
   // ---------------------------------------------------------------------------------
   /*{{|method_: `x_www_form_cp1252_KeyVal_t* next( void )` | desc_: The item that follows this one in the
      block (the items are contiguous); only the first **m_nItemCount** items of the header are valid. }}*/
   x_www_form_cp1252_KeyVal_t * next(void);
   /*{{|method_: `BOOL read_and_decode( LPSTR& pIn, UINT& cbIn, LPSTR& pOut, UINT& cbOut, void* buffer, BOOL u2a_convert = TRUE )`
      | desc_: Fills this item from the source at **pIn**, up to the next '&' or the end, advancing pIn and
        cbIn and writing the decoded key and value at **pOut** (advanced too, cbOut grows by the bytes written).
        '+' becomes a space, `%XX` one byte, blanks, tabs and line ends are dropped, and a second '=' belongs
        to the value. **buffer** is a work area of at least m_cbBuffer bytes; with **u2a_convert** the value is
        taken as UTF-8 and converted to the ANSI code page. Returns FALSE only when cbIn is already 0.
      | note: Called by the header's decode_and_parse_string(); the decoder functions do the whole job. }}*/
   BOOL read_and_decode(LPSTR & pIn, UINT & cbIn , LPSTR & pOut , UINT & cbOut , void* buffer , BOOL u2a_convert = TRUE);
};
/*{{end-cpp-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-class}}*/
/*{{cpp-class_: x_www_form_cp1252_Header_t
   | parent: {{ilink: <cpp-class T_ot4xb_base> T_ot4xb_base}}
   | category: c-api/classes , string/encoding
   | desc: The index of a decoded application/x-www-form-urlencoded block, the one
     {{ilink: <c-function x_www_form_urlencoded_to_cp1252> x_www_form_urlencoded_to_cp1252}} and
     {{ilink: <c-function x_www_form_urlencoded_ncp> x_www_form_urlencoded_ncp}} return through **ppInfo**.
     Everything lives in one allocation: first the decoded strings, then this header, then one
     {{ilink: <cpp-class x_www_form_cp1252_KeyVal_t> x_www_form_cp1252_KeyVal_t}} per item. Walk the items
     from first() with next(), m_nItemCount times, and release the block by freeing the string pointer.
   | example:
     void* info;
     LPSTR s = x_www_form_urlencoded_to_cp1252( query, (UINT) -1, &info );
     if( s )
     {
        x_www_form_cp1252_Header_t* h = (x_www_form_cp1252_Header_t*) info;
        x_www_form_cp1252_KeyVal_t* k = h->first();
        for( UINT i = 0; i < h->m_nItemCount; i++, k = k->next() )
        {
           use( k->m_pKey, k->m_pVal );
        }
        _xfree( s );
     }
     | _kw_: x_www_form_cp1252_Header_t, Class }}*/
class OT4XB_API x_www_form_cp1252_Header_t : public T_ot4xb_base
{
   public:
   /*{{|member_: `UINT m_cbString` | desc_: Bytes of decoded strings written so far (keys and values with
      their terminators). }}*/
   UINT  m_cbString;
   /*{{|member_: `UINT m_nItemCount` | desc_: Number of valid items after the header. }}*/
   UINT  m_nItemCount;
   /*{{|member_: `LPSTR m_pBuffer` | desc_: Start of the allocation: the decoded strings, and the pointer the
      decoder returns. }}*/
   LPSTR m_pBuffer;
   /*{{|member_: `UINT m_cbBuffer` | desc_: Total size of the allocation in bytes. }}*/
   UINT  m_cbBuffer;
   // ---------------------------------------------------------------------------------
   /*{{|method_: `static LPSTR AllocStr( UINT cb, UINT nItemCount, x_www_form_cp1252_Header_t*& ph )`
      | desc_: Makes the block for a source of **cb** bytes with **nItemCount** items: room for the strings,
        the header and nItemCount + 1 items, in one _xgrab(). Returns the string area and the header
        (zeroed counters) through **ph**. }}*/
   static LPSTR AllocStr(UINT cb,UINT nItemCount , x_www_form_cp1252_Header_t* & ph );
   // ---------------------------------------------------------------------------------
   /*{{|method_: `x_www_form_cp1252_KeyVal_t* first( void )` | desc_: The first item, right after the header. }}*/
   x_www_form_cp1252_KeyVal_t * first(void);
   /*{{|method_: `void decode_and_parse_string( LPSTR p, UINT cb, BOOL u2a_convert = TRUE )`
      | desc_: Decodes the **cb** bytes at **p** (a leading '?' is skipped) into the items of the block,
        one per '&'-separated pair, counting them in m_nItemCount; with **u2a_convert** the values are
        converted from UTF-8 to the ANSI code page. }}*/
   void decode_and_parse_string( LPSTR p , UINT cb , BOOL u2a_convert = TRUE);
   // ---------------------------------------------------------------------------------
};
/*{{end-cpp-class}}*/
// -----------------------------------------------------------------------------------------------------------------

namespace json_ns
{
   OT4XB_API ContainerHandle parse_string_utf8( LPSTR source_string,ContainerHandle expando_class_object, char* add_property_method_name );
   OT4XB_API ContainerHandle parse_string_ansi( LPSTR source_string,ContainerHandle expando_class_object, char* add_property_method_name );
   OT4XB_API void __cdecl serialize( XppParamList pl );
   OT4XB_API void __cdecl serialize_value( TZString& z, ContainerHandle con_value, DWORD pStack, DWORD nMoreFlags, DWORD nDepth );
}
   
   


// ---------------------------------------------------------------------------
// Specialiced forms of _conCall() with some param and return types
// ---------------------------------------------------------------------------
OT4XB_API ContainerHandle _conCallConR( LPSTR pFN , ... );
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN );
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN , BOOL   val);
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN , LONG   val);
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN , LONG   val1 , LONG   val2);
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN, LONG   val1, LONG   val2 , LONG val3);
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN , LONG   val, ContainerHandle con);
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN , LONG   val, ContainerHandle con ,  ContainerHandle con2);
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN , ContainerHandle con);
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN , DWORD  val);
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN , double val);
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN , LPSTR  val);
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN , LPSTR  pStr , LONG val);
       // --------------------------------------------------------------------
OT4XB_API void _conCallVoid( LPSTR pFN );
OT4XB_API void _conCallVoid( LPSTR pFN , BOOL val);
OT4XB_API void _conCallVoid( LPSTR pFN , LONG val);
OT4XB_API void _conCallVoid( LPSTR pFN , LONG val , LONG val2);
OT4XB_API void _conCallVoid( LPSTR pFN , LONG val, ContainerHandle con);
OT4XB_API void _conCallVoid( LPSTR pFN , LONG val, ContainerHandle con,ContainerHandle con2);
OT4XB_API void _conCallVoid( LPSTR pFN , ContainerHandle con);
OT4XB_API void _conCallVoid( LPSTR pFN , DWORD val);
OT4XB_API void _conCallVoid( LPSTR pFN , double val);
OT4XB_API void _conCallVoid( LPSTR pFN , LPSTR val);
OT4XB_API void _conCallVoid( LPSTR pFN , LPSTR pStr , LONG val);
       // --------------------------------------------------------------------
OT4XB_API BOOL _conCallBool( LPSTR pFN );
OT4XB_API BOOL _conCallBool( LPSTR pFN , BOOL val);
OT4XB_API BOOL _conCallBool( LPSTR pFN , LONG val);
OT4XB_API BOOL _conCallBool( LPSTR pFN , LONG val , LONG val2);
OT4XB_API BOOL _conCallBool( LPSTR pFN , LONG val, ContainerHandle con);
OT4XB_API BOOL _conCallBool( LPSTR pFN , LONG val, ContainerHandle con, ContainerHandle con2 );
OT4XB_API BOOL _conCallBool( LPSTR pFN , ContainerHandle con);
OT4XB_API BOOL _conCallBool( LPSTR pFN , DWORD val);
OT4XB_API BOOL _conCallBool( LPSTR pFN , double val);
OT4XB_API BOOL _conCallBool( LPSTR pFN , LPSTR val);
OT4XB_API BOOL _conCallBool( LPSTR pFN , LPSTR pStr , LONG val);
       // --------------------------------------------------------------------
OT4XB_API LONG _conCallLong( LPSTR pFN );
OT4XB_API LONG _conCallLong( LPSTR pFN , BOOL val);
OT4XB_API LONG _conCallLong( LPSTR pFN , LONG val);
OT4XB_API LONG _conCallLong( LPSTR pFN , LONG val , LONG val2);
OT4XB_API LONG _conCallLong( LPSTR pFN , LONG val, ContainerHandle con);
OT4XB_API LONG _conCallLong( LPSTR pFN , LONG val, ContainerHandle con, ContainerHandle con2);
OT4XB_API LONG _conCallLong( LPSTR pFN , ContainerHandle con);
OT4XB_API LONG _conCallLong( LPSTR pFN , DWORD val);
OT4XB_API LONG _conCallLong( LPSTR pFN , double val);
OT4XB_API LONG _conCallLong( LPSTR pFN , LPSTR val);
OT4XB_API LONG _conCallLong( LPSTR pFN , LPSTR pStr , LONG val);
       // --------------------------------------------------------------------
OT4XB_API double _conCallDouble( LPSTR pFN );
OT4XB_API double _conCallDouble( LPSTR pFN , BOOL val);
OT4XB_API double _conCallDouble( LPSTR pFN , LONG val);
OT4XB_API double _conCallDouble( LPSTR pFN , LONG val , LONG val2);
OT4XB_API double _conCallDouble( LPSTR pFN , LONG val, ContainerHandle con);
OT4XB_API double _conCallDouble( LPSTR pFN , LONG val, ContainerHandle con, ContainerHandle con2);
OT4XB_API double _conCallDouble( LPSTR pFN , ContainerHandle con);
OT4XB_API double _conCallDouble( LPSTR pFN , DWORD val);
OT4XB_API double _conCallDouble( LPSTR pFN , double val);
OT4XB_API double _conCallDouble( LPSTR pFN , LPSTR val);
OT4XB_API double _conCallDouble( LPSTR pFN , LPSTR pStr , LONG val);
       // --------------------------------------------------------------------
OT4XB_API FLOAT _conCallFloat( LPSTR pFN );
OT4XB_API FLOAT _conCallFloat( LPSTR pFN , BOOL val);
OT4XB_API FLOAT _conCallFloat( LPSTR pFN , LONG val);
OT4XB_API FLOAT _conCallFloat( LPSTR pFN , LONG val , LONG val2);
OT4XB_API FLOAT _conCallFloat( LPSTR pFN , LONG val, ContainerHandle con);
OT4XB_API FLOAT _conCallFloat( LPSTR pFN , LONG val, ContainerHandle con, ContainerHandle con2);
OT4XB_API FLOAT _conCallFloat( LPSTR pFN , ContainerHandle con);
OT4XB_API FLOAT _conCallFloat( LPSTR pFN , DWORD val);
OT4XB_API FLOAT _conCallFloat( LPSTR pFN , double val);
OT4XB_API FLOAT _conCallFloat( LPSTR pFN , LPSTR val);
OT4XB_API FLOAT _conCallFloat( LPSTR pFN , LPSTR pStr , LONG val);
       // --------------------------------------------------------------------
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN );
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN , BOOL val);
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN , LONG val);
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN , LONG val , LONG val2);
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN, LONG val, LONG val2 , LONG val3);
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN , LONG val, ContainerHandle con);
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN , LONG val, ContainerHandle con, ContainerHandle con2);
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN , ContainerHandle con);
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN , DWORD val);
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN , double val);
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN , LPSTR val);
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN , LPSTR pStr , LONG val);

//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conMCallConNR( LPSTR pFN , ContainerHandle Self , ULONG nParams , ... );
OT4XB_API ContainerHandle _conMCallConN( LPSTR pFN , ContainerHandle Self , ULONG nParams , ... );
// ---------------------------------------------------------------------------
// Specialiced forms of _conCallMethodPa() with some param and return types
// ---------------------------------------------------------------------------
       // --------------------------------------------------------------------
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN   );
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN  ,  BOOL   val);                        
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN  ,  LONG   val);                          
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN  ,  LONG   val, ContainerHandle con);     
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN  ,  ContainerHandle con);                 
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN  ,  DWORD  val);                          
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN  ,  LONG   val1 , LONG   val2);           
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN , LONG   val1 , LONG   val2 , LONG val3);
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN  ,  double val);                         
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN  ,  LPSTR  val);                         
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN , LPSTR  p1 , LPSTR p2);
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN  ,  LPSTR  pStr , LONG val);              
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN  ,  LONG v1,BOOL v2);                     
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN ,  ULONG * pDw );                       
       // --------------------------------------------------------------------
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  );                                              
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , BOOL val);                                    
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , LONG val);                                    
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , LONG val , LONG val2);                        
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , LONG val , LONG val2 , LONG val3);                        
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , LONG val, ContainerHandle con);               
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , ContainerHandle con);                         
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , DWORD val);                                   
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , double val);                                  
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , LPSTR val);                                   
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , LPSTR p1 , LPSTR p2);
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , LPSTR pStr , LONG val);                       
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , LONG v1,BOOL v2);                             
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN , ULONG * pDw );                                 
       // --------------------------------------------------------------------
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN  );
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN  , BOOL val);
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN  , LONG val);
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN  , LONG val , LONG val2);
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN  , LONG val, ContainerHandle con);
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN  , ContainerHandle con);
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN  , DWORD val);
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN  , double val);
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN  , LPSTR val);
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN  , LPSTR pStr , LONG val);
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN  , LONG v1,BOOL v2);
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN , ULONG * pDw );
       // --------------------------------------------------------------------
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN  );
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN  , BOOL val);
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN  , LONG val);
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN  , LONG val , LONG val2);
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN  , LONG val, ContainerHandle con);
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN  , ContainerHandle con);
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN  , DWORD val);
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN  , double val);
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN  , LPSTR val);
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN  , LPSTR pStr , LONG val);
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN  , LONG v1,BOOL v2);
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN , ULONG * pDw );
       // --------------------------------------------------------------------
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN  );
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN  , BOOL val);
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN  , LONG val);
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN  , LONG val , LONG val2);
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN  , LONG val, ContainerHandle con);
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN  , ContainerHandle con);
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN  , DWORD val);
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN  , double val);
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN  , LPSTR val);
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN  , LPSTR pStr , LONG val);
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN  , LONG v1,BOOL v2);
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN , ULONG * pDw );
       // --------------------------------------------------------------------
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN  );
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN  , BOOL val);
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN  , LONG val);
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN  , LONG val , LONG val2);
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN  , LONG val, ContainerHandle con);
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN  , ContainerHandle con);
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN  , DWORD val);
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN  , double val);
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN  , LPSTR val);
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN  , LPSTR pStr , LONG val);
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN  , LONG v1,BOOL v2);
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN , ULONG * pDw );
       // --------------------------------------------------------------------
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN  );
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN  , BOOL val);
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN  , LONG val);
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN  , LONG val , LONG val2);
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self, LPSTR pFN, LONG val, LONG val2, LONG val3 );
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN  , LONG val, ContainerHandle con);
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN  , ContainerHandle con);
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN  , DWORD val);
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN  , double val);
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN  , LPSTR val);
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN  , LPSTR pStr , LONG val);
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN  , LONG v1,BOOL v2);
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN , ULONG * pDw );

OT4XB_API ContainerHandle _conEvalCon( ContainerHandle conb );
OT4XB_API ContainerHandle _conEvalCon( ContainerHandle conb , BOOL   val);
OT4XB_API ContainerHandle _conEvalCon( ContainerHandle conb , LONG   val);
OT4XB_API ContainerHandle _conEvalCon( ContainerHandle conb , LONG   val, ContainerHandle con);
OT4XB_API ContainerHandle _conEvalCon( ContainerHandle conb , ContainerHandle con);
OT4XB_API ContainerHandle _conEvalCon( ContainerHandle conb , DWORD  val);
OT4XB_API ContainerHandle _conEvalCon( ContainerHandle conb , LONG   val1 , LONG   val2);
OT4XB_API ContainerHandle _conEvalCon( ContainerHandle conb , double val);
OT4XB_API ContainerHandle _conEvalCon( ContainerHandle conb , LPSTR  val);
OT4XB_API ContainerHandle _conEvalCon( ContainerHandle conb , LPSTR  pStr , LONG val);
       // --------------------------------------------------------------------
OT4XB_API void _conEvalVoid( ContainerHandle conb );
OT4XB_API void _conEvalVoid( ContainerHandle conb , BOOL val);
OT4XB_API void _conEvalVoid( ContainerHandle conb , LONG val);
OT4XB_API void _conEvalVoid( ContainerHandle conb , LONG val , LONG val2);
OT4XB_API void _conEvalVoid( ContainerHandle conb , LONG val, ContainerHandle con);
OT4XB_API void _conEvalVoid( ContainerHandle conb , ContainerHandle con);
OT4XB_API void _conEvalVoid( ContainerHandle conb , DWORD val);
OT4XB_API void _conEvalVoid( ContainerHandle conb , double val);
OT4XB_API void _conEvalVoid( ContainerHandle conb , LPSTR val);
OT4XB_API void _conEvalVoid( ContainerHandle conb , LPSTR pStr , LONG val);
       // --------------------------------------------------------------------
OT4XB_API BOOL _conEvalBool( ContainerHandle conb );
OT4XB_API BOOL _conEvalBool( ContainerHandle conb , BOOL val);
OT4XB_API BOOL _conEvalBool( ContainerHandle conb , LONG val);
OT4XB_API BOOL _conEvalBool( ContainerHandle conb , LONG val , LONG val2);
OT4XB_API BOOL _conEvalBool( ContainerHandle conb , LONG val, ContainerHandle con);
OT4XB_API BOOL _conEvalBool( ContainerHandle conb , ContainerHandle con);
OT4XB_API BOOL _conEvalBool( ContainerHandle conb , DWORD val);
OT4XB_API BOOL _conEvalBool( ContainerHandle conb , double val);
OT4XB_API BOOL _conEvalBool( ContainerHandle conb , LPSTR val);
OT4XB_API BOOL _conEvalBool( ContainerHandle conb , LPSTR pStr , LONG val);
       // --------------------------------------------------------------------
OT4XB_API LONG _conEvalLong( ContainerHandle conb );
OT4XB_API LONG _conEvalLong( ContainerHandle conb , BOOL val);
OT4XB_API LONG _conEvalLong( ContainerHandle conb , LONG val);
OT4XB_API LONG _conEvalLong( ContainerHandle conb , LONG val , LONG val2);
OT4XB_API LONG _conEvalLong( ContainerHandle conb , LONG val, ContainerHandle con);
OT4XB_API LONG _conEvalLong( ContainerHandle conb , ContainerHandle con);
OT4XB_API LONG _conEvalLong( ContainerHandle conb , DWORD val);
OT4XB_API LONG _conEvalLong( ContainerHandle conb , double val);
OT4XB_API LONG _conEvalLong( ContainerHandle conb , LPSTR val);
OT4XB_API LONG _conEvalLong( ContainerHandle conb , LPSTR pStr , LONG val);
       // --------------------------------------------------------------------
OT4XB_API double _conEvalDouble( ContainerHandle conb );
OT4XB_API double _conEvalDouble( ContainerHandle conb , BOOL val);
OT4XB_API double _conEvalDouble( ContainerHandle conb , LONG val);
OT4XB_API double _conEvalDouble( ContainerHandle conb , LONG val , LONG val2);
OT4XB_API double _conEvalDouble( ContainerHandle conb , LONG val, ContainerHandle con);
OT4XB_API double _conEvalDouble( ContainerHandle conb , ContainerHandle con);
OT4XB_API double _conEvalDouble( ContainerHandle conb , DWORD val);
OT4XB_API double _conEvalDouble( ContainerHandle conb , double val);
OT4XB_API double _conEvalDouble( ContainerHandle conb , LPSTR val);
OT4XB_API double _conEvalDouble( ContainerHandle conb , LPSTR pStr , LONG val);
       // --------------------------------------------------------------------
OT4XB_API FLOAT _conEvalFloat( ContainerHandle conb );
OT4XB_API FLOAT _conEvalFloat( ContainerHandle conb , BOOL val);
OT4XB_API FLOAT _conEvalFloat( ContainerHandle conb , LONG val);
OT4XB_API FLOAT _conEvalFloat( ContainerHandle conb , LONG val , LONG val2);
OT4XB_API FLOAT _conEvalFloat( ContainerHandle conb , LONG val, ContainerHandle con);
OT4XB_API FLOAT _conEvalFloat( ContainerHandle conb , ContainerHandle con);
OT4XB_API FLOAT _conEvalFloat( ContainerHandle conb , DWORD val);
OT4XB_API FLOAT _conEvalFloat( ContainerHandle conb , double val);
OT4XB_API FLOAT _conEvalFloat( ContainerHandle conb , LPSTR val);
OT4XB_API FLOAT _conEvalFloat( ContainerHandle conb , LPSTR pStr , LONG val);
       // --------------------------------------------------------------------
OT4XB_API LPSTR _conEvalLpstr( ContainerHandle conb );
OT4XB_API LPSTR _conEvalLpstr( ContainerHandle conb , BOOL val);
OT4XB_API LPSTR _conEvalLpstr( ContainerHandle conb , LONG val);
OT4XB_API LPSTR _conEvalLpstr( ContainerHandle conb , LONG val , LONG val2);
OT4XB_API LPSTR _conEvalLpstr( ContainerHandle conb , LONG val, ContainerHandle con);
OT4XB_API LPSTR _conEvalLpstr( ContainerHandle conb , ContainerHandle con);
OT4XB_API LPSTR _conEvalLpstr( ContainerHandle conb , DWORD val);
OT4XB_API LPSTR _conEvalLpstr( ContainerHandle conb , double val);
OT4XB_API LPSTR _conEvalLpstr( ContainerHandle conb , LPSTR val);
OT4XB_API LPSTR _conEvalLpstr( ContainerHandle conb , LPSTR pStr , LONG val);
       // --------------------------------------------------------------------





// ---------------------------------------------------------------------------
// DrTool
// ---------------------------------------------------------------------------
OT4XB_API TList * Path2TList( LPSTR pPath );





// ---------------------------------------------------------------------------
// String
// ---------------------------------------------------------------------------
OT4XB_API BOOL TZString_urlencode_add(TZString* psc , LPSTR pIn , DWORD cb );
OT4XB_API BOOL TZString_urlencode_add_con(TZString* psc , ContainerHandle con );
OT4XB_API BOOL TZString_add_con(TZString* psc , ContainerHandle con );

// -----------------------------------------------------------------------------------------------------------------
#include <gdiplus_helper.h>
// -----------------------------------------------------------------------------------------------------------------







#endif