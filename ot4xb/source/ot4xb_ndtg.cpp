//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
// Node Trigger API
//------------------------------------------------------------
#include <ot4xb_api.h>
#include <stdlib.h>
#include <stdio.h>
// -----------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------
using namespace ndtg_ns;
// -----------------------------------------------------------------------------------------------------------------
attrib_t::attrib_t(LPSTR pKey, LPSTR pVal)
{
   UINT cb = 0;

   m_pNext = 0;
   m_pKey  = _xstrdupandgetlen(pKey,&cb);
   m_pVal  = _xstrdup(pVal);
   m_dwKeyCrc32  = dwCrc32Lower(0,(LPBYTE) pKey,cb);
}
// -----------------------------------------------------------------------------------------------------------------
attrib_t::~attrib_t(void)
{
   attrib_t* pNext = m_pNext;
   while( pNext )
   {
      attrib_t* p = pNext->m_pNext;
      pNext->m_pNext = 0;
      delete pNext;
      pNext = p;
   }
   m_pNext = 0;
   if( m_pKey ){ _xfree( m_pKey); }
   m_pKey  = 0; m_dwKeyCrc32  = 0;
   if( m_pVal ){ _xfree( m_pVal); }
   m_pVal  = 0;
}
// -----------------------------------------------------------------------------------------------------------------
ndtg_type_t::ndtg_type_t( LPSTR pTypeName, ContainerHandle con, DWORD dwAttrib)
{
   UINT cb = 0;

   m_pNext       = 0;
   m_pPrev       = 0;
   m_pProps      = 0;
   m_pTypeName   = _xstrdupandgetlen(pTypeName,&cb);
   m_dwTypeCrc   = dwCrc32(0,(LPBYTE) m_pTypeName , cb );
   m_con         = _conNew( con );
   m_conb_on_attrib  = NULLCONTAINER; 
   m_dwAttrib    = dwAttrib;
   m_pTable      = 0;
   m_conb_child_pop = NULLCONTAINER;
}
//----------------------------------------------------------------------------------------------------------------------
ndtg_type_t::~ndtg_type_t(void)
{

   m_dwTypeCrc = 0;
   while(m_pProps)
   {
      ndtg_prop_t* p = m_pProps;
      m_pProps       = m_pProps->m_pNext;
      if( m_pProps ){ m_pProps->m_pPrev = 0;}
      p->m_pNext = 0;
      p->m_pPrev = 0;
      delete p;
   }
   if( m_pNext ){ m_pNext->m_pPrev = m_pPrev; }
   if( m_pPrev ){ m_pPrev->m_pNext = m_pNext; }
   if( m_pTypeName ){ _xfree( (void*) m_pTypeName ); m_pTypeName = 0;}
   if( m_con ){_conRelease( m_con); m_con = 0; }
   if( m_conb_on_attrib){_conRelease( m_conb_on_attrib); m_conb_on_attrib = 0; }   
   if( m_conb_child_pop){_conRelease( m_conb_child_pop); m_conb_child_pop = 0; }      
   
   m_pTable      = 0;   
}
//----------------------------------------------------------------------------------------------------------------------
void ndtg_type_t::AddProp( ndtg_prop_t* pProp)
{
   pProp->m_pNext = 0;
   pProp->m_pPrev = 0;
   if( m_pProps )
   {
      ndtg_prop_t* p = m_pProps;
      while( p->m_pNext ){ p = p->m_pNext; }
      pProp->m_pPrev = p;
      p->m_pNext = pProp;
   }
   else { m_pProps = pProp; }
}
// -----------------------------------------------------------------------------------------------------------------
ndtg_prop_t* ndtg_type_t::find_prop( LPSTR pName)
{
   ndtg_prop_t* p;
   UINT  cb;
   DWORD dwCrc;   
   if( !pName ) return 0;
   cb    = _xstrlen(pName);
   if( !cb ) return 0;   
   dwCrc = dwCrc32(0,(LPBYTE) pName,cb);   
   for( p = m_pProps; p ; p = p->m_pNext)
   {
      if( p->m_dwPropCrc == dwCrc )
      {
         if( _xstrcmp(pName,p->m_pPropName) == 0 ){ return p; }
      }
   }
   return 0;
}   
// -----------------------------------------------------------------------------------------------------------------
ndtg_prop_t* ndtg_type_t::AddProp(LPSTR pPropName,LPSTR pTypeName,ContainerHandle con,DWORD dwAttrib)      
{

   if( !( pPropName && pTypeName && m_pTable) ){ return 0;}
   ndtg_type_t* pt = m_pTable->Add(pTypeName,0,0);   
   if( !pt ){ return 0;}
   ndtg_prop_t* pp = find_prop(pPropName);
   if( pp )
   {
      if(con) pp->m_con = _conPut(pp->m_con,con);
      pp->m_dwAttrib |= dwAttrib;   
   }
   else
   {
      pp = new ndtg_prop_t(pPropName,pt,con,dwAttrib);
      AddProp(pp);
   }
   return pp;      
}
// -----------------------------------------------------------------------------------------------------------------
ndtg_typelist_t::ndtg_typelist_t(LPSTR pPropPrefix)

