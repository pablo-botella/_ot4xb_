//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#ifdef __cplusplus
//----------------------------------------------------------------------------------------------------------------------
class OT4XB_API T_ot4xb_base
{
   public:
       void * operator new( unsigned int );
       void operator delete( void * );
};
//----------------------------------------------------------------------------------------------------------------------
class OT4XB_API T_ot4xb_base_with_vheap : public T_ot4xb_base
{
	public:
	OT4XB_VHEAP *	m_vheap;
	enum vheap_flags
	{
		e_zero = 0x00000000,
		e_use_custom_heap = 0x00000800,
		e_create_new_heap = 0x00000100,
		e_destroy_heap_on_release = 0x00000200
	} m_vheap_flags;
	// ---------------------------------------------------------------------------------
	void vheap_on_init( vheap_flags dw, OT4XB_VHEAP* vheap );
	void vheap_on_destroy(void);
	// ---------------------------------------------------------------------------------
	void* alloc_bytes( UINT nBytes );
	void  free_bytes( void* );
	// ---------------------------------------------------------------------------------
};

//-----------------------------------------------------------------------------------------------------------------------
class OT4XB_API TStdCtxCbk : public T_ot4xb_base
{
   public:
   WORD  m_pw[8];
   TStdCtxCbk(DWORD dwCtx,DWORD dwFp );
   ~TStdCtxCbk(void);
   DWORD GetCtx(void);
};
// -----------------------------------------------------------------------------------------------------------------
class OT4XB_API x_www_form_cp1252_KeyVal_t : public T_ot4xb_base
{
   public:
   LPSTR m_pKey;
   UINT  m_cbKey;
   LPSTR m_pVal;
   UINT  m_cbVal;  
   // ---------------------------------------------------------------------------------
   x_www_form_cp1252_KeyVal_t * next(void);
   BOOL read_and_decode(LPSTR & pIn, UINT & cbIn , LPSTR & pOut , UINT & cbOut , void* buffer , BOOL u2a_convert = TRUE);
};
// -----------------------------------------------------------------------------------------------------------------
class OT4XB_API x_www_form_cp1252_Header_t : public T_ot4xb_base
{
   public:
   UINT  m_cbString;
   UINT  m_nItemCount;   
   LPSTR m_pBuffer;         
   UINT  m_cbBuffer;         
   // ---------------------------------------------------------------------------------
   static LPSTR AllocStr(UINT cb,UINT nItemCount , x_www_form_cp1252_Header_t* & ph );
   // ---------------------------------------------------------------------------------   
   x_www_form_cp1252_KeyVal_t * first(void);
   void decode_and_parse_string( LPSTR p , UINT cb , BOOL u2a_convert = TRUE);
   // ---------------------------------------------------------------------------------      
};   
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