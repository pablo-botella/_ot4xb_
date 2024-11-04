//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
static LPSTR _GenCbParamBlock_( ULONG nParams );
static LPSTR _GenCbParamBlockRef_( ULONG nParams );
static DWORD _x_name2crc( LPSTR pName);
//----------------------------------------------------------------------------------------------------------------------
static THashTable* pHookList = 0;
static CRITICAL_SECTION* _pcs_ = 0;
//----------------------------------------------------------------------------------------------------------------------
class gwst_hook_entry : public T_ot4xb_base
{
   public:
   LPSTR m_pClsName;
   DWORD m_dwCrc32;
   ContainerHandle* m_pcon;
   DWORD m_con_count;
   // --------------------------
   gwst_hook_entry( LPSTR pClsName , ContainerHandle con )
   {
      m_pClsName  = _xstrdup( pClsName );
      m_dwCrc32   = _x_name2crc(pClsName );
      m_con_count = 0;
      m_pcon      = (ContainerHandle* ) _xgrab( 4 * sizeof(ContainerHandle) );
      add( con );
   };
   // --------------------------   
   ~gwst_hook_entry( void )
   {
      if( m_pcon )
      {
         DWORD n;      
         for ( n=0; n < m_con_count ; n++)
         {
            if( m_pcon[n] ){ _conRelease( m_pcon[n] ); }
         }
         _xfree( (void*) m_pcon);
         m_pcon = 0;
      }
      m_con_count = 0;
      if( m_pClsName ){ _xfree( m_pClsName); m_pClsName = 0;}
   };
   // --------------------------
   static void __stdcall _OnDestroyItem_(void* p,DWORD)
   {
      if(p) delete reinterpret_cast<gwst_hook_entry*>(p);   
   };
   // --------------------------      
   void grow( DWORD newCount )
   {
      DWORD oldCap = (m_con_count | 3) + 1;   
      DWORD newCap = (newCount | 3) + 1;         
      if( newCap > oldCap )
      {
         DWORD n;
         ContainerHandle* old_pcon = m_pcon;
         m_pcon = (ContainerHandle* ) _xgrab( newCap * sizeof(ContainerHandle) );
         for ( n=0; n < m_con_count ; n++){ m_pcon[n] = old_pcon[n]; }
         _xfree( ( void*) old_pcon );
      }
   };
   // --------------------------   
   void add( ContainerHandle con )
   {
      if( _conCheckType(con, XPP_BLOCK | XPP_OBJECT ) )
      {
         grow( m_con_count + 1 );
         m_pcon[m_con_count] = _conNew( con );
         m_con_count++;
      }
   };
   // --------------------------   
   void EvalHookList( TXbClass* pc )
   {
      DWORD nn;
      ContainerHandle conXbCls = _conNewObjR( "TXbClass" , _conPutNL(0,(LONG) pc), 0);
      ContainerHandle conr = _conNew(NULLCONTAINER);
      for( nn=0; nn < m_con_count; nn++ )
      {
      
         if( _conCheckType(m_pcon[nn], XPP_OBJECT ) )
         {
            ContainerHandle pcon[2]; pcon[0] = m_pcon[nn]; pcon[1] = conXbCls;
            _conCallMethodPa(conr,"OnClassCreate",2,pcon);
         }
         else if( _conCheckType(m_pcon[nn], XPP_BLOCK ) )         
         {
            _conEvalB(conr,m_pcon[nn],1,conXbCls);
         }
      }
      _conRelease(conXbCls);
      _conRelease( conr);
   };
   // --------------------------      
   
};   
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::InitHookList(void)
{
   _pcs_ = _drtool_get_pcs_();
   pHookList = new THashTable();
   pHookList->m_pfnOnDestroyItem = gwst_hook_entry::_OnDestroyItem_;
}
// -----------------------------------------------------------------------------------------------------------------
void TXbClass::FreeHookList(void)
{
   delete pHookList;
   pHookList = 0;
}
//----------------------------------------------------------------------------------------------------------------------
DWORD TXbClass::AddClassHook(LPSTR pClassName , ContainerHandle conoHook )
{
   DWORD pHook = 0;
   DWORD cb = 0;
   if( !pClassName ) return 0;
   if(!_conCheckType(conoHook,XPP_OBJECT | XPP_BLOCK ) ) return 0;   
   cb = _xstrlen(pClassName);
   
   EnterCriticalSection(_pcs_);
   try
   {
      gwst_hook_entry*  pClsItem = ( gwst_hook_entry*) pHookList->FindItem( pClassName,cb);
      if( pClsItem ){ pClsItem->add(conoHook); }
      else
      {
         pClsItem = new gwst_hook_entry(pClassName,conoHook );
         pHookList->InsertItem(pClsItem->m_pClsName,cb,pClsItem,0);
      }
      pHook = ( DWORD ) pClsItem;
   }
   catch(...)
   {
      ;
   
   }
   LeaveCriticalSection(_pcs_);
   return pHook;
       
}
//----------------------------------------------------------------------------------------------------------------------
DWORD TXbClass::GetClassHookHandle(LPSTR pClassName )
{
   DWORD pHook = 0;
   DWORD cb = 0;
   if( !pClassName ) return 0;
   cb = _xstrlen(pClassName);
   
   EnterCriticalSection(_pcs_);
   __try
   {
      pHook = (DWORD) pHookList->FindItem( pClassName,cb);
   }
   __finally
   {
      LeaveCriticalSection(_pcs_);
   }
   return pHook;
       
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void * TXbClsGwstItem::operator new( unsigned int nSize ){ return _xgrab( nSize); }
//----------------------------------------------------------------------------------------------------------------------
void TXbClsGwstItem::operator delete( void * pp)
{
   TXbClsGwstItem * pi;
   pi = ( TXbClsGwstItem * ) pp;
   if( pi->m_conClass  != NULLCONTAINER) _conRelease(pi->m_conClass);
   _xfree(pp);
}
//----------------------------------------------------------------------------------------------------------------------
void * TXbClsMItem::operator new( unsigned int nSize )
{
   TXbClsMItem * pi;
   pi = ( TXbClsMItem * ) _xgrab( nSize);
   pi->m_conName = NULLCONTAINER;
   pi->m_nFlags = 0;
   pi->m_conBlock = NULLCONTAINER;
   pi->m_bSetGet = FALSE;
   pi->m_pNext = 0;
   return (void * ) pi;
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsMItem::operator delete( void * pp)
{
   TXbClsMItem * pi;
   pi = ( TXbClsMItem * ) pp;
   if( pi->m_conName  != NULLCONTAINER) _conRelease(pi->m_conName);
   if( pi->m_conBlock != NULLCONTAINER) _conRelease(pi->m_conBlock);
   _xfree(pp);
}
//----------------------------------------------------------------------------------------------------------------------
void * TXbClsVItem::operator new( unsigned int nSize )
{
   TXbClsVItem * pi;
   pi = ( TXbClsVItem * ) _xgrab( nSize);
   pi->m_conName = NULLCONTAINER;
   pi->m_nFlags  = 0;
   pi->m_pNext       = 0;
   return (void * ) pi;
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsVItem::operator delete( void * pp)
{
   TXbClsVItem * pi;
   pi = ( TXbClsVItem * ) pp;
   if( pi->m_conName  != NULLCONTAINER) _conRelease(pi->m_conName);
   _xfree(pp);
}
//----------------------------------------------------------------------------------------------------------------------
void * TXbClsPItem::operator new( unsigned int nSize )
{
   TXbClsPItem * pi;
   pi = ( TXbClsPItem * ) _xgrab( nSize);
   pi->m_cono = NULLCONTAINER;
   pi->m_pNext       = 0;
   return (void * ) pi;
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsPItem::operator delete( void * pp)
{
   TXbClsPItem * pi;
   pi = ( TXbClsPItem * ) pp;
   if( pi->m_cono  != NULLCONTAINER) _conRelease(pi->m_cono);
   _xfree(pp);
}
//----------------------------------------------------------------------------------------------------------------------
void * TXbClass::operator new( unsigned int nSize )
{
   TXbClass * p;
   p = (TXbClass *) _xgrab(nSize);
   p->m_conClassName  = NULLCONTAINER;
   p->m_pLastParent   = (TXbClsPItem *) 0;
   p->m_pLastMethod   = (TXbClsMItem *) 0;
   p->m_pLastVar      = (TXbClsVItem *) 0;
   p->m_nParentCount  = 0;
   p->m_nMethodCount  = 0;
   p->m_nVarCount     = 0;
   p->m_nDefaultScope = xppCLASS_EXPORTED;
   p->m_szPrintfBuffer = (LPSTR) _xgrab(1024);

   p->m_bGwst                = FALSE;
   p->m_dwGwstOffset         = 0;
   p->m_bGwstUnion           = 0;
   p->m_dwGwstUnionSize      = 0;
   p->m_bGwstReadOnly        = 0;
   p->m_pLastGwst            = (TXbClsGwstItem *) 0;
   p->m_nGwstChildCount      = 0;

   return (void *) p;
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::operator delete( void * pp)
{
   TXbClass * p;
   p = (TXbClass *) pp;
   if( p->m_conClassName  != NULLCONTAINER ) _conRelease( p->m_conClassName );
   while( p->m_pLastParent != 0){ TXbClsPItem * pi = p->m_pLastParent; p->m_pLastParent = pi->m_pNext; delete pi;}
   while( p->m_pLastMethod != 0){ TXbClsMItem * pi = p->m_pLastMethod; p->m_pLastMethod = pi->m_pNext; delete pi;}
   while( p->m_pLastVar    != 0){ TXbClsVItem * pi = p->m_pLastVar   ; p->m_pLastVar    = pi->m_pNext; delete pi;}
   while( p->m_pLastGwst   != 0){ TXbClsGwstItem * pi = p->m_pLastGwst  ; p->m_pLastGwst   = pi->m_pNext; delete pi;}
   _xfree( (void*) p->m_szPrintfBuffer );
   _xfree( pp );
}
//----------------------------------------------------------------------------------------------------------------------
ContainerHandle TXbClass::Create( ContainerHandle conco )
{
   BOOL bReleaseConco = (BOOL) (conco == NULLCONTAINER);

   if( m_conClassName != NULLCONTAINER )
   {
      ContainerHandle conaSuper  = NULLCONTAINER;
      ContainerHandle conaVar    = NULLCONTAINER;
      ContainerHandle conaMethod = NULLCONTAINER;

      BOOL bOk = FALSE;
      ULONG ulType = 0;

      if( m_dwClsHookHandle && (!m_bDisableHooks) )
      {
         reinterpret_cast<gwst_hook_entry*>( m_dwClsHookHandle )->EvalHookList( this );
      }

      conaSuper  = CollectSuper();
      conaVar    = CollectVars();
      conaMethod = CollectMethods();
      conco      = _conPut(conco , NULLCONTAINER);

      bOk = ( _conCall(conco,"CLASSCREATE",4,m_conClassName,conaSuper,conaVar,conaMethod) == 0);
      if( bOk ){ _conType(conco,&ulType); bOk = ( BOOL ) ( ulType & XPP_OBJECT ); }
#ifdef _DEBUG
      if( !bOk )
      {
         ContainerHandle cona = _conNewArray(1,4);
         _conArrayPut(cona, m_conClassName , 1 , 0 );
         _conArrayPut(cona, conaSuper      , 2 , 0 );
         _conArrayPut(cona, conaVar        , 3 , 0 );
         _conArrayPut(cona, conaMethod     , 4 , 0 );
         THDictItem* phi = new THDictItem("LastFailedClassCreateParameters",(UINT) -1,(DWORD) cona , TRUE);
         phi->m_nDataType = THDictItem::hdi_xbase;
         phi->AddToHashTable( GetTls_ht() );
      }
#endif
      _conRelease(conaSuper); _conRelease( conaVar); _conRelease(conaMethod);
      if(bOk)
      {
         if( m_bGwst )
         {
            ContainerHandle  cona  = _conNewArray(2,m_nGwstChildCount,3);
            LPSTR            pDef  = (LPSTR) _xgrab( (m_nGwstCount << 4) + 1 );
            TXbClsGwstItem * pItem;
            GwstEndUnion();
            for( pItem = m_pLastGwst; pItem ; pItem = pItem->m_pNext)
            {
               DWORD * pn = (DWORD*) ( (void*) ( pDef + ( (pItem->m_dwPos) << 4) ) );
               pn[0] = pItem->m_dwNameCrc32;
               pn[1] = pItem->m_dwShift    ;
               pn[2] = pItem->m_dwSize     ;
               pn[3] = MAKELONG( pItem->m_wChildPos,pItem->m_wGwstType);
               if( pItem->m_wChildPos )
               {
                  // ::_mc__chdef_ := {{1class,2shift,3size},...}
                  _conArrayPut(   cona , pItem->m_conClass,MAKELONG(pItem->m_wChildPos,0),1,0 );
                  _conArrayPutNL( cona , (LONG) pItem->m_dwShift,MAKELONG(pItem->m_wChildPos,0),2,0 );
                  _conArrayPutNL( cona , (LONG) pItem->m_dwSize ,MAKELONG(pItem->m_wChildPos,0),3,0 );
               }
            }
            _conSetNLMember(conco,"_mc__size_", m_dwGwstOffset );
            _conSetCLMember(conco,"_mc__mdef_",pDef, (m_nGwstCount << 4));
            _xfree( pDef );
            _conSetMember( conco , "_mc__chdef_" , cona );
            _conRelease( cona );
         }
         return conco;
      }
   }
   if( (conco != NULLCONTAINER ) && bReleaseConco) _conRelease(conco);
   return NULLCONTAINER;
}
//----------------------------------------------------------------------------------------------------------------------
ContainerHandle TXbClass::CollectSuper( void )
{
   ContainerHandle cona = _conNewArray(1,m_nParentCount);
   ULONG n;
   for( n = m_nParentCount; n != 0 ; n-- )
   {
      TXbClsPItem * pi = m_pLastParent;
      if( pi)
      {
         m_pLastParent = pi->m_pNext;
         _conArrayPut(cona,pi->m_cono,n,0);
         delete pi;
      }
   }
   m_nParentCount = 0;
   return cona;
}
//----------------------------------------------------------------------------------------------------------------------
ContainerHandle TXbClass::CollectVars( void )
{
   ContainerHandle cona = _conNewArray(2,m_nVarCount,2);
   ULONG n;
   for( n = m_nVarCount; n != 0 ; n-- )
   {
      TXbClsVItem * pi = m_pLastVar;
      if( pi)
      {
         m_pLastVar = pi->m_pNext;
         _conArrayPut(cona,pi->m_conName,n,1,0);
         _conArrayPutNL(cona,(LONG)pi->m_nFlags,n,2,0);
         delete pi;
      }
   }
   m_nVarCount = 0;
   return cona;
}
//----------------------------------------------------------------------------------------------------------------------
ContainerHandle TXbClass::CollectMethods( void )
{
   ContainerHandle cona = _conNewArray(2,m_nMethodCount,4);
   ULONG n;
   for( n = m_nMethodCount; n != 0 ; n-- )
   {
      TXbClsMItem * pi = m_pLastMethod;
      if( pi)
      {
         m_pLastMethod = pi->m_pNext;
         _conArrayPut(cona,pi->m_conName,n,1,0);
         _conArrayPutNL(cona,(LONG)pi->m_nFlags,n,2,0);
         _conArrayPut(cona,pi->m_conBlock,n,3,0);
         if( pi->m_bSetGet) _conArrayPut(cona,pi->m_conName,n,4,0);
         delete pi;
      }
   }
   m_nMethodCount = 0;
   return cona;
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::ClassName( LPSTR pClassName )
{
   if( pClassName )
   {
      m_conClassName     = _conPutC(m_conClassName,pClassName);
      m_dwClsCrc32       = _x_name2crc(pClassName);
      m_dwClsHookHandle  = GetClassHookHandle( pClassName );
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Parent( LPSTR pName ){_xparent_( _conClsObjNew(pName) );}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::_xparent_( ContainerHandle cono )
{
  if( cono != NULLCONTAINER )
  {
     TXbClsPItem * pi = new TXbClsPItem;
     pi->m_cono = cono;
     pi->m_pNext = m_pLastParent;
     m_pLastParent  = pi;
     m_nParentCount++;
  }
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::EXPORTED(void){ m_nDefaultScope = xppCLASS_EXPORTED;}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::HIDDEN(void){ m_nDefaultScope = xppCLASS_HIDDEN;}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::PROTECTED(void){ m_nDefaultScope = xppCLASS_PROTECTED;}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::_var_( LPSTR pName, ULONG nFlags)
{
  if( pName )
  {
     TXbClsVItem * pv = new TXbClsVItem;
     pv->m_pNext = m_pLastVar;
     m_pLastVar  = pv;
     pv->m_conName = _conPutC( pv->m_conName , pName );
     pv->m_nFlags  = nFlags;
     m_nVarCount++;
  }
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::AddGwstStyleMembers(void)
{
   Var("_m__pt_");
   MethodCB( "_lock_"   , "{|s,n|(n := 0), s:_m__pt_}");
   MethodCB( "_unlock_" , "{|s| NIL }");
}
//-----------------------------------------------------------------------------------------------------------------------
void TXbClass::Var( LPSTR pName,ULONG nMoreFlags){ _var_(pName,xppVAR_INSTANCE | m_nDefaultScope | nMoreFlags);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::ClassVar( LPSTR pName,ULONG nMoreFlags){ _var_(pName,xppVAR_CLASS | m_nDefaultScope | nMoreFlags );}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::SharedClassVar( LPSTR pName, ULONG nMoreFlags ){ ClassVar(pName,xppVAR_CLASS_SHARED|nMoreFlags);}
//----------------------------------------------------------------------------------------------------------------------
LPSTR TXbClass::cbbs(LPSTR s, ... )
{
   va_list v;
   va_start(v,s);
   wvsprintf(m_szPrintfBuffer,s,v);
   return m_szPrintfBuffer;
}
//----------------------------------------------------------------------------------------------------------------------
LPSTR TXbClass::_mkpf1Str_(XbCMethodType pf ,ULONG nParams , LPSTR pExtra)
{
  LPSTR p;
  LPSTR pp = m_szPrintfBuffer;
  int pfl = (int) LOWORD(pf);
  int pfh = (int) HIWORD(pf);
  ULONG nLen = 0;
  ULONG n;
  if( nParams == 0)
  {
     nLen = wsprintf(pp,"{|s,e,rt|iif(_XBMTPF1_(@s,%i,%i,@rt,@e,PCount()-1,0 %hs),"
                "rt,Eval(ErrorBlock(),e))}",pfl,pfh,(pExtra?pExtra:""));
  }
  else
  {
     LPSTR pParams = _GenCbParamBlock_(nParams);
     LPSTR pParamRef = _GenCbParamBlockRef_(nParams);
     nLen = wsprintf(pp,"{|s,%hs,e,rt|iif(_XBMTPF1_(@s,%i,%i,@rt,@e,PCount()-1,%i,%hs%hs),"
                "rt,Eval(ErrorBlock(),e))}",pParams,pfl,pfh,nParams,pParamRef,(pExtra?pExtra:""));
     _xfree(pParams); _xfree(pParamRef);
  }
  p = (LPSTR) _xgrab( nLen + 1);
  for( n = 0; n < nLen; n ++ ) p[n] = pp[n];
  return p;
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::_xmethod_( LPSTR pName, ULONG nFlags, ContainerHandle conb )
{
   ULONG ulType = 0;
   _conType(conb,&ulType);
   if( !( ulType & XPP_BLOCK ) ) { _conRelease(conb); return; }
   else
   {
      TXbClsMItem * pi = new TXbClsMItem;
      pi->m_conBlock = conb;
      pi->m_bSetGet = FALSE;
      pi->m_pNext   = m_pLastMethod;
      m_pLastMethod = pi;
      pi->m_conName = _conPutC( pi->m_conName , pName );
      pi->m_nFlags  = nFlags;
      m_nMethodCount++;
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::_method_( LPSTR pName, ULONG nFlags, LPSTR pCbString )
{
   if( pName )
   {
      ContainerHandle conb = _conNew(NULLCONTAINER);
      if( !pCbString ) _conEvalMacroStr( conb,"{|s| NIL }" );
      else _conEvalMacroStr( conb, pCbString);
      _xmethod_(pName,nFlags,conb);
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Method( LPSTR pName, XbCMethodType pf ,ULONG nParams , LPSTR pExtra)
{
   if( pName && pf )
   {
      LPSTR p = _mkpf1Str_(pf,nParams,pExtra);
      if( p )
      {
         _method_( pName , ( xppMETHOD_INSTANCE | m_nDefaultScope ) , p);
         _xfree(p);
      }
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::ClassMethod( LPSTR pName, XbCMethodType pf ,ULONG nParams , LPSTR pExtra)
{
   if( pName && pf )
   {
      LPSTR p = _mkpf1Str_(pf,nParams,pExtra);
      if( p )
      {
         _method_( pName , ( xppMETHOD_CLASS | m_nDefaultScope ) , p);
         _xfree(p);
      }
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::MethodCB( LPSTR pName, LPSTR pCbString)
{
   _method_( pName , ( xppMETHOD_INSTANCE | m_nDefaultScope ) , pCbString );
}
// -----------------------------------------------------------------------------------------------------------------
void TXbClass::Method_cbbs( LPSTR pName, LPSTR pCbString, ...)
{
   va_list v;
   va_start(v,pCbString);
   wvsprintf(m_szPrintfBuffer,pCbString,v);
   _method_( pName , ( xppMETHOD_INSTANCE | m_nDefaultScope ) , m_szPrintfBuffer );
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::ClassMethodCB( LPSTR pName, LPSTR pCbString)
{
   _method_( pName , ( xppMETHOD_CLASS | m_nDefaultScope ) , pCbString );
}
// -----------------------------------------------------------------------------------------------------------------
void TXbClass::ClassMethod_cbbs( LPSTR pName, LPSTR pCbString, ...)
{
   va_list v;
   va_start(v,pCbString);
   wvsprintf(m_szPrintfBuffer,pCbString,v);
   _method_( pName , ( xppMETHOD_CLASS | m_nDefaultScope ) , m_szPrintfBuffer );
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::_xproperty_( LPSTR pName, ULONG nFlags, ContainerHandle conb )
{
   ULONG ulType = 0;
   _conType(conb,&ulType);
   if( !( ulType & XPP_BLOCK ) ) {  _conRelease(conb); return; }
   else
   {
      TXbClsMItem * pi = new TXbClsMItem;
      pi->m_conBlock = conb;
      pi->m_bSetGet = TRUE;
      pi->m_pNext   = m_pLastMethod;
      m_pLastMethod = pi;
      pi->m_conName = _conPutC( pi->m_conName , pName );
      pi->m_nFlags  = nFlags;
      m_nMethodCount++;
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::_property_( LPSTR pName, ULONG nFlags, LPSTR pCbString )
{
   if( pName )
   {
      ContainerHandle conb = _conNew(NULLCONTAINER);
      if( !pCbString ) _conEvalMacroStr( conb,"{|s| NIL }" );
      else _conEvalMacroStr( conb, pCbString);
      _xproperty_(pName,nFlags,conb);
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Property( LPSTR pName, XbCMethodType pf ,ULONG nParams , LPSTR pExtra)
{
   if( pName && pf )
   {
      LPSTR p = _mkpf1Str_(pf,nParams,pExtra);
      if( p )
      {
         _property_( pName , ( xppMETHOD_INSTANCE | xppMETHOD_ACCESS | xppMETHOD_ASSIGN | m_nDefaultScope ) , p);
         _xfree(p);
      }
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::ClassProperty( LPSTR pName, XbCMethodType pf ,ULONG nParams , LPSTR pExtra)
{
   if( pName && pf )
   {
      LPSTR p = _mkpf1Str_(pf,nParams,pExtra);
      if( p )
      {
         _property_( pName , ( xppMETHOD_CLASS | xppMETHOD_ACCESS | xppMETHOD_ASSIGN | m_nDefaultScope ) , p);
         _xfree(p);
      }
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::PropertyCB( LPSTR pName, LPSTR pCbString)
{
   _property_( pName , ( xppMETHOD_INSTANCE | xppMETHOD_ACCESS | xppMETHOD_ASSIGN | m_nDefaultScope ) , pCbString);
}
// -----------------------------------------------------------------------------------------------------------------
void TXbClass::Property_cbbs( LPSTR pName, LPSTR pCbString, ...)
{              
   va_list v;
   va_start(v,pCbString);
   wvsprintf(m_szPrintfBuffer,pCbString,v);
   _property_( pName , (xppMETHOD_INSTANCE | xppMETHOD_ACCESS | xppMETHOD_ASSIGN | m_nDefaultScope),m_szPrintfBuffer);   
}
// -----------------------------------------------------------------------------------------------------------------
void TXbClass::PropertyCBMask( LPSTR pName, DWORD dwMask , LPSTR pVar )
{
   char sz[1024];
   _bset((LPBYTE)sz,0,1024);
   wsprintf(sz,"{|s,v| iif(PCount() > 1,(s:%s := iif(v,nOr(s:%s,%i),nAndNot(s:%s,%i))),lAnd(s:%s,%i))}",
               pVar,pVar,dwMask,pVar,dwMask,pVar,dwMask );
   _property_( pName , ( xppMETHOD_INSTANCE | xppMETHOD_ACCESS | xppMETHOD_ASSIGN | m_nDefaultScope ) , sz);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::ClassPropertyCB( LPSTR pName, LPSTR pCbString)
{
   _property_( pName , ( xppMETHOD_CLASS | xppMETHOD_ACCESS | xppMETHOD_ASSIGN | m_nDefaultScope ) , pCbString);
}
// -----------------------------------------------------------------------------------------------------------------
void TXbClass::ClassProperty_cbbs( LPSTR pName, LPSTR pCbString, ...)
{              
   va_list v;
   va_start(v,pCbString);
   wvsprintf(m_szPrintfBuffer,pCbString,v);
   _property_( pName , ( xppMETHOD_CLASS | xppMETHOD_ACCESS | xppMETHOD_ASSIGN | m_nDefaultScope ) , m_szPrintfBuffer);   
}
// -----------------------------------------------------------------------------------------------------------------
void TXbClass::ClassPropertyCBMask( LPSTR pName, DWORD dwMask , LPSTR pVar )
{
   char sz[1024];
   _bset((LPBYTE)sz,0,1024);
   wsprintf(sz,"{|s,v| iif(PCount() > 1,(s:%s := iif(v,nOr(s:%s,%i),nAndNot(s:%s,%i))),lAnd(s:%s,%i))}",
               pVar,pVar,dwMask,pVar,dwMask,pVar,dwMask );
   _property_( pName , ( xppMETHOD_CLASS | xppMETHOD_ACCESS | xppMETHOD_ASSIGN | m_nDefaultScope ) , sz);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::ROProperty( LPSTR pName, XbCMethodType pf ,ULONG nParams , LPSTR pExtra)
{
   if( pName && pf )
   {
      LPSTR p = _mkpf1Str_(pf,nParams,pExtra);
      if( p )
      {
         _property_( pName , ( xppMETHOD_INSTANCE | xppMETHOD_ACCESS | m_nDefaultScope ) , p);
         _xfree(p);
      }
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::ROClassProperty( LPSTR pName, XbCMethodType pf ,ULONG nParams , LPSTR pExtra)
{
   if( pName && pf )
   {
      LPSTR p = _mkpf1Str_(pf,nParams,pExtra);
      if( p )
      {
         _property_( pName , ( xppMETHOD_CLASS | xppMETHOD_ACCESS | m_nDefaultScope ) , p);
         _xfree(p);
      }
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::ROPropertyCB( LPSTR pName, LPSTR pCbString)
{
   _property_( pName , ( xppMETHOD_INSTANCE | xppMETHOD_ACCESS | m_nDefaultScope ) , pCbString);
}
// -----------------------------------------------------------------------------------------------------------------
void TXbClass::ROProperty_cbbs( LPSTR pName, LPSTR pCbString,...)
{              
   va_list v;
   va_start(v,pCbString);
   wvsprintf(m_szPrintfBuffer,pCbString,v);
   _property_( pName , ( xppMETHOD_INSTANCE | xppMETHOD_ACCESS | m_nDefaultScope ) , m_szPrintfBuffer);
}       
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::ROClassPropertyCB( LPSTR pName, LPSTR pCbString)
{
   _property_( pName , ( xppMETHOD_CLASS | xppMETHOD_ACCESS | m_nDefaultScope ) , pCbString);
}
// -----------------------------------------------------------------------------------------------------------------
void TXbClass::ROClassProperty_cbbs( LPSTR pName, LPSTR pCbString,...)
{              
   va_list v;
   va_start(v,pCbString);
   wvsprintf(m_szPrintfBuffer,pCbString,v);
   _property_( pName , ( xppMETHOD_CLASS | xppMETHOD_ACCESS | m_nDefaultScope ) , m_szPrintfBuffer);
}       
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::WOProperty( LPSTR pName, XbCMethodType pf ,ULONG nParams , LPSTR pExtra)
{
   if( pName && pf )
   {
      LPSTR p = _mkpf1Str_(pf,nParams,pExtra);
      if( p )
      {
         _property_( pName , ( xppMETHOD_INSTANCE | xppMETHOD_ASSIGN | m_nDefaultScope ) , p);
         _xfree(p);
      }
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::WOClassProperty( LPSTR pName, XbCMethodType pf ,ULONG nParams , LPSTR pExtra)
{
   if( pName && pf )
   {
      LPSTR p = _mkpf1Str_(pf,nParams,pExtra);
      if( p )
      {
         _property_( pName , ( xppMETHOD_CLASS | xppMETHOD_ASSIGN | m_nDefaultScope ) , p);
         _xfree(p);
      }
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::WOPropertyCB( LPSTR pName, LPSTR pCbString)
{
   _property_( pName , ( xppMETHOD_INSTANCE| xppMETHOD_ASSIGN | m_nDefaultScope ) , pCbString);
}
// -----------------------------------------------------------------------------------------------------------------
void TXbClass::WOProperty_cbbs( LPSTR pName, LPSTR pCbString,...)
{              
   va_list v;
   va_start(v,pCbString);
   wvsprintf(m_szPrintfBuffer,pCbString,v);
   _property_( pName , ( xppMETHOD_INSTANCE| xppMETHOD_ASSIGN | m_nDefaultScope ) , m_szPrintfBuffer);
}       
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::WOClassPropertyCB( LPSTR pName, LPSTR pCbString)
{
   _property_( pName , ( xppMETHOD_CLASS | xppMETHOD_ASSIGN | m_nDefaultScope ) , pCbString);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::WOClassProperty_cbbs( LPSTR pName, LPSTR pCbString,...)
{              
   va_list v;
   va_start(v,pCbString);
   wvsprintf(m_szPrintfBuffer,pCbString,v);
   _property_( pName , ( xppMETHOD_CLASS | xppMETHOD_ASSIGN | m_nDefaultScope ) , m_szPrintfBuffer);
}       
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::GwstParent(LPSTR pParent)
{
   if( pParent ) _xGwstParent_( _conClsObjNew(pParent) );
   else _xGwstParent_( NULLCONTAINER );
}
//-----------------------------------------------------------------------------------------------------------------------
void TXbClass::_xGwstParent_( ContainerHandle concoParent )
{
   if( concoParent == NULLCONTAINER ) Parent("GWST");
   else
   {
      if( m_bGwst )
      {
         _conRelease( concoParent );
         concoParent = NULLCONTAINER;
         Parent("GWST");
      }
      // cannot inherit if structure is already initialized;
      _xparent_( concoParent );
   }
   m_bGwst = TRUE;
   SharedClassVar( "_mc__chdef_" );
   SharedClassVar( "_mc__mdef_" );
   SharedClassVar( "_mc__size_"  );
   if( concoParent != NULLCONTAINER )
   {
      ContainerHandle conco   = concoParent; // m_pLastParent->m_cono;
      ULONG           nDefLen = 0;
      LPSTR           pDef    = _pszMember(conco, "_mc__mdef_", &nDefLen);

      m_dwGwstOffset = (DWORD) _conGetNLMember( conco , "_mc__size_" );

      if( pDef )
      {
         ULONG           nItems,n;
         ContainerHandle cona    = _conNew(NULLCONTAINER);
         _conGetMember( conco , "_mc__chdef_", cona);
         nItems = nDefLen >> 4;
         for( n = 0; n < nItems; n++ )
         {
            DWORD * pn = (DWORD*) ( (void*) ( pDef + (n << 4) ) );
            TXbClsGwstItem * pItem = new TXbClsGwstItem;
            m_nGwstCount++;
            // ::_mc__mdef_  :=  // 0Crc32(MName)+1SHIFT+2SIZE+3CHPOS" + ...
            pItem->m_dwNameCrc32  = pn[0];
            pItem->m_dwShift      = pn[1];
            pItem->m_dwSize       = pn[2];
            pItem->m_wChildPos   = LOWORD(pn[3]);
            pItem->m_wGwstType   = HIWORD(pn[3]);
            if( pItem->m_wChildPos )
            {
               pItem->m_conClass = _conArrayGet( cona,NULLCONTAINER,MAKELONG(pItem->m_wChildPos,0),1,0 );
               m_nGwstChildCount++;
            }
            pItem->m_dwPos        = m_nGwstCount-1;
            pItem->m_pNext        = m_pLastGwst;
            m_pLastGwst           = pItem;
         }
         _conRelease( cona );
         _xfree( pDef );
      }
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member( LPSTR pName , ULONG nMType, UINT nSize)
{

   TXbClsGwstItem * pItem = new TXbClsGwstItem;
   char sz[512];
   char sztps[] = "{|s,v| %s(@v, PCount(),@s:_m__pto_:_m__pt_,s:_m__shift_ ,%u,s:_m__pto_:_m__size_,s:_m__ghpt_,%u )}";
   char sztpn[] = "{|s,v| %s(@v, PCount(),@s:_m__pto_:_m__pt_,s:_m__shift_ ,%u,s:_m__pto_:_m__size_,s:_m__ghpt_)}";

   m_nGwstCount++;

   pItem->m_dwNameCrc32  = _x_name2crc(pName);
   pItem->m_dwShift      = m_dwGwstOffset;
   pItem->m_dwSize       = (DWORD) nSize;
   pItem->m_wChildPos    = 0;
   pItem->m_wGwstType    = LOWORD(nMType);
   pItem->m_dwPos        = m_nGwstCount -1;
   pItem->m_conClass     = NULLCONTAINER;
   pItem->m_pNext        = m_pLastGwst;
   m_pLastGwst           = pItem;
   if( m_bGwstUnion ){ if (pItem->m_dwSize > m_dwGwstUnionSize ) m_dwGwstUnionSize = pItem->m_dwSize; }
   else m_dwGwstOffset += pItem->m_dwSize;
   switch( nMType )
   {
      case __GWST_MEMBER_BOOL__ :
      {
         wsprintf(sz,sztpn,"_GWST_XBSETGET_BOOL_",pItem->m_dwShift);
         break;
      }
      case __GWST_MEMBER_BYTEBOOL__ :
      {
         wsprintf(sz,sztpn,"_GWST_XBSETGET_BYTEBOOL_",pItem->m_dwShift);
         break;
      }
      case __GWST_MEMBER_BYTE__ :
      {
         wsprintf(sz,sztpn,"_GWST_XBSETGET_BYTE_",pItem->m_dwShift);
         break;
      }
      case __GWST_MEMBER_WORD__ :
      {
         wsprintf(sz,sztpn,"_GWST_XBSETGET_WORD_",pItem->m_dwShift);
         break;
      }
      case __GWST_MEMBER_DWORD__ :
      {
         wsprintf(sz,sztpn,"_GWST_XBSETGET_DWORD_",pItem->m_dwShift);
         break;
      }
      case __GWST_MEMBER_DWORD64__ :
      {
         wsprintf(sz,sztpn,"_GWST_XBSETGET_DWORD64_",pItem->m_dwShift);
         break;
      }
      case __GWST_MEMBER_PCLIPVAR__ :
      {
         wsprintf(sz,sztpn,"_GWST_XBSETGET_PCLIPVAR_",pItem->m_dwShift);
         break;
      }
      case __GWST_MEMBER_FLOAT__ :
      {
         wsprintf(sz,sztpn,"_GWST_XBSETGET_FLOAT_",pItem->m_dwShift);
         break;
      }
      case __GWST_MEMBER_DOUBLE__ :
      {
         wsprintf(sz,sztpn,"_GWST_XBSETGET_DOUBLE_",pItem->m_dwShift);
         break;
      }
      case __GWST_MEMBER_LPSTR__ :
      {
         wsprintf(sz,sztpn,"_GWST_XBSETGET_LPSTR_",pItem->m_dwShift);
         break;
      }
      case __GWST_MEMBER_BINSTR__ :
      {
         wsprintf(sz,sztps,"_GWST_XBSETGET_BINSTR_",pItem->m_dwShift,pItem->m_dwSize);
         break;
      }
      case __GWST_MEMBER_SZSTR__ :
      {
         wsprintf(sz,sztps,"_GWST_XBSETGET_SZSTR_",pItem->m_dwShift,pItem->m_dwSize);
         break;
      }
      case __GWST_MEMBER_SZWSTR__ :
      {
         wsprintf(sz,sztps,"_GWST_XBSETGET_SZWSTR_",pItem->m_dwShift,pItem->m_dwSize);
         break;
      }
      case __GWST_MEMBER_DYNSZ__ :
      {
         wsprintf(sz,sztps,"_GWST_XBSETGET_DYNSZ_",pItem->m_dwShift,pItem->m_dwSize);
         break;
      }
      case __GWST_MEMBER_DYNWSZ__:
      {
         wsprintf( sz, sztps, "_GWST_XBSETGET_DYNWSZ_", pItem->m_dwShift, pItem->m_dwSize );
         break;
      }
      case __GWST_MEMBER_WORDNET__ :
      {
         wsprintf(sz,sztpn,"_GWST_XBSETGET_WORDNET_",pItem->m_dwShift);
         break;
      }
      case __GWST_MEMBER_DWORDNET__ :
      {
         wsprintf(sz,sztpn,"_GWST_XBSETGET_DWORDNET_",pItem->m_dwShift);
         break;
      }
      case __GWST_MEMBER_XPPGUIWND__ :
      {
         wsprintf(sz,sztpn,"_GWST_XBSETGET_XPPGUIWND_",pItem->m_dwShift);
         break;
      }
      case __GWST_MEMBER_SINT8__ :
      {
         wsprintf(sz,sztpn,"_GWST_XBSETGET_SINT8_",pItem->m_dwShift);
         break;
      }
      case __GWST_MEMBER_SINT16__ :
      {
         wsprintf(sz,sztpn,"_GWST_XBSETGET_SINT16_",pItem->m_dwShift);
         break;
      }
      case __GWST_MEMBER_UINT32__ :
      {
         wsprintf(sz,sztpn,"_GWST_XBSETGET_UINT32_",pItem->m_dwShift);
         break;
      }
      case __GWST_MEMBER_NINT64__ :
      {
         wsprintf(sz,sztpn,"_GWST_XBSETGET_NINT64_",pItem->m_dwShift);
         break;
      }
      case __GWST_MEMBER_XDATE__ :
      {
         wsprintf(sz,sztpn,"_GWST_XBSETGET_XDATE_",pItem->m_dwShift);
         break;
      }
      case __GWST_MEMBER_POINTER32__ :
      {
         wsprintf(sz,sztpn,"_GWST_XBSETGET_POINTER32_",pItem->m_dwShift);
         break;
      }
      case __GWST_MEMBER_HANDLE__ :
      {
         wsprintf(sz,sztpn,"_GWST_XBSETGET_HANDLE_",pItem->m_dwShift);
         break;
      }
      default:
      {
         wsprintf(sz,"{|| NIL}");
         break;
      }
   }
   if( m_bGwstReadOnly ) ROPropertyCB(pName,sz);
   else PropertyCB(pName,sz);
}
//-----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_BitField(LPSTR pName , LPSTR pHolder , DWORD sh, DWORD cb , DWORD nBits)
{
   DWORD pSet = (DWORD) _dw_bf_set_;
   DWORD pGet = (DWORD) _dw_bf_get_;
   char sz[1024];
   
   if( nBits == 16 ){ pSet = (DWORD) _w_bf_set_; pGet = (DWORD) _w_bf_get_; }   
   else{ if( nBits == 8 ){ pSet = (DWORD) _b1_bf_set_; pGet = (DWORD) _b1_bf_get_; }}
   ZeroMemory(sz,1024);
   wsprintf(sz,"{|s,v| iif(PCount() > 1, s:%s := nFpCall(%i,s:%s,%i,%i,v),nFpCall(%i,s:%s,%i,%i))}",
                                        pHolder,pSet,pHolder,sh,cb,pGet,pHolder,sh,cb );
   PropertyCB(pName,sz);
}
// -----------------------------------------------------------------------------------------------------------------
static void EmbededStructArray_xb( XppParamList pl )
{
   TXppParamList xpp(pl,8);// 1Self,2nItem,3nShift,4nSize,5@aArr,6oClsObj,7cMHolder,8nCount
   ContainerHandle Self = xpp[1]->Get();
   if( xpp[2]->CheckType(XPP_NUMERIC ) )
   {
      LONG nCount = xpp[8]->GetLong();
      LONG nItem  = xpp[2]->GetLong();
      ContainerHandle cona = NULLCONTAINER;
      if( nCount < 1 ) return;
      if( nItem  < 0 ) return;
      if( nItem  >= nCount ) return;       
      if( !xpp[5]->CheckType(XPP_ARRAY) ){ xpp[5]->PutNewArray(1,nCount); }
      cona = xpp[5]->Get();
      if( ((LONG) _conGetArrayLen(cona)) < nCount ){ _conResizeA(cona,nCount); }
      if( _conArrayCheckType(cona,XPP_OBJECT,nItem+1,0) )
      {
         _conArrayGet(cona,xpp[0]->con(),nItem+1,0);         
      }
      else
      {
         LONG dw = xpp[3]->GetDWord() + ( ((DWORD) nItem) *  (xpp[4]->GetDWord()));
         ContainerHandle cono = _conMCallConNR("new",xpp[6]->Get(),2,_conNew(Self),_conPutNL(0,(LONG) dw));
         xpp[0]->Put(cono);
         _conArrayPut(cona,cono,nItem+1,0);
         _conRelease( cono );
      }         
   }
   else
   {
      xpp[0]->PutLong( _conMCallLong(Self,"_addressof_",xpp[7]->LockStr()));      
   }
}
// -----------------------------------------------------------------------------------------------------------------
void TXbClass::Member_EmbededStructArray(LPSTR pName , LPSTR pCls , LPSTR pHolder, LPSTR pCounter, DWORD sh, DWORD cb)
{
   char sz[1024];
   ZeroMemory(sz,1024);
   wsprintf(sz,"{|s,n| XbFpCall(%i,s,n,%i,%i,@s:_array_%s,%s(),\"%s\",s:%s)}",
                       (DWORD) EmbededStructArray_xb,sh,cb,pName,pCls,pHolder,pCounter);
   MethodCB(pName,sz);                       
   ZeroMemory(sz,1024);
   wsprintf(sz,"_array_%s",pName );
   Var(sz);
      
   
}
//-----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_Bool(LPSTR pName){Member(pName, __GWST_MEMBER_BOOL__ ,4);}
void TXbClass::Member_ByteBool(LPSTR pName){Member(pName, __GWST_MEMBER_BYTEBOOL__ ,1);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_Byte(LPSTR pName){Member(pName, __GWST_MEMBER_BYTE__ ,1);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_Word(LPSTR pName){Member(pName, __GWST_MEMBER_WORD__ ,2);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_Int16(LPSTR pName){Member(pName, __GWST_MEMBER_WORD__ ,2);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_Short(LPSTR pName){Member(pName, __GWST_MEMBER_WORD__ ,2);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_WordNet(LPSTR pName){Member(pName, __GWST_MEMBER_WORDNET__ ,2);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_DWord(LPSTR pName){Member(pName, __GWST_MEMBER_DWORD__ ,4);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_ULong(LPSTR pName){Member(pName, __GWST_MEMBER_DWORD__ ,4);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_Long(LPSTR pName){Member(pName, __GWST_MEMBER_DWORD__ ,4);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_UInt(LPSTR pName){Member(pName, __GWST_MEMBER_DWORD__ ,4);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_Int(LPSTR pName){Member(pName, __GWST_MEMBER_DWORD__ ,4);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_Int32(LPSTR pName){Member(pName, __GWST_MEMBER_DWORD__ ,4);}
//-----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_DWordNet(LPSTR pName){Member(pName, __GWST_MEMBER_DWORDNET__ ,4);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_LParam(LPSTR pName){Member(pName, __GWST_MEMBER_DWORD__ ,4);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_WParam(LPSTR pName){Member(pName, __GWST_MEMBER_DWORD__ ,4);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_Pointer(LPSTR pName){Member(pName, __GWST_MEMBER_POINTER32__ ,4);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_Pointer32(LPSTR pName){Member(pName, __GWST_MEMBER_POINTER32__ ,4);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_Handle(LPSTR pName){Member(pName, __GWST_MEMBER_HANDLE__ ,4);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_hWnd(LPSTR pName){Member(pName, __GWST_MEMBER_HANDLE__ ,4);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_hDC(LPSTR pName){Member(pName, __GWST_MEMBER_HANDLE__ ,4);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_pClipVar(LPSTR pName){Member(pName, __GWST_MEMBER_PCLIPVAR__ ,4);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_CodeBlock(LPSTR pName){Member(pName, __GWST_MEMBER_PCLIPVAR__ ,4);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_lpXBase(LPSTR pName){Member(pName, __GWST_MEMBER_PCLIPVAR__ ,4);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_Xbase(LPSTR pName){Member(pName, __GWST_MEMBER_PCLIPVAR__ ,4);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_DWord64(LPSTR pName){Member(pName, __GWST_MEMBER_DWORD64__ ,8);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_Double(LPSTR pName){Member(pName, __GWST_MEMBER_DOUBLE__ ,8);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_Float(LPSTR pName){Member(pName, __GWST_MEMBER_FLOAT__ ,4);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_lpStr(LPSTR pName){Member(pName, __GWST_MEMBER_LPSTR__ ,4);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_BinStr(LPSTR pName , UINT nSize){Member(pName, __GWST_MEMBER_BINSTR__ ,nSize);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_szStr(LPSTR pName , UINT nSize){Member(pName, __GWST_MEMBER_SZSTR__ ,nSize);}
void TXbClass::Member_szWStr(LPSTR pName , UINT nSize){Member(pName, __GWST_MEMBER_SZWSTR__ ,(nSize*2));}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_DynSz( LPSTR pName ) { Member( pName, __GWST_MEMBER_DYNSZ__, 4 ); }
void TXbClass::Member_DynSzW( LPSTR pName ) { Member( pName, __GWST_MEMBER_DYNWSZ__, 4 ); }

//-----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_XppGuiWnd(LPSTR pName){Member(pName, __GWST_MEMBER_XPPGUIWND__ ,4);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::Member_SINT8(LPSTR pName  ){Member(pName, __GWST_MEMBER_SINT8__  ,1);}
void TXbClass::Member_SINT16(LPSTR pName ){Member(pName, __GWST_MEMBER_SINT16__ ,2);}
void TXbClass::Member_UINT32(LPSTR pName ){Member(pName, __GWST_MEMBER_UINT32__ ,4);}
void TXbClass::Member_NINT64(LPSTR pName ){Member(pName, __GWST_MEMBER_NINT64__ ,8);}
void TXbClass::Member_XDate(LPSTR pName ){Member(pName, __GWST_MEMBER_XDATE__ ,8);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::_xchild_(LPSTR pName , ContainerHandle conco )
{
   TXbClsGwstItem * pItem = new TXbClsGwstItem;
   char szExtra[128];

   m_nGwstChildCount++;
   m_nGwstCount++;

   pItem->m_dwNameCrc32  = _x_name2crc(pName);
   pItem->m_dwShift      = m_dwGwstOffset;
   pItem->m_dwSize       = (DWORD) _conGetNLMember(conco,"_mc__size_");
   pItem->m_wChildPos    = LOWORD(m_nGwstChildCount);
   pItem->m_wGwstType    = 0;
   pItem->m_dwPos        = m_nGwstCount-1;
   pItem->m_conClass     = conco;
   pItem->m_pNext        = m_pLastGwst;
   m_pLastGwst           = pItem;
   if( m_bGwstUnion ){ if (pItem->m_dwSize > m_dwGwstUnionSize ) m_dwGwstUnionSize = pItem->m_dwSize; }
   else m_dwGwstOffset += pItem->m_dwSize;

   wsprintf(szExtra,"{|s| s:_m__child_[%u]}",MAKELONG(pItem->m_wChildPos,0));
   ROPropertyCB(pName,szExtra);
}
//-----------------------------------------------------------------------------------------------------------------------
void TXbClass::Child( LPSTR pName , LPSTR pClassName){ _xchild_(pName ,_conClsObjNew(pClassName) ); }
//-----------------------------------------------------------------------------------------------------------------------
void TXbClass::GwstReadOnly(void){ m_bGwstReadOnly = TRUE; }
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::GwstReadWrite(void){ m_bGwstReadOnly = FALSE; }
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::GwstBeginUnion(void){if( !m_bGwstUnion ){ m_bGwstUnion = TRUE; m_dwGwstUnionSize = 0;}}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::GwstEndUnion(void)
{
   if(m_bGwstUnion)
   {
      m_dwGwstOffset += m_dwGwstUnionSize;
      m_bGwstUnion = FALSE;
      m_dwGwstUnionSize = 0;
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::GwstSkipBytes(ULONG nBytes)
{
   if(m_bGwstUnion)
   {
      if( nBytes > m_dwGwstUnionSize ) m_dwGwstUnionSize = nBytes;
   }
   else m_dwGwstOffset += nBytes;
}
//----------------------------------------------------------------------------------------------------------------------
UINT  TXbClass::GwstGetOffset(){ return m_dwGwstOffset; }
//----------------------------------------------------------------------------------------------------------------------
void  TXbClass::GwstSetOffset( UINT nn ){ m_dwGwstOffset = (DWORD) nn; }
//-----------------------------------------------------------------------------------------------------------------------
void  TXbClass::GwstBack(void) { if (m_pLastGwst) { m_dwGwstOffset = m_pLastGwst->m_dwShift; } }
//----------------------------------------------------------------------------------------------------------------------
void TXbClass::GwstAdjustSize( ULONG nBytes )
{
   if(m_bGwstUnion)
   {
      if( nBytes > (m_dwGwstOffset + m_dwGwstUnionSize)) m_dwGwstUnionSize = (nBytes - m_dwGwstOffset);
   }
   else
   {
      if( nBytes > m_dwGwstOffset) m_dwGwstOffset = nBytes;
   }
}
//-----------------------------------------------------------------------------------------------------------------------
void TXbClass::GwstAlignNextMember(DWORD dwAlign)
{
   if(m_bGwstUnion)
   {
      DWORD dwRest = (m_dwGwstOffset + m_dwGwstUnionSize) % dwAlign;
      if( dwRest ) m_dwGwstUnionSize += dwRest;
   }
   else
   {
      DWORD dwRest = m_dwGwstOffset %  dwAlign;
      if( dwRest ) m_dwGwstOffset += dwRest;
   }
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _XBMTPF1_( XppParamList pl)
{
   XbCMethodType pf = ( XbCMethodType )( MAKELONG(_parLong(pl,2),_parLong(pl,3)) );
   BOOL bRet = FALSE;
   if( pl ) 
   {
      TXbClsParams xpp(pl);   
      if(pf){ (*pf)(&xpp); }
      else 
      {
         xpp.GenError();
         xpp.SetErrorSubSystem("TXbClass");
         xpp.SetErrorOperation("_XBMTPF1_");
         xpp.SetErrorDescription("Invalid function pointer.");
         xpp.SetErrorGenCode(0x1000);
      }
      bRet = xpp.m_bResult;      
   }
   _retl(pl,bRet);
}
//----------------------------------------------------------------------------------------------------------------------
static LPSTR _GenCbParamBlock_( ULONG nParams )
{
   if( nParams )
   {
      LPSTR pOut  = (LPSTR) _xgrab( (nParams * 6)+1 );
      LPSTR p     = pOut;
      ULONG n;
      for( n=1 ;n < nParams; n++) p += wsprintf(p,"p%lu,",n);
      wsprintf(p,"p%lu",nParams);
      return pOut;
   }
   return (LPSTR) 0;
}
//----------------------------------------------------------------------------------------------------------------------
static LPSTR _GenCbParamBlockRef_( ULONG nParams )
{
   if( nParams )
   {
      LPSTR pOut  = (LPSTR) _xgrab( (nParams * 7)+1 );
      LPSTR p     = pOut;
      ULONG n;
      for( n=1 ;n < nParams; n++) p += wsprintf(p,"@p%lu,",n);
      wsprintf(p,"@p%lu",nParams);
      return pOut;
   }
   return (LPSTR) 0;
}
//----------------------------------------------------------------------------------------------------------------------
static DWORD _x_name2crc( LPSTR pName)
{
   DWORD dw  = 0;
   ULONG nNameLen = _xstrlen( pName );
   LPSTR pp  = (LPSTR) _xgrab( nNameLen +1);
   _bcopy((LPBYTE)pp, (LPBYTE) pName, nNameLen);
   CharLowerBuff(pp,nNameLen);
   dw = dwCrc32(0,(LPBYTE)pp,nNameLen);
   _xfree( (void*) pp );
   return dw;
}
// -----------------------------------------------------------------------------------------------------------------
static void TXbClass_opaque_prop_ansi2wide_meth_( TXbClsParams * px)
{
   void* psc = px->GetSelfC();
   if( psc )
   {
      LPWSTR* ppw = (LPWSTR*) _mk_ptr_(LPVOID,psc, px->GetExtraLong(1) );
      if( px->PCount() > 0 ){ px->Param_setprop_ansi2wide(1,ppw); }
      else { px->PutReturn_getprop_wide2ansi(ppw); }
   }
}
// -----------------------------------------------------------------------------------------------------------------
void TXbClass::opaque_prop_ansi2wide( LPSTR pName , DWORD offset )
{
   char sz_extra[32];
   wsprintf(sz_extra,",%i",offset);
   Property(pName,TXbClass_opaque_prop_ansi2wide_meth_,1,sz_extra);
}
// -----------------------------------------------------------------------------------------------------------------
static void TXbClass_opaque_prop_ARGB_meth_( TXbClsParams * px)
{
   void* psc = px->GetSelfC();
   if( psc )
   {
      LONG* pp = (LONG*) _mk_ptr_(LPVOID,psc, px->GetExtraLong(1) );
      if( px->PCount() > 0 ){ *pp = px->GetParamLong(1); }
      else { px->PutReturnLong((LONG) *pp ); }
   }
}
// -----------------------------------------------------------------------------------------------------------------
void TXbClass::opaque_prop_ARGB( LPSTR pName , DWORD offset )
{
   char sz_extra[32];
   wsprintf(sz_extra,",%i",offset);
   Property(pName,TXbClass_opaque_prop_ARGB_meth_,1,sz_extra);
}
// -----------------------------------------------------------------------------------------------------------------