{
   m_pFirst = 0;
   m_pPropPrefix = ( pPropPrefix  ? _xstrdup(pPropPrefix) : 0 );      
}
// -----------------------------------------------------------------------------------------------------------------
ndtg_typelist_t::~ndtg_typelist_t(void)
{
   while(m_pFirst)
   {
      ndtg_type_t* p = m_pFirst;
      m_pFirst  = m_pFirst->m_pNext;
      if( m_pFirst ){ m_pFirst->m_pPrev = 0;}
      p->m_pNext = 0;
      p->m_pPrev = 0;
      delete p;
   }
   if( m_pPropPrefix )
   {
      _xfree( (void*) m_pPropPrefix );
      m_pPropPrefix = 0;
   }
}
// -----------------------------------------------------------------------------------------------------------------
void ndtg_typelist_t::Add( ndtg_type_t* pType )
{
   pType->m_pNext  = 0;
   pType->m_pPrev  = 0;
   pType->m_pTable = this; 
   
   if( m_pFirst )
   {
      ndtg_type_t* p = m_pFirst;
      while( p->m_pNext ){ p = p->m_pNext; }
      pType->m_pPrev = p;
      p->m_pNext = pType;
   }
   else { m_pFirst = pType ; }
}
// -----------------------------------------------------------------------------------------------------------------
ndtg_type_t* ndtg_typelist_t::Add( LPSTR pTypeName,ContainerHandle con,DWORD dwAttrib)
{
   if( !pTypeName ) return 0;
   ndtg_type_t* pt = _find_(pTypeName);
   if( pt )
   {
      if(con) pt->m_con = _conPut(pt->m_con,con);
      pt->m_dwAttrib |= dwAttrib;
   }
   else
   {
      pt = new ndtg_type_t(pTypeName,con,dwAttrib);
      Add(pt);
   }
   return pt;
}      
// -----------------------------------------------------------------------------------------------------------------
ndtg_type_t* ndtg_typelist_t::_find_( LPSTR pName )
{
   UINT  cb;
   DWORD dwCrc;
   ndtg_type_t* p = m_pFirst;
   if(!p) return 0;
   if(!pName) return 0;
   cb    = _xstrlen(pName);
   if( !cb ) return 0;
   dwCrc = dwCrc32(0,(LPBYTE) pName,cb);
   while( p )
   {
      if( dwCrc == p->m_dwTypeCrc )
      {
         if( _xstrcmp(pName,p->m_pTypeName) == 0 ){ return p; }
      }
      p = p->m_pNext;
   }
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
ndtg_prop_t::ndtg_prop_t( LPSTR pPropName , ndtg_type_t* pType , ContainerHandle con , DWORD dwAttrib )
{
   UINT cb = 0;
   m_pNext         = 0;
   m_pPrev         = 0;
   m_pType         = pType;
   m_pPropName     = _xstrdupandgetlen(pPropName,&cb);
   m_dwPropCrc     = dwCrc32(0,(LPBYTE) m_pPropName , cb );
   m_con          = _conNew( con );
   m_dwAttrib      = dwAttrib;
}
// -----------------------------------------------------------------------------------------------------------------
ndtg_prop_t::~ndtg_prop_t( void )
{
   m_dwPropCrc = 0;
   if( m_pNext ){ m_pNext->m_pPrev = m_pPrev; }
   if( m_pPrev ){ m_pPrev->m_pNext = m_pNext; }
   if( m_pPropName ){ _xfree( (void*) m_pPropName ); m_pPropName = 0;}
   if( m_con ){_conRelease( m_con); m_con = 0; }
}
// -----------------------------------------------------------------------------------------------------------------
BOOL ndtg_prop_t::SetChildStackItem( LPSTR pKey , ndtg_item_t* pItem )
{
   if( m_dwAttrib & XPP_ARRAY )
   {
      pItem->m_bDynamicProp = TRUE;
      pItem->m_pProp        = new ndtg_prop_t( pKey,m_pType,0,m_pType->m_dwAttrib);
      return pItem->m_pProp->SetStackItem(pItem);      
   }
   if( m_dwAttrib & XPP_OBJECT )   
   {
      pItem->m_bDynamicProp = FALSE;   
      pItem->m_pProp = m_pType->find_prop(pKey);
      if( pItem->m_pProp )
      {
         return pItem->m_pProp->SetStackItem(pItem);            
      }
   }
   return FALSE;
}
// -----------------------------------------------------------------------------------------------------------------
BOOL ndtg_prop_t::SetStackItem( ndtg_item_t* pItem )
{
   pItem->m_pProp = this;
   if( m_pType->m_dwAttrib & XPP_BLOCK )
   {
      pItem->m_conItem  = _conEvalCon(m_pType->m_con);
      pItem->m_bSealed = TRUE;        
      return TRUE;         
   }      
   if( m_dwAttrib & XPP_ARRAY )
   {
      pItem->m_conItem = _conNewArray(1,0);
      return TRUE;
   }
   if( m_pType->m_dwAttrib & XPP_OBJECT )
   {
      pItem->m_conItem  = _conMCallCon(m_pType->m_con,"new");
      pItem->m_bSealed = TRUE;        
      return TRUE;      
   }
   pItem->m_conItem  = _conNew(NULLCONTAINER);
   pItem->m_bSealed = FALSE;
   return TRUE;         
}

// -----------------------------------------------------------------------------------------------------------------
ndtg_item_t::ndtg_item_t( void )
{
   m_pNext   = 0;
   m_pPrev   = 0;
   m_pProp   = 0;
   m_conItem = 0;
   m_bSealed = 0;  
   m_nDepth  = 0;     
   m_bDynamicProp = 0;   
}
// -----------------------------------------------------------------------------------------------------------------
ndtg_item_t::~ndtg_item_t( void )
{
   if( m_pNext ){ m_pNext->m_pPrev = m_pPrev; }
   if( m_pPrev ){ m_pPrev->m_pNext = m_pNext; }
   if( m_conItem ){_conRelease( m_conItem ); m_conItem = 0; }   
   if( m_bDynamicProp && m_pProp ){ delete m_pProp; m_pProp = 0;}
  if( m_pAttrib ){ delete m_pAttrib;  m_pAttrib = 0;} // deleted in cascade   
}
// -----------------------------------------------------------------------------------------------------------------
void ndtg_item_t::attrib_add(LPSTR pKey , LPSTR pVal )
{
   attrib_t* p = new attrib_t(pKey,pVal);
   p->m_pNext = m_pAttrib;
   m_pAttrib = p;
}
// -----------------------------------------------------------------------------------------------------------------
void ndtg_item_t::eval_attrib(void)
{
   ContainerHandle conb = m_pProp->m_pType->m_conb_on_attrib;
   if( conb && m_pAttrib && m_conItem )
   {
      ContainerHandle conr  = _conNew( NULLCONTAINER );
      ContainerHandle con_k = NULLCONTAINER;
      ContainerHandle con_v = NULLCONTAINER;      
      ContainerHandle con_h = NULLCONTAINER;
      attrib_t* p;
      for(p = m_pAttrib; p ; p = p->m_pNext )
      {
         con_k = _conPutC(con_k , p->m_pKey );
         con_v = _conPutC(con_v , p->m_pVal );
         con_h = _conPutNL(con_h, p->m_dwKeyCrc32 );
         _conEvalB(conr,conb,4,m_conItem,con_k,con_v,con_h);
      }
      if( conr  ){ _conRelease( conr  );}
      if( con_k ){ _conRelease( con_k );}    
      if( con_v ){ _conRelease( con_v );}
      if( con_h ){ _conRelease( con_h );}    
      delete m_pAttrib; m_pAttrib = 0; // deleted in cascade
   }
}
// -----------------------------------------------------------------------------------------------------------------      
void ndtg_item_t::PutVal(LPSTR pStr)
{
   if( !pStr ) return;
   if( m_bSealed ) return;   
   switch( m_pProp->m_pType->m_dwAttrib )
   {
      case 0x03010000 : // boolean 
      {
         m_conItem = _conPutL(m_conItem, (BOOL)( _xstrcmpi_09az( pStr , "true") == 0 )||( _xstrcmpi_09az( pStr , "yes") == 0 ) ); 
         return;
      }
      case 0x03040000 : // int // long          
      case 0x03020000 : // short         
      {
         m_conItem = _conPutNL(m_conItem, (LONG) atoi(pStr));       
         return;
      }
      case 0x03180000 : // double  
      {
         m_conItem = _conPutND(m_conItem, atof(pStr));             
         return;
      }
      case 0x03880000 : // anyType       
      case 0x03200000 : // string  
      {
         m_conItem = _conPutC(m_conItem,pStr);
         return;
      }
      case 0x03810000 : // datetime
      {
         m_conItem = _conPutNewObj(m_conItem,"FILETIME64",0);
         _conMCallVoid(m_conItem,"SetTimeStamp",pStr);
         return;
      }
   }
}
// -----------------------------------------------------------------------------------------------------------------
ndtg_stack_t::ndtg_stack_t( ndtg_typelist_t* pTypeList ,ndtg_type_t* pResultType, DWORD nResultFlags)
{
   m_pFirst        = 0;
   m_pLast         = 0;
   m_pTypeList     = pTypeList;
   m_conResult     = NULLCONTAINER;   
   m_pResultProp   = new ndtg_prop_t("result",pResultType,0,nResultFlags);
}
// -----------------------------------------------------------------------------------------------------------------
ndtg_stack_t::~ndtg_stack_t()
{
   while( m_pFirst ){ pop_step(); }   
   if( m_conResult ){ _conRelease( m_conResult ); m_conResult = 0; } 
   if( m_pResultProp ) delete m_pResultProp;
   m_pResultProp = 0;   
}
// -----------------------------------------------------------------------------------------------------------------
ndtg_item_t* ndtg_stack_t::pop(void)
{
   ndtg_item_t* p = m_pLast;
   if( p )
   {
      m_pLast = p->m_pPrev;
      if( m_pLast ) { m_pLast->m_pNext = 0;}
      else { m_pFirst = 0; }
      p->m_pNext = 0;
      p->m_pPrev = 0;      
   }
   return p;
}
// -----------------------------------------------------------------------------------------------------------------
void ndtg_stack_t::push( ndtg_item_t* pItem )
{
   pItem->m_pNext = 0;
   pItem->m_pPrev = m_pLast;   
   if( m_pLast ){ m_pLast->m_pNext = pItem;}
   else { m_pFirst = pItem; }
   m_pLast = pItem;   
}
// -----------------------------------------------------------------------------------------------------------------
void ndtg_stack_t::depth_control(LONG nDepth)
{
   while( m_pLast && (m_pLast->m_nDepth >= nDepth) ){ pop_step(); }
}
// -----------------------------------------------------------------------------------------------------------------
void ndtg_stack_t::pop_step(void)
{
   ndtg_item_t* pItem = pop();
   if(pItem)
   {
      pItem->eval_attrib();
      if( m_pLast ) 
      {
         if( m_pLast->m_pProp->m_pType->m_conb_child_pop )
         {
            ContainerHandle conr = _conNew( NULLCONTAINER);
            ContainerHandle conk = _conPutC( NULLCONTAINER,pItem->m_pProp->m_pPropName );
            ContainerHandle conh = _conPutNL(NULLCONTAINER, (LONG) pItem->m_pProp->m_dwPropCrc );
            _conEvalB( conr , m_pLast->m_pProp->m_pType->m_conb_child_pop, 3,conk,pItem->m_conItem,conh);
            _conReleaseM(conr,conk,conh,0);
         }
         else if( m_pLast->m_pProp->m_dwAttrib & XPP_ARRAY )
         {
            m_pLast->m_conItem = _conaadd( m_pLast->m_conItem , pItem->m_conItem );
         }
         else if( m_pLast->m_pProp->m_dwAttrib & XPP_OBJECT )
         {
            char sz[512];
            ZeroMemory(sz,512);
            if( m_pTypeList->m_pPropPrefix )
            {
               _snprintf_s(sz,512,_TRUNCATE,"%s%s",m_pTypeList->m_pPropPrefix,pItem->m_pProp->m_pPropName);
            }
            else
            {
               _snprintf_s(sz,512,_TRUNCATE,"%s",pItem->m_pProp->m_pPropName);
            }            
            _conSetMember( m_pLast->m_conItem , sz,pItem->m_conItem );
         }
      }
      else 
      {
         m_conResult = _conPut(m_conResult,pItem->m_conItem);
      }
      delete pItem;
   }
}
// -----------------------------------------------------------------------------------------------------------------
BOOL ndtg_stack_t::step( LPSTR pKey , LONG nDepth)
{
   depth_control(nDepth);
   ndtg_item_t*  pi = new ndtg_item_t();
   pi->m_nDepth = nDepth;   
   if( m_pLast )   
   {
      if( !m_pLast->m_pProp->SetChildStackItem(pKey,pi) ){ delete pi; return FALSE;}
   }
   else m_pResultProp->SetStackItem(pi);
   push(pi);
   return TRUE;
}
// -----------------------------------------------------------------------------------------------------------------
void ndtg_stack_t::seal(void)
{
   if( m_pLast )   m_pLast->m_bSealed = TRUE;
}
// -----------------------------------------------------------------------------------------------------------------
BOOL ndtg_stack_t::unsealed(void){ return (BOOL) ( m_pLast && !(m_pLast->m_bSealed) );}
// -----------------------------------------------------------------------------------------------------------------
void ndtg_stack_t::putval(LPSTR pVal)
{
   if( m_pLast && !(m_pLast->m_bSealed))
   {
      m_pLast->PutVal(pVal);
   }
}
// -----------------------------------------------------------------------------------------------------------------
ContainerHandle ndtg_stack_t::GetResult( ContainerHandle conr )
{
   while( m_pLast ){ pop_step(); }
   conr = _conPut(conr, m_conResult );
   return conr;
}
// -----------------------------------------------------------------------------------------------------------------
void ndtg_stack_t::attrib(LPSTR pAttrib, LPSTR pVal)
{
   if( m_pLast && pAttrib && pVal ) m_pLast->attrib_add(pAttrib,pVal);
}
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ndtg_create_typedef_table
            | syntax_: `ndtg_create_typedef_table( [@pTable] [, cPropertyPrefix] )`
            | category: xml/node-trigger
            | _kw_: ndtg_create_typedef_table, Function
   }}*/
