//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
// -----------------------------------------------------------------------------------------------------------------
THDictKey::THDictKey(LPSTR pKey, DWORD cb, BOOL bDup)
{
   if( cb == -1 )
   {
      cb = _xstrlen(pKey);
   }
   if( bDup )
   {
    
      m_pKey = (LPSTR) _xgrab(cb+1);
      m_cbKey = cb;   
      _bcopy((LPBYTE) m_pKey,(LPBYTE) pKey,cb);
   }
   else
   {
      m_pKey = pKey;
      m_cbKey = cb;
   }
}
// -----------------------------------------------------------------------------------------------------------------
THDictKey::~THDictKey(void){ if(m_pKey ){ _xfree((void*) m_pKey );} m_pKey = 0; m_cbKey=0;}
// -----------------------------------------------------------------------------------------------------------------
THDictKey* THDictKey::FromPl( XppParamList pl , ULONG np)
{
   BOOL            bByRef = FALSE;
   ContainerHandle con    = _conParam(pl,np,&bByRef);
   THDictKey*      pdk    = THDictKey::FromXbItem(con);
   if(!bByRef) _conRelease(con);
   return pdk;
}
// -----------------------------------------------------------------------------------------------------------------
THDictKey* THDictKey::FromXbItem(ContainerHandle con)
{
   DWORD cb   = 0;
   LPSTR pKey = THDictKey::XbItemToPointer(con,&cb);
   if( pKey ) return new THDictKey(pKey,cb);
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
LPSTR THDictKey::XbItemToPointer(ContainerHandle con, DWORD * pcb )
{
   LPSTR pKey = 0;
   pcb[0] = 0;
   if( con )
   {
      ULONG ulType = 0;
      _conType(con,&ulType);
      switch( ulType & 0xFF )
      {
         case XPP_NUMERIC:
         {
            LONG  n = 0;
            _conGetLong(con,&n);
            pKey = (LPSTR) _xgrab(16);
            pcb[0] = wsprintf(pKey,"int_%lx",n);
            return pKey;
         }
         case XPP_DATE:
         {
            char szd[9];
            ZeroMemory(szd,9);
            _conGetDS(con,pKey);
            pKey = (LPSTR) _xgrab(16);
            pcb[0] = wsprintf(pKey,"date_%s",szd);
            return pKey;
         }
         case XPP_CHARACTER:
         {                      
            ULONG ul = 0;
            _conSizeC(con,pcb);
            pKey = (LPSTR) _xgrab(pcb[0] + 1 );
            _conGetCL(con,&ul,(LPSTR)pKey,(pcb[0] + 1 ));
            return pKey;
         }
      }
   }
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
THDictItem* THDictKey::Find(THashTable* pht){ return reinterpret_cast<THDictItem*>( pht->FindItem(m_pKey,m_cbKey));}     
THDictItem* THDictKey::Find(THtcsTable* pht){ return reinterpret_cast<THDictItem*>( pht->FindItem(m_pKey,m_cbKey));}     
// -----------------------------------------------------------------------------------------------------------------
THDictItem::THDictItem( LPSTR pKey , UINT cbKey , LPSTR pData , UINT cbData , BOOL bDup)
{
   m_dwExtra = 0;       
   m_nDataType   = hdi_str;   
   if( cbKey == (UINT) -1 ) cbKey  = _xstrlen(pKey);
   m_cbKey       = cbKey;   
   if( cbData == (UINT) -1 ) cbData = _xstrlen(pData);   
   m_dwDataSize  = cbData;   
   if( bDup)
   {
      m_pKey  = (LPSTR) _xgrab( cbKey  + 1 ); _bcopy((LPBYTE)m_pKey,(LPBYTE)pKey,cbKey);
      m_pData = (LPSTR) _xgrab( cbData + 1 ); _bcopy((LPBYTE)m_pData,(LPBYTE)pData,cbData);      
   }
   else
   {
      m_pKey  = pKey;
      m_pData = pData;
   }
}
// -----------------------------------------------------------------------------------------------------------------
THDictItem::THDictItem( THDictKey* pdk, ContainerHandle conData)
{
   ULONG ul = 0;
   m_pData = 0; m_dwExtra = 0; m_dwDataSize  = 0;
   m_pKey  = pdk->m_pKey ; pdk->m_pKey  = 0;
   m_cbKey = pdk->m_cbKey; pdk->m_cbKey = 0;
   
   if( conData ) _conType(conData,&ul);
   else ul = XPP_UNDEF;

   if( ul & XPP_UNDEF )
   {
      m_nDataType  = hdi_empty;
      return;
   }
   if( ul & XPP_DATE )
   {
      m_nDataType  = hdi_xdate;
      m_dwDataSize = 8;
      m_pData = _xgrab(8);
      _conGetDS(conData,(LPSTR)m_pData);
      return;
   }
   if( ul & XPP_CHARACTER )
   {
      m_nDataType = hdi_str;
      _conSizeC(conData,&m_dwDataSize);
      m_pData = _xgrab(m_dwDataSize+1);
      ul = 0;
      _conGetCL(conData,&ul,(LPSTR)m_pData,m_dwDataSize+1);
      return;
   }
   if( (ul & XPP_NUMERIC) && (ul & _xpp_DOUBLE) )
   {
      m_nDataType = hdi_double;
      m_dwDataSize = sizeof(double);
      m_pData = _xgrab(m_dwDataSize);
      _conGetND(conData,(double*) m_pData);
      return;
   }
   if( ul & XPP_NUMERIC )
   {
      m_nDataType = hdi_int;
      m_dwDataSize = sizeof(LONG);
      _conGetNL(conData,(LONG*) &m_dwExtra);
      return;
   }
   if( ul & XPP_LOGICAL )
   {
      m_nDataType = hdi_bool;
      m_dwDataSize = sizeof(BOOL);
      _conGetL(conData,(BOOL*) &m_dwExtra);
      return;
   }
   m_nDataType = hdi_xbase;
   m_dwExtra   = (DWORD) _conNew( conData );
}
// -----------------------------------------------------------------------------------------------------------------
THDictItem::THDictItem( LPSTR pKey , UINT cbKey , DWORD value , BOOL bDup)
{
   m_pData = 0;
   m_dwDataSize = sizeof(LONG);   
   m_nDataType   = hdi_int;   
   m_dwExtra = value;   
   if( cbKey == (UINT) -1 ) cbKey  = _xstrlen(pKey);
   m_cbKey       = cbKey;   
   if( bDup)
   {
      m_pKey  = (LPSTR) _xgrab( cbKey  + 1 ); _bcopy((LPBYTE)m_pKey,(LPBYTE)pKey,cbKey);
   }
   else
   {
      m_pKey  = pKey;
   }
}
// -----------------------------------------------------------------------------------------------------------------
THDictItem::~THDictItem(void)
{
   switch ( m_nDataType )
   {
      case hdi_double: { if( m_pData){ _xfree( m_pData);} break;}
      case hdi_xdate : { if( m_pData){ _xfree( m_pData);} break;}
      case hdi_str   : { if( m_pData){ _xfree( m_pData);} break;}
      case hdi_xbase : { if( m_dwExtra ){_conRelease( (ContainerHandle) m_dwExtra);} break;}
   }
   if( m_pKey ){ _xfree((void*) m_pKey );}
   m_pKey = 0; m_cbKey=0;m_dwDataSize = 0; m_nDataType = hdi_empty; m_pData = 0; m_dwExtra = 0;
}
// -----------------------------------------------------------------------------------------------------------------
void __stdcall THDictItem::_OnDestroyItem_( void* p , DWORD){if(p) delete reinterpret_cast<THDictItem*>(p);}
// -----------------------------------------------------------------------------------------------------------------
ContainerHandle THDictItem::ConPutValue( ContainerHandle con )
{
   switch ( m_nDataType )
   {
      case hdi_empty : { return _conPut(con,NULLCONTAINER);}
      case hdi_bool  : { return _conPutL(con,(BOOL) m_dwExtra);}
      case hdi_int   : { return _conPutNL( con , (LONG) m_dwExtra);}
      case hdi_double: { return _conPutND( con , reinterpret_cast<double*>(m_pData)[0]);}
      case hdi_xdate : { return _conPutDS( con , (LPSTR) m_pData);}
      case hdi_str   : { return _conPutCL( con , (LPSTR) m_pData , m_dwDataSize);}
      case hdi_xbase : { return _conPut(con,reinterpret_cast<ContainerHandle>(m_dwExtra));}
   }
   return _conPut(con, NULLCONTAINER);
}
// -----------------------------------------------------------------------------------------------------------------
void THDictItem::AddToHashTable( THashTable* pht ){if( pht ) pht->InsertItem(m_pKey,m_cbKey,(void*) this , TRUE);}
void THDictItem::AddToHashTable( THtcsTable* pht ){if( pht ) pht->InsertItem(m_pKey,m_cbKey,(void*) this , TRUE);}
// -----------------------------------------------------------------------------------------------------------------

