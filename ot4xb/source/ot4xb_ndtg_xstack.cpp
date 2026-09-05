//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
//------------------------------------------------------------
#include <ot4xb_api.h>
#include <stdlib.h>
#include <stdio.h>
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
using namespace ndtg_ns;
// -----------------------------------------------------------------------------------------------------------------
ndtg_xstack_t::recursion_t::recursion_t(DWORD id, ContainerHandle con)
{
   m_pNext = 0;
   m_id    = id;
   m_con   = _conNew(con);
}
// -----------------------------------------------------------------------------------------------------------------
ndtg_xstack_t::recursion_t::~recursion_t(void)
{
   recursion_t* pNext = m_pNext;
   while( pNext )
   {
      recursion_t* p = pNext->m_pNext;
      pNext->m_pNext = 0;
      delete pNext;
      pNext = p;
   }
   m_pNext = 0;
   if( m_con ){ _conRelease( m_con ); m_con = 0; }
}
// -----------------------------------------------------------------------------------------------------------------
ndtg_xstack_t::item_t::item_t(LPSTR pName , LONG nDepth)
{
   m_pNext   = 0;
   m_pPrev   = 0;
   m_pAttrib = 0;
   m_con     = NULLCONTAINER;
   m_bSealed = 0;
   m_nDepth  = nDepth;
   m_pType   = (xtype_t) dwCrc32Lower(0,(LPBYTE) pName,_xstrlen(pName));
}
// -----------------------------------------------------------------------------------------------------------------
ndtg_xstack_t::item_t::~item_t(void)
{
  if( m_pAttrib ){ delete m_pAttrib;  m_pAttrib = 0;} // deleted in cascade
  if( m_con ) { _conRelease( m_con) ; m_con = 0; }
  // warning: destructor don't detach the item from the link list
}
// -----------------------------------------------------------------------------------------------------------------
void ndtg_xstack_t::item_t::attrib_add(LPSTR pKey , LPSTR pVal )
{
   attrib_t* p = new attrib_t(pKey,pVal);
   p->m_pNext = m_pAttrib;
   m_pAttrib = p;

}
// -----------------------------------------------------------------------------------------------------------------
LPSTR ndtg_xstack_t::item_t::attrib_get(LPSTR pKey)
{
   attrib_t* p;
   DWORD dw;
   if( !pKey ){ return 0;}
   dw = dwCrc32Lower(0,(LPBYTE) pKey,_xstrlen(pKey));
   for( p = m_pAttrib; p ; p = p->m_pNext )
   {
      if( p->m_dwKeyCrc32 == dw )
      {
         if( _xstrcmpi(pKey,p->m_pKey) == 0 )
         {
            return p->m_pVal;
         }
      }
   }
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
LONG ndtg_xstack_t::item_t::attrib_get_int32(LPSTR pKey)
{
   LPSTR p = attrib_get(pKey);
   if( p ) return atol(p);
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
double ndtg_xstack_t::item_t::attrib_get_double(LPSTR pKey)
{
   LPSTR p = attrib_get(pKey);
   if( p ) return atof(p);
   return 0.00F;
}
// -----------------------------------------------------------------------------------------------------------------
LPSTR ndtg_xstack_t::item_t::get_last_path_component_as_LPSTR(void)
{
   LPSTR p  = attrib_get("path");
   if( p )
   {
      LPSTR pp = 0;
      for( ; *p ; p++)
      {
         if( *p == '.' ) pp = _mk_ptr_(LPSTR,p,1);
      }
      return pp;
   }
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
LONG  ndtg_xstack_t::item_t::get_last_path_component_as_int32(void)
{
   LPSTR p = get_last_path_component_as_LPSTR();
   if( p ) return atol(p);
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
void ndtg_xstack_t::item_t::putval(LPSTR pVal)
{
   LPSTR pEncode;
   if( !pVal ) return;
   if( m_bSealed ) return;
   pEncode = attrib_get("enq");
   if( !pEncode ) return;
   if( _xstrcmp( pEncode , "ot4xb" ) ) return;
   switch( m_pType )
   {
      case XTYPE_CODEBLOCK:
      {
         UINT cb = 0;
         LPSTR p = ot4xbenc2bin(pVal,INFINITE,&cb);
         if(p)
         {
            if(m_con){ _conRelease(m_con); m_con = 0; }         
            m_con = _conCallConR("var2bin",_conPutCL(0,p,cb));
            _xfree(p);
         }
         return;
      }
      case XTYPE_CHARACTER: ;
      case XTYPE_MEMO:
      {
         UINT  cb = 0;
         LPSTR p  = ot4xbenc2bin(pVal,INFINITE,&cb);
         if(p)
         {
            TXbCPItem xi(m_con,TRUE);
            xi.resize(cb);
            _bcopy((LPBYTE) xi.LockStrEx(1),(LPBYTE) p, cb );
            xi.UnLockStrEx();
            m_con = xi.detach();
            _xfree(p);
         }
         return;
      }
   }
}
// -----------------------------------------------------------------------------------------------------------------
void ndtg_xstack_t::item_t::attrib_seal(ndtg_xstack_t* pStack )
{
   if( (!m_bSealed) && ( m_con == NULLCONTAINER ) )
   {
      switch( m_pType )
      {
         case XTYPE_CODEBLOCK:
         {
            return;
         }
         case XTYPE_CHARACTER:
         {
            TXbCPItem xi(m_con,TRUE);
            xi.PutEmptyData(XPP_CHARACTER);
            m_con = xi.detach();
            return;
         }
         case XTYPE_MEMO:
         {
            TXbCPItem xi(m_con,TRUE);
            xi.PutEmptyData(_xpp_MEMO);
            m_con = xi.detach();
            return;
         }
         case XTYPE_DOUBLE:
         {
            m_con = _conPutND(m_con,attrib_get_double("val"));
            return;
         }
         case XTYPE_INT32:
         {
            m_con = _conPutNL(m_con,attrib_get_int32("val"));
            return;
         }
         case XTYPE_DATE:
         {
            m_con = _conPutDS(m_con,attrib_get("dtos"));
            return;
         }
         case XTYPE_LOGICAL:
         {
            m_con = _conPutL(m_con,(BOOL) attrib_get_int32("val"));
            return;
         }
         case XTYPE_NIL:
         {
            m_con = _conPut(m_con,NULLCONTAINER);
            return;
         }
         case XTYPE_FILETIME64:
         {

            m_con = _conNewObj("FILETIME64",NULLCONTAINER);
            _conMCallVoid(m_con,"SetHexTs",attrib_get("hexts"));
            return;
         }
         case XTYPE_ARRAY:
         {
            m_con = _conNewArray(1,(ULONG) attrib_get_int32("len"));
            pStack->recursion_add((DWORD)  attrib_get_int32("rcid"),m_con);
            return;
         }
         case XTYPE_OBJECT:
         {
            LONG  nObjType = attrib_get_int32("xppobjtype");
            LPSTR pClsName = attrib_get("classname");
            if( nObjType == 1 ){ m_con = _conNewObj(pClsName,NULLCONTAINER); }
            else { m_con = _conClsObjNew(pClsName);}
            pStack->recursion_add((DWORD)  attrib_get_int32("rcid"),m_con);
            return;
         }
         case XTYPE_RECURSION:
         {
            m_con = _conPut(m_con,pStack->recursion_get(attrib_get_int32("value")) );
            return;
         }
      }
   }
}
// -----------------------------------------------------------------------------------------------------------------
void ndtg_xstack_t::item_t::seal(void ){ m_bSealed = TRUE; }
// -----------------------------------------------------------------------------------------------------------------
ndtg_xstack_t::ndtg_xstack_t( void )
{
   m_pFirst     = 0;
   m_pLast      = 0;
   m_pRecursion = 0;
   m_conResult  = NULLCONTAINER;
}
// -----------------------------------------------------------------------------------------------------------------
ndtg_xstack_t::~ndtg_xstack_t( void )
{
   item_t* p = m_pFirst;
   while(p)
   {
      item_t* pp = p->m_pNext;
      delete p;
      p = pp;
   }
   m_pFirst    = 0;
   m_pLast     = 0;
   if( m_conResult ){ _conRelease( m_conResult ); }
   m_conResult = NULLCONTAINER;
   if( m_pRecursion ){ delete m_pRecursion; m_pRecursion = 0; }
}
// -----------------------------------------------------------------------------------------------------------------
void ndtg_xstack_t::push( ndtg_xstack_t::item_t* pItem )
{
   pItem->m_pNext = 0;
   pItem->m_pPrev = m_pLast;
   if( m_pLast ){ m_pLast->m_pNext = pItem;}
   else { m_pFirst = pItem; }
   m_pLast = pItem;
}
// -----------------------------------------------------------------------------------------------------------------
ndtg_xstack_t::item_t* ndtg_xstack_t::pop( void )
{
   item_t* p = m_pLast;
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
void ndtg_xstack_t::pop_step(void)
{
   item_t* pItem = pop();
   if(pItem)
   {

      if( m_pLast )
      {
         if( m_pLast->m_pType == item_t::XTYPE_ARRAY )
         {
            ULONG nIndex = (ULONG) pItem->get_last_path_component_as_int32();
            if( nIndex ){ _conArrayPut(m_pLast->m_con,pItem->m_con,nIndex,0); }
         }
         else if( m_pLast->m_pType == item_t::XTYPE_OBJECT )
         {
            LPSTR pMName = pItem->get_last_path_component_as_LPSTR();
            if( pMName ) _conSetMember(m_pLast->m_con,pMName,pItem->m_con);
         }
      }
      else
      {
         m_conResult = _conPut(m_conResult,pItem->m_con);
      }
      delete pItem;
   }
}

// -----------------------------------------------------------------------------------------------------------------
void ndtg_xstack_t::depth_control(LONG nDepth)
{
   while( m_pLast && (m_pLast->m_nDepth >= nDepth) )
   {
      pop_step();
   }
}
// -----------------------------------------------------------------------------------------------------------------
BOOL ndtg_xstack_t::step( LPSTR pKey , LONG nDepth)
{
   depth_control(nDepth);
   item_t*  pi = new item_t(pKey,nDepth);
   push(pi);
   return TRUE;
}
// -----------------------------------------------------------------------------------------------------------------
void ndtg_xstack_t::recursion_add(DWORD id, ContainerHandle con)
{
   if( id && con )
   {
      recursion_t* p = new recursion_t(id,con);
      p->m_pNext = m_pRecursion;
      m_pRecursion = p;
   }
}
// -----------------------------------------------------------------------------------------------------------------
ContainerHandle ndtg_xstack_t::recursion_get(DWORD id)
{
   recursion_t* p;
   for( p = m_pRecursion; p ; p = p->m_pNext )
   {
      if( p->m_id == id ){ return p->m_con; }
   }
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
void ndtg_xstack_t::attrib_seal(void)
{
   if( m_pLast ) m_pLast->attrib_seal(this);
}
// -----------------------------------------------------------------------------------------------------------------
void ndtg_xstack_t::seal(void)
{
   if( m_pLast ) m_pLast->seal();
}
// -----------------------------------------------------------------------------------------------------------------
BOOL ndtg_xstack_t::unsealed(void)
{
   return (BOOL) ( m_pLast && !(m_pLast->m_bSealed) );
}
// -----------------------------------------------------------------------------------------------------------------
void ndtg_xstack_t::putval(LPSTR pVal)
{
   if( m_pLast && !(m_pLast->m_bSealed))
   {
      m_pLast->putval(pVal);
   }
}
// -----------------------------------------------------------------------------------------------------------------
void ndtg_xstack_t::attrib(LPSTR pAttrib, LPSTR pVal)
{
   if( m_pLast && pAttrib && pVal ) m_pLast->attrib_add(pAttrib,pVal);
}
// -----------------------------------------------------------------------------------------------------------------
ContainerHandle ndtg_xstack_t::GetResult( ContainerHandle conr)
{
   while( m_pLast ){ pop_step(); }
   return _conPut(conr,m_conResult);
}