/*{{|desc: Creates an empty type-definition table for typed NDTG stacks and returns its handle. The types
      and their properties are then described with ndtg_add_type() and ndtg_add_prop().
    | params:
    - `pTable` Numeric pointer - Optional variable; when passed by reference it also receives the new
      table handle. A handle already stored there is overwritten, not destroyed.
    - `cPropertyPrefix` Character - Optional prefix added to the property name when a child value is
      assigned to an object member, so with prefix "_" the property "name" is assigned to member "_name".

    Returns Numeric pointer - Handle of the new table. Release it with ndtg_destroy_typedef_table().

    |seealso: See also: {{ilink: <function ndtg_add_type> ndtg_add_type}}, {{ilink: <function ndtg_stack_begin> ndtg_stack_begin}}, {{ilink: <function ndtg_destroy_typedef_table> ndtg_destroy_typedef_table}} }}*/
_XPP_REG_FUN_( NDTG_CREATE_TYPEDEF_TABLE )
{
   TXppParamList xpp(pl);
   ndtg_typelist_t* p =  new ndtg_typelist_t( xpp[2]->str() );
   xpp[0]->PutDWord((DWORD) p );
   xpp[1]->PutDWord((DWORD) p );   
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ndtg_destroy_typedef_table
            | syntax_: `ndtg_destroy_typedef_table( @pTable )`
            | category: xml/node-trigger
            | _kw_: ndtg_destroy_typedef_table, Function
   }}*/
