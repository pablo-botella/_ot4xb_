//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#pragma once
// -----------------------------------------------------------------------------------------------------------------
BEGIN_NAMESPACE( ndtg_ns )
// -----------------------------------------------------------------------------------------------------------------
class ndtg_item_t;
class ndtg_prop_t;
class ndtg_type_t;
class ndtg_typelist_t;
class attrib_t;
// -----------------------------------------------------------------------------------------------------------------
class OT4XB_API attrib_t : public T_ot4xb_base
{
   public:
   // ---------------------------------------------------------------------------------
   attrib_t* m_pNext;
   LPSTR     m_pKey;
   LPSTR     m_pVal;
   DWORD     m_dwKeyCrc32;
   // ---------------------------------------------------------------------------------
   attrib_t(LPSTR pKey , LPSTR pVal);
   ~attrib_t(void);
   // ---------------------------------------------------------------------------------
};
// -----------------------------------------------------------------------------------------------------------------
class OT4XB_API ndtg_type_t : public T_ot4xb_base
{
   public:
      // ---------------------------------------------------------------------------------
      ndtg_type_t*          m_pNext;
      ndtg_type_t*          m_pPrev;
      ndtg_prop_t*          m_pProps;
      ndtg_typelist_t*      m_pTable;
      LPSTR                 m_pTypeName;
      DWORD                 m_dwTypeCrc;
      ContainerHandle       m_con;
      ContainerHandle       m_conb_on_attrib; // how to handle xml attributes     
      ContainerHandle       m_conb_child_pop;
      DWORD                 m_dwAttrib;
      // ---------------------------------------------------------------------------------
      ndtg_type_t( LPSTR pTypeName , ContainerHandle con = 0, DWORD dwAttrib = 0 );
      ~ndtg_type_t(void);
      // ---------------------------------------------------------------------------------
      ndtg_prop_t* find_prop( LPSTR pPropName );
      void AddProp( ndtg_prop_t* pProp );
      ndtg_prop_t* AddProp(LPSTR pPropName,LPSTR pTypeName,ContainerHandle con = 0,DWORD dwAttrib = 0);

};
// -----------------------------------------------------------------------------------------------------------------
class OT4XB_API ndtg_typelist_t : public T_ot4xb_base
{
   public:
      // ---------------------------------------------------------------------------------
      ndtg_type_t*          m_pFirst;
      LPSTR                 m_pPropPrefix;
      // ---------------------------------------------------------------------------------
      ndtg_typelist_t(LPSTR pPropPrefix = 0);
      ~ndtg_typelist_t(void);
      // ---------------------------------------------------------------------------------
      void Add( ndtg_type_t* pType );
      ndtg_type_t* Add( LPSTR pTypeName , ContainerHandle con = 0, DWORD dwAttrib = 0 );
      ndtg_type_t* _find_( LPSTR pName );
      // ---------------------------------------------------------------------------------
};
// -----------------------------------------------------------------------------------------------------------------
class OT4XB_API ndtg_prop_t : public T_ot4xb_base
{
   public:
      // ---------------------------------------------------------------------------------
      ndtg_prop_t*          m_pNext;
      ndtg_prop_t*          m_pPrev;
      ndtg_type_t*          m_pType;
      LPSTR                 m_pPropName;
      DWORD                 m_dwPropCrc;
      ContainerHandle       m_con;
      DWORD                 m_dwAttrib;
      // ---------------------------------------------------------------------------------
      ndtg_prop_t( LPSTR pPropName , ndtg_type_t* pType = 0 , ContainerHandle con = 0, DWORD dwAttrib = 0 );
      ~ndtg_prop_t( void );
      // ---------------------------------------------------------------------------------
      BOOL SetChildStackItem( LPSTR pKey , ndtg_item_t* pItem );
      BOOL SetStackItem( ndtg_item_t* pItem );
      // ---------------------------------------------------------------------------------
};
// -----------------------------------------------------------------------------------------------------------------
class OT4XB_API ndtg_item_t : public T_ot4xb_base
{
   public:
      // ---------------------------------------------------------------------------------
      ndtg_item_t*          m_pNext;
      ndtg_item_t*          m_pPrev;
      ndtg_prop_t*          m_pProp;
      ContainerHandle       m_conItem;
      BOOL                  m_bSealed;
      LONG                  m_nDepth;
      BOOL                  m_bDynamicProp;
      attrib_t*             m_pAttrib;            
      // ---------------------------------------------------------------------------------
      ndtg_item_t( void );
      ~ndtg_item_t( void );
      // ---------------------------------------------------------------------------------
      void PutVal( LPSTR pStr );
      void attrib_add(LPSTR pKey , LPSTR pVal );      
      void eval_attrib(void);            
      
      // ---------------------------------------------------------------------------------
};
// -----------------------------------------------------------------------------------------------------------------
class OT4XB_API ndtg_stack_t : public T_ot4xb_base
{
   public:
      // ---------------------------------------------------------------------------------
      ndtg_item_t*          m_pFirst;
      ndtg_item_t*          m_pLast;
      ndtg_typelist_t*      m_pTypeList;
      ContainerHandle       m_conResult;
      ndtg_prop_t*          m_pResultProp;

