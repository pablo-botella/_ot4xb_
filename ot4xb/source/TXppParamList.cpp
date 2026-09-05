//------------------------------------------------------------
// Project: Open Tools for Xbase++ -
// Repository : http://www.xbwin.com -
// Author: Pablo Botella Navarro ( http://www.xbwin.com ) -
//------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
TXppParamList::TXppParamList( XppParamList pl , ULONG nFormalCount )
{
   m_pl            = pl;
   m_nPCount       = (pl ? _partype(pl,0) : 0 );
   if( nFormalCount < m_nPCount ) nFormalCount = m_nPCount;
   m_nFormalCount  = nFormalCount;
   m_nCapacity     = m_nFormalCount + 1;   
   m_pItems    = (TXbCPItem **) _xgrab( m_nCapacity * sizeof(TXbCPItem*) );
   m_pItems[0] = new TXbCPItem();
   m_pItems[0]->m_pl = pl;
   m_pItems[0]->m_nRealPosition = 0;
   m_pItems[0]->m_con = _conNew(NULLCONTAINER);
   m_pItems[0]->m_bInit  = TRUE;   
}
//----------------------------------------------------------------------------------------------------------------------
TXppParamList::~TXppParamList( void )
{
   ULONG n;
   TXbCPItem* p = 0;
   for( n = 1; n < m_nCapacity; n++ )
   {
      p = m_pItems[n]; m_pItems[n] = 0;
      if( p ){ delete p; }
   }
   p = m_pItems[0];  m_pItems[0] = 0;      
   if( p )
   {
      p->UnLockStrEx(); // TODO: check this also!!!
      if( m_pl ){ _conReturn(m_pl,p->m_con);}
      delete p;
   }
   else { if( m_pl ){ _ret(m_pl); }}
   _xfree( (void*) m_pItems );
}
//----------------------------------------------------------------------------------------------------------------------
TXbCPItem* TXppParamList::operator[]( int n )
{
   return _get_( (ULONG) n );
}         
// -----------------------------------------------------------------------------------------------------------------
void TXppParamList::init_formal_params(void)
{
   UINT n;
   for( n = 0; n <= m_nFormalCount; n++){ _get_(n)->con(); }
}
// -----------------------------------------------------------------------------------------------------------------
TXbCPItem* TXppParamList::_get_(ULONG n)
{
   if( ((int) n) < 0 )
   {
      n = (ULONG) (((int) m_nFormalCount) - ((int) n) );
   }
   if( n >= m_nCapacity )
   {
      ULONG nn = (n | 15);
      m_pItems = (TXbCPItem**) _xxgrowa((void*)m_pItems,m_nCapacity,nn+1,sizeof(TXbCPItem*));
      m_nCapacity = nn;
   }
   if( !m_pItems[n] )
   {
      m_pItems[n] = (( n > m_nPCount) ? (new TXbCPItem()) : ( new TXbCPItem(m_pl,n) ));
   }
   return m_pItems[n];
}
// -----------------------------------------------------------------------------------------------------------------
ULONG TXppParamList::PCount(void){ return m_nPCount; }
//----------------------------------------------------------------------------------------------------------------------
DWORD TXppParamList::Eval(UINT nParams)
{
   DWORD result = INFINITE;
   if( _get_(1)->CheckType( XPP_BLOCK ) )
   {
      UINT n;
      ContainerHandle* pcon = (ContainerHandle*) _xgrab(nParams * sizeof(ContainerHandle));
      for( n = 0 ; n < nParams; n++ ){pcon[n] = _get_(n+2)->con();}
      result = _conEvalBa(_get_(0)->con(),_get_(1)->con(),nParams,pcon);
      _xfree(pcon);
   }
   return result;
}
// -----------------------------------------------------------------------------------------------------------------