/*{{|desc: Destroys a type-definition table with every type and property definition it holds. When pTable is
      passed by reference the variable is set to 0.
    | params:
    - `pTable` Numeric pointer - Table handle returned by ndtg_create_typedef_table(); 0 does nothing.

    Returns NIL.

    |note: Stacks created from the table keep a pointer to it: destroy the table only after every typed
      stack using it has been closed with ndtg_stack_end().

    |seealso: See also: {{ilink: <function ndtg_create_typedef_table> ndtg_create_typedef_table}} }}*/
_XPP_REG_FUN_( NDTG_DESTROY_TYPEDEF_TABLE )
{
   TXppParamList xpp(pl);
   ndtg_typelist_t* p =  (ndtg_typelist_t*) xpp[1]->GetLong();
   if( p ){ delete p; }
   xpp[1]->PutDWord(0);   
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ndtg_add_type
            | syntax_: `ndtg_add_type( pTable, cTypeName [, uItem] [, nAttrib] )`
            | category: xml/node-trigger
            | _kw_: ndtg_add_type, Function
   }}*/
/*{{|desc: Adds the type cTypeName to a type-definition table and returns its handle. When the type already
      exists it is updated instead: uItem replaces the stored item and the nAttrib bits are added to the
      existing attributes.
    | params:
    - `pTable` Numeric pointer - Table handle returned by ndtg_create_typedef_table().
    - `cTypeName` Character - Type name. NDTG matches type names case sensitively.
    - `uItem` Object/CodeBlock - Item used to build node values: with XPP_OBJECT in nAttrib the class
      object whose :new() creates the value, with XPP_BLOCK a codeblock whose Eval() result is the value.
      With other attributes it is only stored. Logical, Date and NIL values are not stored.
    - `nAttrib` Numeric - Type attributes. XPP_OBJECT (0x80) creates an object node value from uItem and
      XPP_BLOCK (0x40) evaluates uItem; both seal the node, so its own text is ignored. For text nodes the
      whole value must be one conversion code, applied by ndtg_stack_putval(): 0x03010000 Logical ("true" or
      "yes" is .T.), 0x03020000 or 0x03040000 integer Numeric, 0x03180000 decimal Numeric, 0x03200000 or
      0x03880000 Character, 0x03810000 FILETIME64 object loaded with :SetTimeStamp( cText ). With any other
      value the node text is ignored.

    Returns Numeric pointer - Type handle for ndtg_add_prop() and ndtg_set_attrib_cb(), or 0 when cTypeName
      is missing. NIL when pTable is 0.

    |seealso: See also: {{ilink: <function ndtg_add_prop> ndtg_add_prop}}, {{ilink: <function ndtg_get_type> ndtg_get_type}} }}*/