      // ---------------------------------------------------------------------------------
      ndtg_stack_t( ndtg_typelist_t* pTypeList ,ndtg_type_t* pResultType, DWORD nResultFlags);
      ~ndtg_stack_t( void );
      // ---------------------------------------------------------------------------------
      void depth_control(LONG nDepth);
      void pop_step(void);
      // ---------------------------------------------------------------------------------
      ndtg_item_t* pop(void);
      void push( ndtg_item_t* pItem );
      BOOL step( LPSTR pKey , LONG nDepth);
      void seal(void);
      BOOL unsealed(void);
      void putval(LPSTR pVal = 0);
      ContainerHandle GetResult( ContainerHandle conr = 0 );
      void attrib(LPSTR pAttrib, LPSTR pVal);
};
// -----------------------------------------------------------------------------------------------------------------
class OT4XB_API ndtg_xstack_t : public T_ot4xb_base
{
      // ---------------------------------------------------------------------------------
   public:
      // ---------------------------------------------------------------------------------
      class recursion_t;
      class item_t;      
      // ---------------------------------------------------------------------------------
      class OT4XB_API recursion_t : public T_ot4xb_base
      {
         public:
            // ---------------------------------------------------------------------------------
            recursion_t*            m_pNext;            
            DWORD                   m_id;
            ContainerHandle         m_con;
            // ---------------------------------------------------------------------------------
            recursion_t(DWORD id, ContainerHandle con);
            ~recursion_t(void);
            // ---------------------------------------------------------------------------------
      };            
      // ---------------------------------------------------------------------------------
      class OT4XB_API item_t : public T_ot4xb_base
      {
         public:      
         // ---------------------------------------------------------------------------------
         enum xtype_t
         {
            XTYPE_CHARACTER      = 0x110CAD95 ,
            XTYPE_MEMO           = 0x092256F5 ,
            XTYPE_DOUBLE         = 0xAE40EED2 ,
            XTYPE_INT32          = 0xF07331AE ,
            XTYPE_DATE           = 0x08F6F1A5 ,
            XTYPE_LOGICAL        = 0x6F8BBE55 ,
            XTYPE_NIL            = 0x42846F86 ,
            XTYPE_FILETIME64     = 0x1B430155 ,
            XTYPE_CODEBLOCK      = 0x6AA39059 ,
            XTYPE_ARRAY          = 0xB7C24934 ,
            XTYPE_OBJECT         = 0xDC0AB7D1 ,
            XTYPE_RECURSION      = 0x3661F1CC
         };
         // ---------------------------------------------------------------------------------
         public:
            // ---------------------------------------------------------------------------------
            item_t*                 m_pNext;
            item_t*                 m_pPrev;
            attrib_t*               m_pAttrib;
            xtype_t                 m_pType;
            ContainerHandle         m_con;
            BOOL                    m_bSealed;
            LONG                    m_nDepth;
            // ---------------------------------------------------------------------------------
            item_t(LPSTR pName, LONG nDepth);
            ~item_t(void);
            void attrib_add(LPSTR pKey , LPSTR pVal );
            LPSTR attrib_get(LPSTR pKey);
            LONG attrib_get_int32(LPSTR pKey);            
            double attrib_get_double(LPSTR pKey);                        
            // ---------------------------------------------------------------------------------
            LPSTR get_last_path_component_as_LPSTR(void);            
            LONG  get_last_path_component_as_int32(void);                        
            // ---------------------------------------------------------------------------------
            void seal(void);
            void attrib_seal(ndtg_xstack_t* pStack );                        
            void putval(LPSTR pVal = 0);            
      };
      // ---------------------------------------------------------------------------------

   public:      
      // ---------------------------------------------------------------------------------
      item_t*           m_pFirst;
      item_t*           m_pLast;
      recursion_t*      m_pRecursion;                  
      ContainerHandle   m_conResult;
      // ---------------------------------------------------------------------------------
      void push( item_t* pItem );
      item_t* pop( void );
      void pop_step(void);
      void depth_control(LONG nDepth);
      // ---------------------------------------------------------------------------------
      void recursion_add(DWORD id, ContainerHandle con);
      ContainerHandle recursion_get(DWORD id);
      // ---------------------------------------------------------------------------------
      
      // ---------------------------------------------------------------------------------            
   public:      
      // ---------------------------------------------------------------------------------      
      ndtg_xstack_t( void );
      ~ndtg_xstack_t( void );
      BOOL step( LPSTR pKey , LONG nDepth);
      void attrib_seal(void);
      void seal(void);
      BOOL unsealed(void);
      void putval(LPSTR pVal = 0);
      void attrib(LPSTR pAttrib, LPSTR pVal = 0);
      ContainerHandle GetResult( ContainerHandle conr = 0 );
      // ---------------------------------------------------------------------------------
};
// -----------------------------------------------------------------------------------------------------------------
class OT4XB_API ndtg_t : public T_ot4xb_base
{
   public:
      // ---------------------------------------------------------------------------------
      enum qualifier_t
      {
         q_unknow         = 0 ,
         q_ndtg_stack_t   = 1 ,
         q_ndtg_xstack_t  = 2
      };
      // ---------------------------------------------------------------------------------
      void*        m_p;
      qualifier_t  m_q;
      // ---------------------------------------------------------------------------------
      ndtg_t(void){ m_p = 0; m_q = q_unknow;};
      ndtg_t(ndtg_stack_t* p){ m_p = (void*) p; m_q = q_ndtg_stack_t;};
      ndtg_t(ndtg_xstack_t* p){ m_p = (void*) p; m_q = q_ndtg_xstack_t;};
      // ---------------------------------------------------------------------------------
      ~ndtg_t(void)
      {
         if( !m_p ){ return; }
         switch( m_q )
         {
            case q_ndtg_stack_t  : { delete reinterpret_cast<ndtg_stack_t*>( m_p ); break;}
            case q_ndtg_xstack_t : { delete reinterpret_cast<ndtg_xstack_t*>( m_p ); break;}
         }
         m_p = 0;
      };
      // ---------------------------------------------------------------------------------
};
// -----------------------------------------------------------------------------------------------------------------
END_NAMESPACE()
// -----------------------------------------------------------------------------------------------------------------



