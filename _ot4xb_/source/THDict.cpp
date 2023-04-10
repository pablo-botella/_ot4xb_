//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
#define PXERROR( n , m , d )  px->GenError();px->SetErrorSubSystem("ot4xb"); \
                              px->SetErrorOperation("THDict::"  ##m  "()"); \
                              px->SetErrorDescription( d ); \
                              px->SetErrorGenCode(0x00300000 + n);
// -----------------------------------------------------------------------------------------------------------------
static void hdict_add_env_strings(  THashTable * pht , LPSTR pEnvironment );
//----------------------------------------------------------------------------------------------------------------------
static  void* lock_hdict( THashTable * pHt )
{
   if( pHt )
   {
      if( pHt->m_cs_cargo )
      {
         EnterCriticalSection((CRITICAL_SECTION*) pHt->m_cs_cargo );
         return pHt->m_cs_cargo;
      }
   }
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
static  void* lock_hdict( THtcsTable* pHt )
{
   if( pHt )
   {
      if( pHt->m_cs_cargo )
      {
         EnterCriticalSection((CRITICAL_SECTION*) pHt->m_cs_cargo );
         return pHt->m_cs_cargo;
      }
   }
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
static  void unlock_hdict( void* cs )
{
   if( cs )
   {
      LeaveCriticalSection((CRITICAL_SECTION*) cs);
   }
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _HDICT_NEW( XppParamList pl )// (pOld,nBuckets,nMaxPopulation,lSync) -> pTHashTable
{
   THashTable * pHt  = reinterpret_cast<THashTable *>(_parLong(pl,1));
   void* cs = 0;
   cs = lock_hdict(pHt);
   if( pHt )
   {
      delete pHt;
   }
   pHt = new THashTable((DWORD) _parLong(pl,2),(DWORD) _parLong(pl,3) );
   pHt->m_pfnOnDestroyItem = THDictItem::_OnDestroyItem_;
   if( _parl(pl,4) && ( cs == 0) )
   {
      pHt->m_cs_cargo = _xgrab(sizeof(CRITICAL_SECTION));
      InitializeCriticalSection( (CRITICAL_SECTION*) pHt->m_cs_cargo );
   }
   pHt->m_cs_cargo = cs;
   _stornl((LONG) pHt , pl,1,0);
   _retnl( pl , (LONG) pHt );
   unlock_hdict(cs);
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _HDICTCS_NEW( XppParamList pl )// (pOld,nBuckets,nMaxPopulation,lSync) -> pTHashTable
{
   THtcsTable * pHt  = reinterpret_cast<THtcsTable *>(_parLong(pl,1));
   void* cs = 0;
   cs = lock_hdict(pHt);
   if( pHt )
   {
      delete pHt;
   }
   pHt = new THtcsTable((DWORD) _parLong(pl,2),(DWORD) _parLong(pl,3) );
   pHt->m_pfnOnDestroyItem = THDictItem::_OnDestroyItem_;
   if( _parl(pl,4) && ( cs == 0) )
   {
      pHt->m_cs_cargo = _xgrab(sizeof(CRITICAL_SECTION));
      InitializeCriticalSection( (CRITICAL_SECTION*) pHt->m_cs_cargo );
   }
   pHt->m_cs_cargo = cs;
   _stornl((LONG) pHt , pl,1,0);
   _retnl( pl , (LONG) pHt );
   unlock_hdict(cs);
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _HDICT_DESTROY( XppParamList pl )
{
   THashTable * pHt  = reinterpret_cast<THashTable *>( _parLong(pl,1) );
   void* cs = 0;
   cs = lock_hdict(pHt);
   if( pHt ) delete pHt;
   _stornl(0,pl,1,0);
   _retnl(pl,0);
   if( cs )
   {
      DeleteCriticalSection((CRITICAL_SECTION*) cs );
      _xfree(cs);
   }
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _HDICTCS_DESTROY( XppParamList pl )
{
   THtcsTable * pHt  = reinterpret_cast<THtcsTable *>( _parLong(pl,1) );
   void* cs = 0;
   cs = lock_hdict(pHt);
   if( pHt ) delete pHt;
   _stornl(0,pl,1,0);
   _retnl(pl,0);
   if( cs )
   {
      DeleteCriticalSection((CRITICAL_SECTION*) cs );
      _xfree(cs);
   }
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _HDICT_KEY_COMPARE( XppParamList pl ) // (k1,k2) -> lEqual
{
   THDictKey* phk1  = THDictKey::FromPl(pl,1);
   THDictKey* phk2  = THDictKey::FromPl(pl,2);
   int iCmp = 0;
   if( phk1 && phk2 ) iCmp = THashTable::Compare(phk1->m_pKey,phk1->m_cbKey,0,phk2->m_pKey,phk2->m_cbKey,0);
   else if( phk1 || phk2 ) iCmp = 1;
   if( phk1 ) delete phk1;
   if( phk1 ) delete phk2;
   _retl(pl,(BOOL) ( iCmp == 0 ) );
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _HDICTCS_KEY_COMPARE( XppParamList pl ) // (k1,k2) -> lEqual
{
   THDictKey* phk1  = THDictKey::FromPl(pl,1);
   THDictKey* phk2  = THDictKey::FromPl(pl,2);
   int iCmp = 0;
   if( phk1 && phk2 ) iCmp = THtcsTable::Compare(phk1->m_pKey,phk1->m_cbKey,0,phk2->m_pKey,phk2->m_cbKey,0);
   else if( phk1 || phk2 ) iCmp = 1;
   if( phk1 ) delete phk1;
   if( phk1 ) delete phk2;
   _retl(pl,(BOOL) ( iCmp == 0 ) );
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _HDICT_SETPROP( XppParamList pl ) // (s:_m__pHt_,c,v) -> NIL
{
   THashTable * pHt  = reinterpret_cast<THashTable *>( _parLong(pl,1) );
   void* cs = 0; cs = lock_hdict(pHt);

   if( pHt )
   {
      THDictKey* phk  = THDictKey::FromPl(pl,2);
      if( phk )
      {
         BOOL bByRef = FALSE;
         ContainerHandle con = _conParam(pl,3,&bByRef);
         THDictItem* phi = new THDictItem(phk,con);
         if( !bByRef ) _conRelease(con);
         if( phi )
         {
            phi->AddToHashTable( pHt );

         }
         delete phk;
      }
   }
   _ret(pl);
   unlock_hdict(cs);
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _HDICTCS_SETPROP( XppParamList pl ) // (s:_m__pHt_,c,v) -> NIL
{
   THtcsTable * pHt  = reinterpret_cast<THtcsTable *>( _parLong(pl,1) );
   void* cs = 0; cs = lock_hdict(pHt);
   if( pHt )
   {
      THDictKey* phk  = THDictKey::FromPl(pl,2);
      if( phk )
      {
         BOOL bByRef = FALSE;
         ContainerHandle con = _conParam(pl,3,&bByRef);
         THDictItem* phi = new THDictItem(phk,con);
         if( !bByRef ) _conRelease(con);
         if( phi )
         {
            phi->AddToHashTable( pHt );

         }
         delete phk;
      }
   }
   _ret(pl);
   unlock_hdict(cs);
}
// -----------------------------------------------------------------------------------------------------------------
static void hdict_add_env_strings(  THashTable * pht , LPSTR pEnvironment )
{
   void* cs = 0;   
   cs = lock_hdict(pht);

   if (pht && pEnvironment)
   {
      LPSTR p = pEnvironment;
      while (*p)
      {
         UINT  cb = 0;
         UINT  ns = 0;
         for (; p[cb]; cb++)
         {
            if ((!ns) && (p[cb] == '='))
            {
               if (cb) { ns = cb; }
            }
         }
         if ((((int)ns) > 0) && (cb > 2) && (cb > (ns + 1)))
         {
            THDictItem* phi = new THDictItem(p, ns, _mk_ptr_(LPSTR, p, (ns + 1)), cb - (ns + 1), TRUE);
            phi->AddToHashTable(pht);
         }
         p = _mk_ptr_(LPSTR, p, cb + 1);
      }
   }
   unlock_hdict(cs);
}
// -----------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_( _HDICT_ADD_ENV_STRINGS  )
{
   TXppParamList xpp(pl,2);
   THashTable * pht  = reinterpret_cast<THashTable *>( xpp[1]->GetLong() );
   LPSTR p = (LPSTR) xpp[2]->GetDWord();
   BOOL bReleaseEnvBlock = (BOOL) ( p ? 0 : 1 );
   if( bReleaseEnvBlock )
   {
       p = GetEnvironmentStrings();
   }
   hdict_add_env_strings( pht , p);
   if( bReleaseEnvBlock &&  p)
   {
      FreeEnvironmentStrings(p);
   }
}
// -----------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_( _HDICT_FROM_ZKDW ) // _HDICT_FROM_ZKDW( ht,cStr) -> nItems // DWORD value DWORD keycb BYTE key[keycb]
{
   TXppParamList xpp(pl,2);
   THashTable * pht  = reinterpret_cast<THashTable *>( xpp[1]->GetLong() );
   void* cs = 0;   cs = lock_hdict(pht);
   DWORD item_count = 0;
   if( pht )
   {
      DWORD  cb = 0;
      LPBYTE p  = (LPBYTE) xpp[2]->LockStr(&cb);
      while( cb > 8 )
      {
         DWORD value = _mk_ptr_(LPDWORD,p,0)[0];
         DWORD keycb = _mk_ptr_(LPDWORD,p,0)[1];
         cb -= 8;
         p   = _mk_ptr_(LPBYTE,p, 8 );
         if( (keycb <= cb) && ( keycb ) )
         {
            THDictItem* phi = new THDictItem((LPSTR) p,(UINT) keycb, value , TRUE );
            phi->AddToHashTable( pht);
            p   = _mk_ptr_(LPBYTE,p, keycb );
            cb -= keycb;
            item_count++;
         }
         else
         {
            cb = 0;
         }
      }
   }
   unlock_hdict(cs);
   xpp[0]->PutDWord(item_count);
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _HDICT_GETPROP( XppParamList pl )
{
   THashTable * pHt  = reinterpret_cast<THashTable *>( _parLong(pl,1) );
   void* cs = 0; cs = lock_hdict(pHt);
   ContainerHandle conr = _conNew(NULLCONTAINER);
   if( pHt )
   {
      THDictKey* phk  = THDictKey::FromPl(pl,2);
      if( phk )
      {
         THDictItem* phi = phk->Find( pHt );
         if( phi ) phi->ConPutValue(conr);
         delete phk;
      }
   }
   _conReturn(pl,conr); _conRelease(conr);
   unlock_hdict(cs);
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _HDICTCS_GETPROP( XppParamList pl )
{
   THtcsTable * pHt  = reinterpret_cast<THtcsTable *>( _parLong(pl,1) );
   void* cs = 0; cs = lock_hdict(pHt);
   ContainerHandle conr = _conNew(NULLCONTAINER);
   if( pHt )
   {
      THDictKey* phk  = THDictKey::FromPl(pl,2);
      if( phk )
      {
         THDictItem* phi = phk->Find( pHt );
         if( phi ) phi->ConPutValue(conr);
         delete phk;
      }
   }
   _conReturn(pl,conr); _conRelease(conr);
   unlock_hdict(cs);
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _HDICT_ISPROP( XppParamList pl )
{
   THashTable * pHt  = reinterpret_cast<THashTable *>( _parLong(pl,1) );
   void* cs = 0; cs = lock_hdict(pHt);
   BOOL b = FALSE;
   if( pHt )
   {
      THDictKey* phk  = THDictKey::FromPl(pl,2);
      if( phk )
      {
         THDictItem* phi = phk->Find( pHt );
         if( phi ){ b = TRUE; }
         delete phk;
      }
   }
   _retl(pl,b);
   unlock_hdict(cs);
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _HDICTCS_ISPROP( XppParamList pl )
{
   THtcsTable * pHt  = reinterpret_cast<THtcsTable *>( _parLong(pl,1) );
   void* cs = 0; cs = lock_hdict(pHt);
   BOOL b = FALSE;
   if( pHt )
   {
      THDictKey* phk  = THDictKey::FromPl(pl,2);
      if( phk )
      {
         THDictItem* phi = phk->Find( pHt );
         if( phi ){ b = TRUE; }
         delete phk;
      }
   }
   _retl(pl,b);
   unlock_hdict(cs);
}

// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _HDICT_GETPROP_RAW_( XppParamList pl )
{
   THashTable * pHt  = reinterpret_cast<THashTable *>( _parLong(pl,1) );
   void* cs = 0; cs = lock_hdict(pHt);
   if( pHt )
   {
      THDictKey* phk  = THDictKey::FromPl(pl,2);
      if( phk )
      {
         _retnl(pl,(LONG) phk->Find( pHt ) );
         delete phk;
         goto TheEnd;
      }
   }
   _retnl(pl,0);
   TheEnd:;
   unlock_hdict(cs);
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _HDICT_REMOVEPROP( XppParamList pl )
{
   THashTable * pHt  = reinterpret_cast<THashTable *>( _parLong(pl,1) );
   void* cs = 0; cs = lock_hdict(pHt);
   BOOL bOk = FALSE;
   if( pHt )
   {
      THDictKey* phk  = THDictKey::FromPl(pl,2);
      if( phk )
      {
         bOk = pHt->DeleteItem(phk->m_pKey , phk->m_cbKey);
         delete phk;
      }
   }
   _retl(pl,bOk);
   unlock_hdict(cs);
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _HDICTCS_REMOVEPROP( XppParamList pl )
{
   THtcsTable * pHt  = reinterpret_cast<THtcsTable *>( _parLong(pl,1) );
   void* cs = 0; cs = lock_hdict(pHt);
   BOOL bOk = FALSE;
   if( pHt )
   {
      THDictKey* phk  = THDictKey::FromPl(pl,2);
      if( phk )
      {
         bOk = pHt->DeleteItem(phk->m_pKey , phk->m_cbKey);
         delete phk;
      }
   }
   _retl(pl,bOk);
   unlock_hdict(cs);
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _HDICT_REMOVEALL( XppParamList pl )
{
   THashTable * pHt  = reinterpret_cast<THashTable *>( _parnl(pl,1) );
   void* cs = 0; cs = lock_hdict(pHt);
   if( pHt ) pHt->DeleteAllItems();
   _ret(pl);
   unlock_hdict(cs);
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _HDICTCS_REMOVEALL( XppParamList pl )
{
   THtcsTable * pHt  = reinterpret_cast<THtcsTable *>( _parnl(pl,1) );
   void* cs = 0; cs = lock_hdict(pHt);
   if( pHt ) pHt->DeleteAllItems();
   _ret(pl);
   unlock_hdict(cs);
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _HDICT_COUNT( XppParamList pl )
{
   THashTable * pHt  = reinterpret_cast<THashTable *>( _parnl(pl,1) );
   void* cs = 0; cs = lock_hdict(pHt);
   if( pHt ){ _retnl(pl,pHt->m_nCount); goto TheEnd;}
   _ret(pl);
   TheEnd:;
   unlock_hdict(cs);
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _HDICTCS_COUNT( XppParamList pl )
{
   THtcsTable * pHt  = reinterpret_cast<THtcsTable *>( _parnl(pl,1) );
   void* cs = 0; cs = lock_hdict(pHt);
   if( pHt ){ _retnl(pl,pHt->m_nCount); goto TheEnd;}
   _ret(pl);
   TheEnd:;
   unlock_hdict(cs);
}
// -----------------------------------------------------------------------------------------------------------------
//  5 parametro filtro _xgrab(  __i32(functionpointer,cb_string) + string ) asi salta los pasos que no hacen match
XPPRET XPPENTRY _HDICT_ITERATE_STEP( XppParamList pl ) // _HDICT_ITERATE_STEP( pHt, @pIterator , @xItem , @xKey [,pFilter] )
{
   THashTable * pHt  = reinterpret_cast<THashTable *>( _parnl(pl,1) );
   THashItem*   pItem  = reinterpret_cast<THashItem*>( _parnl(pl,2) );
   void* filter = reinterpret_cast<void*>( _parnl(pl,5,0) );
   LPSTR filter_string = 0;
   DWORD filter_cb     = 0;
   _PFN_HDICT_FILTER_ filter_fp = 0;
   if( pHt->m_cs_cargo )
   {
         TXbGenError e;
         e.subsystem( "OT4XB" );
         e.description("Operation not supported on Syncronized hash tables.");
         e.gencode(-1);
         e.operation( __FUNCTION__ );
         e.Launch();
         _ret(pl);
         return;
   }
   if( pHt )
   {

      if( !pItem ) pItem = pHt->m_pFirstItem;
      else pItem = pItem->m_pNext;

      if( filter && pItem  )
      {
         filter_fp = reinterpret_cast<_PFN_HDICT_FILTER_*>(filter)[0];
         filter_cb = reinterpret_cast<DWORD*>(filter)[1];
         filter_string = _mk_ptr_(LPSTR,filter,8);
         if( !(filter_fp && filter_string && filter_cb) ){ goto label_end_filter; }

         for( ; pItem ; pItem = pItem->m_pNext )
         {
            if( (*filter_fp)(pItem->m_pKey,pItem->m_cbKey,filter_string,filter_cb) )
            {
               goto label_end_filter;
            }
         }
      }
      label_end_filter: ;

      if( pItem )
      {
         THDictItem* phi = reinterpret_cast<THDictItem*>(pItem->m_pData);
         if( phi )
         {
            BOOL bByRef = 0;
            ContainerHandle conItem = _conParam(pl,3,&bByRef);
            if( conItem && bByRef ) phi->ConPutValue(conItem);
            if( !bByRef ) _conRelease(conItem);
         }
         else _stor(pl,3,0);
         _stornl((LONG) pItem,pl,2,0);
         _storclen(pItem->m_pKey,pItem->m_cbKey,pl,4,0);
         _retl(pl,1);
         return;
      }
   }
   _stor(pl,2,0);
   _stor(pl,3,0);
   _stor(pl,4,0);
   _retl(pl,0);
}
// -----------------------------------------------------------------------------------------------------------------
// _HDICT_ITERATE_CB( pHt, cb , @cargo){|pos,key,val,cargo|lContinue } -> nCount
// TODO: _HDICT_ITERATE_CB() document new extra usage of the second param
// _HDICT_ITERATE_CB( pHt, 1 ) -> aKeys
// _HDICT_ITERATE_CB( pHt, 2 ) -> aValues
// _HDICT_ITERATE_CB( pHt, 3 , [3 @hashstr] ) -> { {key1,value1},...,{keyN,valueN} }
// _HDICT_ITERATE_CB( pHt, 4 , @cb ) ->  LPSTR pEnvironment
// _HDICT_ITERATE_CB( pHt, 5 , default_value ) ->  ZKDW string
// _HDICT_ITERATE_CB( pHt, 6 , default_value ) ->  RESET ZKDW TO DEFAULT VALUE

// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _HDICT_ITERATE_CB( XppParamList pl )
{
   ULONG nOp = ( (_partype(pl,2) & XPP_NUMERIC) ? _parLong(pl,2,0) : 0 );
   THashTable * pHt  = reinterpret_cast<THashTable *>( _parnl(pl,1) );
   void* cs = 0; cs = lock_hdict(pHt);
   LONG nCount = 0;
   if( pHt )
   {
      switch( nOp )
      {
         case 0:
         {
            BOOL bBlockByRef = FALSE;
            ContainerHandle conb = _conTParam( pl,2,&bBlockByRef,XPP_BLOCK);
            if( conb )
            {
               BOOL bCargoByRef = FALSE;
               ContainerHandle conCargo = _conParam( pl,3,&bCargoByRef);
               ContainerHandle conPos   = _conNew(NULLCONTAINER);
               ContainerHandle conKey   = _conNew(NULLCONTAINER);
               ContainerHandle conValue = _conNew(NULLCONTAINER);
               ContainerHandle conr     = _conNew(NULLCONTAINER);
               THashItem* pItem = pHt->m_pFirstItem;
               while( pItem )
               {
                  BOOL bContinue = TRUE;
                  THDictItem* phi = reinterpret_cast<THDictItem*>(pItem->m_pData);
                  nCount++; _conPutNL(conPos,nCount);
                  _conPutCL(conKey,pItem->m_pKey,pItem->m_cbKey);
                  if( phi ) phi->ConPutValue(conValue); else _conPut(conValue,NULLCONTAINER);
                  _conEvalB(conr,conb,4,conPos,conKey,conValue,conCargo);
                  if( _conCheckType(conr, XPP_LOGICAL) ) _conGetL(conr,&bContinue);
                  if( bContinue ) pItem = pItem->m_pNext;
                  else pItem = 0;
               }
               _conReleaseM( conr,conPos,conKey,conValue,0);
               if(!bCargoByRef ) _conRelease( conCargo);
               if(!bBlockByRef ) _conRelease( conb );
            }
            break;
         }
         case 1: // array with keys
         {
            ContainerHandle cona = _conNewArray(1,pHt->m_nCount);
            THashItem* pItem = pHt->m_pFirstItem;
            while( pItem )
            {
               nCount++;
               _conArrayPutCL(cona,pItem->m_pKey,pItem->m_cbKey,nCount,0);
               pItem = pItem->m_pNext;
            }
            _conReturn(pl,cona);
            _conRelease(cona);
            goto TheEnd;
         }
         case 2: // array with values
         {
            ContainerHandle cona = _conNewArray(1,pHt->m_nCount);
            THashItem* pItem = pHt->m_pFirstItem;
            while( pItem )
            {
               THDictItem* phi = reinterpret_cast<THDictItem*>(pItem->m_pData);
               nCount++;
               if( phi )
               {
                  ContainerHandle con_value = phi->ConPutValue();
                  _conArrayPut(cona,con_value,nCount,0);
                  _conRelease( con_value );
               }
               pItem = pItem->m_pNext;
            }
            _conReturn(pl,cona);
            _conRelease(cona);
            goto TheEnd;
         }
         case 3: // array with { key,values}
         {
            ContainerHandle cona = _conNewArray(2,pHt->m_nCount,2);
            THashItem* pItem = pHt->m_pFirstItem;
            DWORD* pdwcrc = 0;

            if( _partype(pl,0) >= 3 )
            {
               pdwcrc = (DWORD*) _xgrab( (pHt->m_nCount + 1 ) * sizeof(DWORD) );
            }

            while( pItem )
            {
               THDictItem* phi = reinterpret_cast<THDictItem*>(pItem->m_pData);
               if( pdwcrc )
               {
                  pdwcrc[nCount] = pItem->m_dwCrc;
               }
               nCount++;
               _conArrayPutCL(cona,pItem->m_pKey,pItem->m_cbKey,nCount,1,0);
               if( phi )
               {
                  ContainerHandle con_value = phi->ConPutValue();
                  _conArrayPut(cona,con_value,nCount,2,0);
                  _conRelease( con_value );
               }
               pItem = pItem->m_pNext;
            }

            if( pdwcrc )
            {
               _storclen((LPSTR) pdwcrc, (ULONG) (pHt->m_nCount * sizeof(DWORD)),pl,3,0);
               _xfree( (void*) pdwcrc );
               pdwcrc = 0;
            }
            _conReturn(pl,cona);
            _conRelease(cona);
            goto TheEnd;
         }
         case 4: // -> LPSTR pEnvBlock
         {
            if( _partype(pl,0) < 3 ){ _ret(pl); goto TheEnd; }
            TByteStream z;
            THashItem* pItem = pHt->m_pFirstItem;
            DWORD dwzero = 0;
            while( pItem )
            {
               THDictItem* phi = reinterpret_cast<THDictItem*>(pItem->m_pData);
               if( phi )
               {
                  if( (phi->m_nDataType == THDictItem::hdi_str) && phi->m_dwDataSize )
                  {
                     z.Add( (LPBYTE) phi->m_pKey );
                     z.Add( (LPBYTE) &dwzero , 1 );
                     z.Add( (LPBYTE) phi->m_pData );
                     z.Add( (LPBYTE) &dwzero , 1 );
                  }
               }
               pItem = pItem->m_pNext;
            }
            z.Add( (LPBYTE) &dwzero , 4 );
            UINT cb = 0;
            LPBYTE p  = z.Detach(&cb);
            _stornl((LONG) cb,pl,3,0);
            _retnl(pl,(LONG) p );
            goto TheEnd;
         }
         case 5: // ZKDW string
         {
            TByteStream s(65536,65536);
            THashItem* pItem = pHt->m_pFirstItem;
            BOOL  bDefaultValue = ( _partype(pl,3) & XPP_NUMERIC );
            DWORD dwDefault = (DWORD) ( bDefaultValue ? _parLong(pl,3,0) : 0 );
            while( pItem )
            {
               THDictItem* phi = reinterpret_cast<THDictItem*>(pItem->m_pData);
               if( phi )
               {
                  switch( phi->m_nDataType )
                  {
                     case THDictItem::hdi_int :
                     {
                        s.append_DWORD( phi->m_dwExtra );
                        s.append_DWORD( phi->m_cbKey   );
                        s.Add( (LPBYTE) phi->m_pKey , phi->m_cbKey );
                        break;
                     }
                     case THDictItem::hdi_double:
                     {
                        double nd = 0.00;
                        if( (phi->m_dwDataSize == sizeof(double)) && phi->m_pData )
                        {
                           nd = reinterpret_cast<double*>( phi->m_pData )[0];
                        }
                        s.append_DWORD( phi->m_dwExtra );
                        s.append_DWORD( phi->m_cbKey   );
                        s.Add( (LPBYTE) phi->m_pKey , phi->m_cbKey );
                        break;
                     }
                     default:
                     {
                        if( bDefaultValue )
                        {
                           s.append_DWORD( dwDefault );
                           s.append_DWORD( phi->m_cbKey   );
                           s.Add( (LPBYTE) phi->m_pKey , phi->m_cbKey );
                           break;
                        }
                        break;
                     }
                  }

               }
               pItem = pItem->m_pNext;
            }
            ContainerHandle conr = _conPutCL( NULLCONTAINER , (LPSTR) s.GetBuffer() , s.len() );
            _conReturn(pl,conr);
            _conRelease(conr);
            goto TheEnd;
         }
         case 6: // reset ZKDW table
         {
            THashItem* pItem = pHt->m_pFirstItem;
            BOOL  bDefaultValue = ( _partype(pl,3) & XPP_NUMERIC );
            DWORD dwDefault = (DWORD) ( bDefaultValue ? _parLong(pl,3,0) : 0 );
            while( pItem )
            {
               THDictItem* phi = reinterpret_cast<THDictItem*>(pItem->m_pData);
               if( phi )
               {
                  if( phi->m_pData )
                  {
                     _xfree( phi->m_pData );
                     phi->m_pData = 0;
                  }
                  if( phi->m_nDataType == THDictItem::hdi_xbase && phi->m_dwExtra )
                  {
                     _conRelease( (ContainerHandle) phi->m_dwExtra );
                     phi->m_dwExtra = 0;
                  }
                  phi->m_pData       = 0;
                  phi->m_dwExtra     = dwDefault;
                  phi->m_nDataType   = THDictItem::hdi_int;
                  phi->m_dwDataSize  = sizeof(LONG);
               }
               pItem = pItem->m_pNext;
            }
            _ret(pl);
            goto TheEnd;
         }
      }
   }
   _retnl(pl,nCount);
   TheEnd: ;
   unlock_hdict(cs);
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _HDICT_ADDPROPFROMARRAY( XppParamList pl )
{
   TXppParamList xpp(pl,1);
   THashTable * pht  = reinterpret_cast<THashTable *>( xpp[1]->GetLong() );
   void* cs = 0; cs = lock_hdict(pht);
   if(pht && xpp[2]->CheckType(XPP_ARRAY) )
   {
      ContainerHandle cona = xpp[2]->Get();
      ULONG nItems = _conGetArrayLen(cona);
      ULONG n;
      for( n=1; n <= nItems; n++ )
      {
         ULONG nType = 0;
         _conTypeA(cona,&nType,n,0);
         if( nType & XPP_ARRAY )
         {
            ULONG nn = 0;
            _conSizeA(cona,&nn,n,0);
            if( nn > 0 )
            {
               THDictKey* phk  = 0;
               ContainerHandle con_k = _conNew(NULLCONTAINER);
               _conArrayGet(cona,con_k,n,1,0);
               phk  = THDictKey::FromXbItem(con_k);
               _conRelease(con_k);
               if( phk )
               {
                  THDictItem* phi = 0;
                  ContainerHandle con_v = _conNew(NULLCONTAINER);
                  if( nn > 1 ){ _conArrayGet(cona,con_v,n,2,0); }
                  phi = new THDictItem(phk,con_v);
                  if( phi ){phi->AddToHashTable(pht);}
                  delete phk;
                  _conRelease(con_v);
               }
            }
         }
      }
   }
   unlock_hdict(cs);
}
// -----------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_( _HDICT_ADD_HTTP_HEADERS )
{
   TXppParamList xpp(pl,1);
   THashTable * pht  = reinterpret_cast<THashTable *>( xpp[1]->GetLong() );
   void* cs = 0; cs = lock_hdict(pht);
   LPSTR p = xpp[2]->LockStrEx();
   if (pht && p)
   {

      LPSTR k = 0;
      DWORD kcb = 0;
      DWORD ksp = 0; // spaces after the key
      LPSTR v = 0;
      DWORD vcb = 0;
      DWORD vsp = 0; // spaces after the value
      int status = 0; // 0 CRLF; 1 key ; 2 value blank ; 3 value ; 4 invalid
      char ch = 0;

      for (; *p; p++)
      {
         switch (*p)
         {
         case 0x0A:;
         case 0x0D:
         {
            kcb = kcb - ksp; ksp = 0;
            vcb = vcb - vsp; vsp = 0;
            if (kcb)
            {
               if (!vcb) { v = &ch; }
               THDictItem* phi = new THDictItem(k, kcb, v, vcb, TRUE);
               phi->AddToHashTable(pht);
            }
            k = 0; kcb = 0; v = 0; vcb = 0;
            status = 0;
            break;
         }
         case 0x20:
         {
            switch (status)
            {
            case 0: { status = 1; k = p; kcb = 1; ksp = 1; v = 0; vcb = 0; break; }
            case 1: { kcb++; ksp++; break; }
            case 2: { vcb = 1; v = p; vsp = 0; break; }
            case 3: { vcb++; vsp++; break; }
            }
            break;


         }
         case ':':
         {
            kcb = kcb - ksp; ksp = 0;
            if (!kcb) { status = 0; }
            switch (status)
            {
            case 0: { status = 4; k = 0; kcb = 0; ksp = 0; v = 0; vcb = 0; vsp = 0; break; }
            case 1: { status = 2; vcb = 0; v = _mk_ptr_(LPSTR, p, 1); break; }
            case 2: { status = 3; vcb = 1; v = p; vsp = 0; break; }
            case 3: { vcb++; break; }
            }
            break;
         }
         default:
         {
            switch (status)
            {
            case 0: { status = 1; k = p; kcb = 1; ksp = 0; v = 0; vcb = 0; vsp = 0; break; }
            case 1: { ksp = 0; kcb++; break; }
            case 2: { status = 3; v = p; vcb = 1; vsp = 0; break; }
            case 3: { vsp = 0; vcb++; break; }
            }
            break;
         }
         }
      }
      if ((status > 0) && (status < 4))
      {
         kcb = kcb - ksp; ksp = 0;
         vcb = vcb - vsp; vsp = 0;
         if (kcb)
         {
            if (!vcb) { v = &ch; }
            THDictItem* phi = new THDictItem(k, kcb, v, vcb, TRUE);
            phi->AddToHashTable(pht);
         }
      }
   }
   unlock_hdict(cs);
}
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
///<xpp_function name="_hdict_AddPropFromIniString">
///<short>Add properties to a hash table using as input the content of an ini file</short>
///<proto>_hdict_AddPropFromIniString( ht , cIniStr, nFlags) -&gt; NIL</proto>
///<parameters>
///   <param name="ht">Handle of the hash table</param>
///   <param name="cIniStr">String to parse usually comming from an ini file</param>
///   <param name="nFlags">
///      0 - Ignore Section lines
///      1 - section\entry
///      2 - LTrim Values
///      4 - ReturnSectionArray // flag 1 is also required
///   </param>
///</parameters>
///</xpp_function>
_XPP_REG_FUN_( _HDICT_ADDPROPFROMINISTRING ) // _hdict_AddPropFromIniString( ht, cIniStr , nFlags)
{

   TXppParamList xpp(pl,3);
   THashTable * pht  = reinterpret_cast<THashTable *>( xpp[1]->GetLong() );
   void* cs = 0; cs = lock_hdict(pht);
   DWORD dwFlags = xpp[3]->GetDWord();
   TList* pSectionList = 0;
   if( (dwFlags & 5) == 5 )
   {
      pSectionList = new TList;
   }


   if(pht && xpp[2]->CheckType(XPP_CHARACTER) )
   {
      LPSTR  pStr  = xpp[2]->StrDupA();
      TList* pList = TxtSplitLinesToTList(pStr,0x13);
      if( pList )
      {
         BYTE bt[256]; ZeroMemory(bt,256);
         bt[9] = bt[10] = bt[13] = bt[32] = 1;
         LPSTR pLastSection = 0;
         DWORD cbLastSection = 0;
         DWORD nCount = pList->Count();
         DWORD nItem;
         for( nItem = 0; nItem < nCount ; nItem++ )
         {
            LPSTR k = (LPSTR) pList->Get(nItem);
            if( k[0] == '[' )
            {
               if( dwFlags & 1 )
               {
                  k++;
                  DWORD cb = _xstrlen(k);
                  DWORD n = _bscan((LPBYTE) k , cb , (BYTE) ']' );
                  if( n < cb )
                  {
                     k[n] = 0;
                     cb = n;
                  }
                  cb = ByteMapTable_RTrimEx(bt,(LPBYTE)k,cb);
                  cb = ByteMapTable_LTrimEx(bt,(LPBYTE)k,cb);
                  _bcopy((LPBYTE) pStr, (LPBYTE) k , cb );
                  if( pSectionList )
                  {
                     pStr[cb] = 0;
                     pSectionList->Add( (void*) _xstrdup(pStr) );
                  }
                  pStr[cb] = '\\';
                  pLastSection = pStr;
                  cbLastSection = cb+1;
               }
            }
            else if( k[0] != ';' )
            {


               LPSTR v   = 0;
               DWORD cbv = 0;
               DWORD cbk = _xstrlen(k);
               DWORD n  = _bscan((LPBYTE) k , cbk , (BYTE) '=' );
               if( n < cbk )
               {
                  cbk   = n;
                  k[cbk] = 0;
                  v = _mk_ptr_( LPSTR,k,n+1);
                  if( dwFlags & 2 )
                  {
                     cbv = ByteMapTable_RTrimEx(bt,(LPBYTE)v,(DWORD) -1);
                     cbv = ByteMapTable_LTrimEx(bt,(LPBYTE)v,cbv);
                  }
                  else
                  {
                     cbv = _xstrlen(v);
                  }
               }
               if( cbk )
               {
                  cbk = ByteMapTable_RTrimEx(bt,(LPBYTE)k,cbk);
                  cbk = ByteMapTable_LTrimEx(bt,(LPBYTE)k,cbk);
               }

               if( pLastSection && cbk )
               {
                  _bcopy( _mk_ptr_( LPBYTE , pLastSection,cbLastSection) ,(LPBYTE)  k ,cbk + 1 );
                  k = pLastSection;
                  cbk += cbLastSection;
               }
               if( !v)
               {
                  n = 0;
                  v = _mk_ptr_(LPSTR,&n,0);
                  cbv = 0;
               }
               if( cbk )
               {

                  THDictItem* phi = new THDictItem(k,cbk,v,cbv,TRUE);
                  phi->AddToHashTable( pht);
               }
            }
         }
         delete pList;
      }
      _xfree( (void*) pStr );
   }
   unlock_hdict(cs);
   if( pSectionList )
   {
      xpp[0]->PutNewArray(1,pSectionList,0);
      DWORD dwCount = pSectionList->Count();
      DWORD dw;
      for( dw=0; dw < dwCount; dw++ )
      {
         LPSTR p = (LPSTR) pSectionList->Replace(dw,0);
         if( p )
         {
            _conArrayPutC(xpp[0]->con(),p,dw+1,0);
            _xfree( (void*) p ); p = 0;
         }
      }
      delete pSectionList;
      pSectionList = 0;
   }

}
// -----------------------------------------------------------------------------------------------------------------
BEGIN_XBASE_CLASS( THDICTEX )
{
   pc->EXPORTED();
   pc->Var("m_23D7C8B01AF14A059D83551121621B91");
   pc->MethodCB("h","{|s| s:m_23D7C8B01AF14A059D83551121621B91 }");
   pc->MethodCB("handle","{|s| s:m_23D7C8B01AF14A059D83551121621B91 }");
   pc->MethodCB("init"       ,"{|s,lSync| s:m_23D7C8B01AF14A059D83551121621B91 := _hdict_new(@s:m_23D7C8B01AF14A059D83551121621B91,NIL,NIL,lSync),s}");
   pc->MethodCB("destroy"    ,"{|s| _HDICT_DESTROY(s:h()) , s:m_23D7C8B01AF14A059D83551121621B91 := NIL}");
   pc->MethodCB("SetProp"   ,"{|s,k,v| _HDICT_SETPROP(s:h(),k,v) }");
   pc->MethodCB("GetProp"   ,"{|s,k| _HDICT_GETPROP(s:h(),k) }");
   pc->MethodCB("SetNoIVar"  ,"{|s,k,v| _HDICT_SETPROP(s:h(),k,v) }");
   pc->MethodCB("GetNoIVar"  ,"{|s,k| _HDICT_GETPROP(s:h(),k) }");
   pc->MethodCB("IsProp"     ,"{|s,k| _HDICT_ISPROP(s:h(),k) }");
   pc->MethodCB("RemoveProp" ,"{|s,k| _HDICT_REMOVEPROP(s:h(),k) }");
   pc->MethodCB("RemoveAll"  ,"{|s| _HDICT_REMOVEALL(s:h()) }");
   pc->MethodCB("Count"      ,"{|s| _HDICT_COUNT(s:h()) }");
   pc->MethodCB("AddFromArray"     ,"{|s,aData| _HDICT_ADDPROPFROMARRAY(s:h(),aData) }");
   pc->MethodCB("AddFromIniString" ,"{|s,cStr,flags| _HDICT_ADDPROPFROMINISTRING(s:h(),cStr,flags) }");
   pc->MethodCB("AddEnvStrings" ,"{|s,pEnv| _HDICT_ADD_ENV_STRINGS(s:h(),pEnv) }");
   pc->MethodCB("AddHttpHeaders" ,"{|s,cStr| _HDICT_ADD_HTTP_HEADERS(s:h(),cStr,flags) }");
   pc->MethodCB("ToArray" ,"{|s| _HDICT_ITERATE_CB(s:h(),3) }");
   pc->MethodCB("FromZkdw" ,"{|s,zkdw| _HDICT_FROM_ZKDW(s:h(),zkdw) }");
   pc->MethodCB("ToZkdw" ,"{|s,defval| _HDICT_ITERATE_CB(s:h(),5,defval) }");
   pc->MethodCB("ResetZkdw" ,"{|s,defval| _HDICT_ITERATE_CB(s:h(),6,defval) }");
}
END_XBASE_CLASS
//----------------------------------------------------------------------------------------------------------------------