_XPP_REG_FUN_( NDTG_ADD_TYPE )
{
   TXppParamList xpp(pl);
   ndtg_typelist_t* pTable =  (ndtg_typelist_t*) xpp[1]->GetLong();
   if( pTable )
   {
      xpp[0]->PutDWord((DWORD) pTable->Add( xpp[2]->LockStrEx(),xpp[3]->GetT(0xE6),xpp[4]->GetDWord()));            
   }
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ndtg_get_type
            | syntax_: `ndtg_get_type( pTable, cTypeName )`
            | category: xml/node-trigger
            | _kw_: ndtg_get_type, Function
   }}*/
/*{{|desc: Returns the handle of a type already defined in a type-definition table, without adding anything.
    | params:
    - `pTable` Numeric pointer - Table handle returned by ndtg_create_typedef_table().
    - `cTypeName` Character - Type name, matched case sensitively.

    Returns Numeric pointer - Type handle, or 0 when the name is not defined or pTable is 0.

    |seealso: See also: {{ilink: <function ndtg_add_type> ndtg_add_type}} }}*/
_XPP_REG_FUN_( NDTG_GET_TYPE )
{
   TXppParamList xpp(pl);
   ndtg_typelist_t* pTable =  (ndtg_typelist_t*) xpp[1]->GetLong();   
   if( pTable ){ xpp[0]->PutDWord( (DWORD) pTable->_find_(xpp[2]->LockStrEx()));}
   else xpp[0]->PutDWord(0);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ndtg_add_prop
            | syntax_: `ndtg_add_prop( pType, cPropName, cTypeName [, uItem] [, nAttrib] )`
            | category: xml/node-trigger
            | _kw_: ndtg_add_prop, Function
   }}*/
/*{{|desc: Adds the property cPropName to a type and returns the property handle. A property describes a
      child node of the nodes of type pType: the child value is built as cTypeName. When cTypeName is not yet
      in the table an empty type is added for it, to be completed later with ndtg_add_type(). When the
      property already exists it is updated: uItem replaces the stored item and the nAttrib bits are added.
    | params:
    - `pType` Numeric pointer - Type handle from ndtg_add_type() or ndtg_get_type().
    - `cPropName` Character - Property name, matched case sensitively against child node names.
    - `cTypeName` Character - Name of the type of the property value.
    - `uItem` AnyType - Reserved; stored with the property but not used by the current version.
    - `nAttrib` Numeric - Property attributes. XPP_ARRAY (0x20): the property value is an array and every
      child node, whatever its name, is appended to it as a cTypeName value. XPP_OBJECT (0x80): child nodes
      are resolved as properties of cTypeName and each child value is assigned to the member of the node
      value named after the property (plus the table prefix); children whose name matches no property are not
      captured. When both bits are present XPP_ARRAY wins.

    Returns Numeric pointer - Property handle, or 0 when cPropName or cTypeName is missing. NIL when pType
      is 0.

    |seealso: See also: {{ilink: <function ndtg_add_type> ndtg_add_type}} }}*/
_XPP_REG_FUN_( NDTG_ADD_PROP)
{
   TXppParamList xpp(pl);
   ndtg_type_t* pt = reinterpret_cast<ndtg_type_t*>(xpp[1]->GetLong());
   if( pt )
   {
      xpp[0]->PutDWord((DWORD) pt->AddProp(xpp[2]->str(),xpp[3]->str(),xpp[4]->GetT(0xE6),xpp[5]->GetDWord()) );            
   }
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ndtg_set_attrib_cb
            | syntax_: `ndtg_set_attrib_cb( pType, bAttrib )`
            | category: xml/node-trigger
            | _kw_: ndtg_set_attrib_cb, Function
   }}*/
/*{{|desc: Installs the attribute callback of a type, replacing any previous one. When a node of the type is
      closed in a typed stack, the codeblock is evaluated once per collected attribute as
      Eval( bAttrib, xValue, cKey, cValue, nKeyCrc32 ), where xValue is the node value being completed and
      nKeyCrc32 is the CRC32 of the lowercased attribute name. Without a callback the attributes of the
      node are discarded.
    | params:
    - `pType` Numeric pointer - Type handle from ndtg_add_type() or ndtg_get_type().
    - `bAttrib` CodeBlock - Attribute callback; any other value only removes the current one.

    Returns NIL.

    |note: Attributes are delivered when the node is closed, not when they are added, and in reverse order
      of the ndtg_stack_attrib() calls.

    |seealso: See also: {{ilink: <function ndtg_stack_attrib> ndtg_stack_attrib}} }}*/
_XPP_REG_FUN_( NDTG_SET_ATTRIB_CB)
{
   TXppParamList xpp(pl);
   ndtg_type_t* pt = reinterpret_cast<ndtg_type_t*>(xpp[1]->GetLong());
   if( pt )
   {
      if( pt->m_conb_on_attrib ){ _conRelease( pt->m_conb_on_attrib);pt->m_conb_on_attrib = NULLCONTAINER;}
      if( xpp[2]->CheckType(XPP_BLOCK) ){ pt->m_conb_on_attrib = _conNew( xpp[2]->con()); }
   }
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ndtg_stack_begin
            | syntax_: `ndtg_stack_begin( [pTable, cResultType [, nResultFlags]] )`
            | category: xml/node-trigger
            | _kw_: ndtg_stack_begin, Function
   }}*/
/*{{|desc: Creates a node trigger stack and returns its handle. With parameters the stack is typed: node
      values are built as described by the pTable definitions, and the value of the first node, built as
      cResultType, becomes the final result. Without parameters a generic xstack is created instead, which
      rebuilds a Xbase++ value serialized in the OT4XB XML format.
    | params:
    - `pTable` Numeric pointer - Type-definition table handle. 0 generates a runtime error.
    - `cResultType` Character - Name of an existing type in pTable describing the result value. A
      runtime error is generated when the type is not defined.
    - `nResultFlags` Numeric - Property attributes applied to the result, with the same meaning as
      nAttrib in ndtg_add_prop(): XPP_OBJECT (0x80) resolves the children of the first node as properties of
      cResultType, XPP_ARRAY (0x20) collects them into an array of cResultType values.

    Returns Numeric pointer - Stack handle. Release it with ndtg_stack_end(), which also returns the
      result.

    |note: In typed mode the name of the first node is not checked; the result type is fixed by cResultType.

    |seealso: See also: {{ilink: <function ndtg_stack_step> ndtg_stack_step}}, {{ilink: <function ndtg_stack_end> ndtg_stack_end}}, {{ilink: <function ndtg_create_typedef_table> ndtg_create_typedef_table}} }}*/
_XPP_REG_FUN_( NDTG_STACK_BEGIN    )
{
   TXppParamList xpp(pl);
   if( xpp.PCount() > 0 )
   {
      ndtg_typelist_t* ptl = reinterpret_cast<ndtg_typelist_t*>(xpp[1]->GetDWord());
      xpp_assert( ptl , -1 , "Invalid param: 1" );   
      ndtg_type_t* prt     = ptl->_find_(xpp[2]->LockStr());
      xpp_assert( prt , -1, "Invalid param: 2");   
      xpp[0]->PutDWord( (DWORD) new ndtg_t( new ndtg_stack_t(ptl,prt,xpp[3]->GetDWord()) ) );
   }
   else
   {
      xpp[0]->PutDWord( (DWORD) new ndtg_t( new ndtg_xstack_t() ) );   
   }
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ndtg_stack_step
            | syntax_: `ndtg_stack_step( pStack, nDepth, cNodeName )`
            | category: xml/node-trigger
            | _kw_: ndtg_stack_step, Function
   }}*/
/*{{|desc: Opens a new node at nesting level nDepth. Nodes still open at the same or a deeper level are
      closed first and their completed values delivered to their parents, so there is no explicit close
      call: a sibling or a shallower node closes the previous branch, and ndtg_stack_end() closes whatever
      is left.
    | params:
    - `pStack` Numeric pointer - Stack handle from ndtg_stack_begin(). 0 generates a runtime error.
    - `nDepth` Numeric - Nesting level of the node. A child must use a deeper level than its parent;
      siblings repeat the level. Typically the XML nesting depth.
    - `cNodeName` Character - Node name. A runtime error is generated when it is missing.

    Returns NIL.

    |note: In a typed stack the node name selects the property of the parent node type (case sensitively);
      when the parent expects an object and the name matches no property, the node is not captured.

    |seealso: See also: {{ilink: <function ndtg_stack_attrib> ndtg_stack_attrib}}, {{ilink: <function ndtg_stack_putval> ndtg_stack_putval}}, {{ilink: <function ndtg_stack_end> ndtg_stack_end}} }}*/
_XPP_REG_FUN_( NDTG_STACK_STEP     )
{
   TXppParamList xpp(pl);
   ndtg_t* ndtg = reinterpret_cast<ndtg_t*>(xpp[1]->GetDWord());
   xpp_assert( ndtg , -1 , "Invalid param: 1" );         
   switch( ndtg->m_q )
   {
      case ndtg_t::q_ndtg_stack_t :
      {
         ndtg_stack_t* ps = reinterpret_cast<ndtg_stack_t*>(ndtg->m_p);
         LPSTR pKey = xpp[3]->LockStr();
         xpp_assert( pKey , -1 , "Invalid param: 3" );         
         ps->step(pKey,xpp[2]->GetLong() );
         return;
      }
      case ndtg_t::q_ndtg_xstack_t :
      {
         ndtg_xstack_t* ps = reinterpret_cast<ndtg_xstack_t*>(ndtg->m_p);
         LPSTR pKey = xpp[3]->LockStr();
         xpp_assert( pKey , -1 , "Invalid param: 3" );         
         ps->step(pKey,xpp[2]->GetLong() );
         return;
      }      
   }
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ndtg_stack_seal
            | syntax_: `ndtg_stack_seal( pStack )`
            | category: xml/node-trigger
            | _kw_: ndtg_stack_seal, Function
   }}*/
/*{{|desc: Seals the node currently open: later ndtg_stack_putval() calls are ignored for it and
      ndtg_stack_unsealed() returns .F. for it. Child nodes opened afterwards are not affected. Does nothing
      when no node is open.
    | params:
    - `pStack` Numeric pointer - Stack handle from ndtg_stack_begin(). 0 generates a runtime error.

    Returns NIL.

    |seealso: See also: {{ilink: <function ndtg_stack_unsealed> ndtg_stack_unsealed}}, {{ilink: <function ndtg_stack_putval> ndtg_stack_putval}} }}*/
_XPP_REG_FUN_( NDTG_STACK_SEAL     )
{
   TXppParamList xpp(pl);
   ndtg_t* ndtg = reinterpret_cast<ndtg_t*>(xpp[1]->GetDWord());
   xpp_assert( ndtg , -1 , "Invalid param: 1" );         
   switch( ndtg->m_q )
   {
      case ndtg_t::q_ndtg_stack_t :
      {
         ndtg_stack_t* ps = reinterpret_cast<ndtg_stack_t*>(ndtg->m_p);
         ps->seal();
         return;
      }
      case ndtg_t::q_ndtg_xstack_t :
      {
         ndtg_xstack_t* ps = reinterpret_cast<ndtg_xstack_t*>(ndtg->m_p);
         ps->seal();
         return;
      }      
   }
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ndtg_stack_unsealed
            | syntax_: `ndtg_stack_unsealed( pStack )`
            | category: xml/node-trigger
            | _kw_: ndtg_stack_unsealed, Function
   }}*/
/*{{|desc: Tells whether the node currently open can still receive its text with ndtg_stack_putval().
    | params:
    - `pStack` Numeric pointer - Stack handle from ndtg_stack_begin(). 0 generates a runtime error.

    Returns Logical - .T. while there is an open node that is not sealed; .F. when the node is sealed or no
      node is open.

    |seealso: See also: {{ilink: <function ndtg_stack_putval> ndtg_stack_putval}}, {{ilink: <function ndtg_stack_seal> ndtg_stack_seal}} }}*/
_XPP_REG_FUN_( NDTG_STACK_UNSEALED )
{
   TXppParamList xpp(pl);
   ndtg_t* ndtg = reinterpret_cast<ndtg_t*>(xpp[1]->GetDWord());
   xpp_assert( ndtg , -1 , "Invalid param: 1" );         
   switch( ndtg->m_q )
   {
      case ndtg_t::q_ndtg_stack_t :
      {
         ndtg_stack_t* ps = reinterpret_cast<ndtg_stack_t*>(ndtg->m_p);
         xpp[0]->PutBool( ps->unsealed() );                           
         return;
      }
      case ndtg_t::q_ndtg_xstack_t :
      {
         ndtg_xstack_t* ps = reinterpret_cast<ndtg_xstack_t*>(ndtg->m_p);
         xpp[0]->PutBool( ps->unsealed() );                                    
         return;
      }            
   }
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ndtg_stack_putval
            | syntax_: `ndtg_stack_putval( pStack, cValue )`
            | category: xml/node-trigger
            | _kw_: ndtg_stack_putval, Function
   }}*/
/*{{|desc: Stores the text content of the node currently open. In a typed stack the text is converted as
      selected by the conversion code in the type's nAttrib (see ndtg_add_type()); nodes whose type has no
      conversion code ignore their text. In a generic xstack the text is decoded following the OT4XB
      serialization rules for the node.
    | params:
    - `pStack` Numeric pointer - Stack handle from ndtg_stack_begin(). 0 generates a runtime error.
    - `cValue` Character - Node text. NIL is ignored.

    Returns NIL.

    |note: Ignored when the node is sealed or no node is open. Each call replaces the value stored by a
      previous one: text arriving in chunks must be concatenated by the caller before the call.

    |seealso: See also: {{ilink: <function ndtg_stack_unsealed> ndtg_stack_unsealed}}, {{ilink: <function ndtg_stack_seal> ndtg_stack_seal}} }}*/
_XPP_REG_FUN_( NDTG_STACK_PUTVAL   )
{
   TXppParamList xpp(pl);
   ndtg_t* ndtg = reinterpret_cast<ndtg_t*>(xpp[1]->GetDWord());
   xpp_assert( ndtg , -1 , "Invalid param: 1" );         
   switch( ndtg->m_q )
   {
      case ndtg_t::q_ndtg_stack_t :
      {
         ndtg_stack_t* ps = reinterpret_cast<ndtg_stack_t*>(ndtg->m_p);
         LPSTR pval = xpp[2]->LockStr();
         ps->putval( pval );         
         return;
      }
      case ndtg_t::q_ndtg_xstack_t :
      {
         ndtg_xstack_t* ps = reinterpret_cast<ndtg_xstack_t*>(ndtg->m_p);
         ps->putval( xpp[2]->LockStr() );         
         return;
      }      
   }
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ndtg_stack_attrib
            | syntax_: `ndtg_stack_attrib( pStack, cName, cValue )`
            | category: xml/node-trigger
            | _kw_: ndtg_stack_attrib, Function
   }}*/
/*{{|desc: Adds one attribute to the node currently open. In a typed stack attributes are kept until the
      node is closed and then delivered to the attribute callback of the node type (see
      ndtg_set_attrib_cb()); without callback they are discarded. In a generic xstack the attributes carry
      the serialized description of the node value, consumed by ndtg_stack_attrib_seal().
    | params:
    - `pStack` Numeric pointer - Stack handle from ndtg_stack_begin(). 0 generates a runtime error.
    - `cName` Character - Attribute name.
    - `cValue` Character - Attribute value.

    Returns NIL.

    |note: The call is ignored when no node is open or when cName or cValue is not a Character value.

    |seealso: See also: {{ilink: <function ndtg_set_attrib_cb> ndtg_set_attrib_cb}}, {{ilink: <function ndtg_stack_attrib_seal> ndtg_stack_attrib_seal}} }}*/
_XPP_REG_FUN_( NDTG_STACK_ATTRIB )
{
   TXppParamList xpp(pl);
   ndtg_t* ndtg = reinterpret_cast<ndtg_t*>(xpp[1]->GetDWord());
   xpp_assert( ndtg , -1 , "Invalid param: 1" );         
   switch( ndtg->m_q )
   {
      case ndtg_t::q_ndtg_stack_t :
      {
         ndtg_stack_t* ps = reinterpret_cast<ndtg_stack_t*>(ndtg->m_p);
         LPSTR pkey = xpp[2]->LockStr();         
         LPSTR pval = xpp[3]->LockStr();                  
         ps->attrib( pkey , pval );         
         return;
      }   
      case ndtg_t::q_ndtg_xstack_t :
      {
         ndtg_xstack_t* ps = reinterpret_cast<ndtg_xstack_t*>(ndtg->m_p);
         ps->attrib( xpp[2]->LockStr() , xpp[3]->LockStr() );
         return;
      }      
   }
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ndtg_stack_attrib_seal
            | syntax_: `ndtg_stack_attrib_seal( pStack )`
            | category: xml/node-trigger
            | _kw_: ndtg_stack_attrib_seal, Function
   }}*/
/*{{|desc: In a generic xstack, closes the attribute phase of the node currently open: the node value is
      created from the attributes collected so far. Call it once the start tag of a node is complete and
      before any child node is stepped, because array and object values must exist before child values are
      delivered into them. In a typed stack the call does nothing.
    | params:
    - `pStack` Numeric pointer - Stack handle from ndtg_stack_begin(). 0 generates a runtime error.

    Returns NIL.

    |note: The node is not sealed against text: nodes whose serialized content travels as node text still
      take it from ndtg_stack_putval().

    |seealso: See also: {{ilink: <function ndtg_stack_attrib> ndtg_stack_attrib}}, {{ilink: <function ndtg_stack_putval> ndtg_stack_putval}} }}*/
_XPP_REG_FUN_( NDTG_STACK_ATTRIB_SEAL )
{
   TXppParamList xpp(pl);
   ndtg_t* ndtg = reinterpret_cast<ndtg_t*>(xpp[1]->GetDWord());
   xpp_assert( ndtg , -1 , "Invalid param: 1" );         
   switch( ndtg->m_q )
   {
      case ndtg_t::q_ndtg_xstack_t :
      {
         ndtg_xstack_t* ps = reinterpret_cast<ndtg_xstack_t*>(ndtg->m_p);
         ps->attrib_seal();
         return;
      }      
   }
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ndtg_stack_end
            | syntax_: `ndtg_stack_end( @pStack )`
            | category: xml/node-trigger
            | _kw_: ndtg_stack_end, Function
   }}*/
/*{{|desc: Closes every node still open, destroys the stack and returns the completed result value. When
      pStack is passed by reference the variable is set to 0.
    | params:
    - `pStack` Numeric pointer - Stack handle from ndtg_stack_begin(). 0 generates a runtime error.

    Returns AnyType - The completed value: for a typed stack the value of the first node, built as the
      cResultType given to ndtg_stack_begin(); for a generic xstack the rebuilt Xbase++ value. NIL when no
      node was ever opened.

    |note: The handle is always destroyed by the call. The type-definition table of a typed stack is not
      destroyed and can be reused.

    |seealso: See also: {{ilink: <function ndtg_stack_begin> ndtg_stack_begin}}, {{ilink: <function ndtg_destroy_typedef_table> ndtg_destroy_typedef_table}} }}*/
_XPP_REG_FUN_( NDTG_STACK_END )
{
   TXppParamList xpp(pl);
   ndtg_t* ndtg = reinterpret_cast<ndtg_t*>(xpp[1]->GetDWord());
   xpp_assert( ndtg , -1 , "Invalid param: 1" );         
   switch( ndtg->m_q )
   {
      case ndtg_t::q_ndtg_stack_t :
      {
         ndtg_stack_t* ps = reinterpret_cast<ndtg_stack_t*>(ndtg->m_p);
         ps->GetResult( xpp[0]->con() );         
         break;
      }
      case ndtg_t::q_ndtg_xstack_t :
      {
         ndtg_xstack_t* ps = reinterpret_cast<ndtg_xstack_t*>(ndtg->m_p);
         ps->GetResult( xpp[0]->con() );         
         break;
      }      
   }
   delete ndtg;
   xpp[1]->PutLong(0);   
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------



