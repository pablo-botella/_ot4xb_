//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
// -----------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_( TOKENIZEEX ) // TokenizeEx( str, aSep , nFlags ) -> aToken
{
   TokenizeEx_t k;
   k.run_xbase(pl);
}
//----------------------------------------------------------------------------------------------------------------------
TokenizeEx_t::separator_t::separator_t(LPBYTE str, int cb)
{
   m_str = 0; m_cb = 0;
   if( str && (cb > 0 ) )
   {
      m_cb  = (UINT) cb;
      m_str = _bdup(str,m_cb);
   }
}
// -----------------------------------------------------------------------------------------------------------------
TokenizeEx_t::separator_t::~separator_t(void)
{
   if( m_str ){ _xfree((void*) m_str ); m_str = 0; }
   m_cb = 0;
}
// -----------------------------------------------------------------------------------------------------------------
BOOL TokenizeEx_t::separator_t::test(LPBYTE p, int cb)
{
   if( p && (cb > 0) && (cb >= m_cb) && m_str )
   {
      int n;
      for( n=0; n < m_cb; n++ ){ if( p[n] != m_str[n]){ return FALSE; } }
      return TRUE;
   }
   return FALSE;
}
// -----------------------------------------------------------------------------------------------------------------
TokenizeEx_t::item_t::item_t(LPBYTE start , int cb ){ m_start = start; m_cb = cb; }
// -----------------------------------------------------------------------------------------------------------------
TokenizeEx_t::TokenizeEx_t(void)
{
   m_sep_list  = new TList;
   m_item_list = new TList;   
   m_buffer    = 0;
   m_cb        = 0;
}
// -----------------------------------------------------------------------------------------------------------------
TokenizeEx_t::~TokenizeEx_t(void)
{
   if( m_sep_list )
   {
      UINT n,nn;
      for( n=0,nn=m_sep_list->Count();n<nn;n++ )
      {
         separator_t* sep = (separator_t*) m_sep_list->Replace(n,0);
         if( sep ){ delete sep; }
      }
      delete m_sep_list;
      m_sep_list = 0;
   }
   FreeBuffer();
   if( m_item_list )
   {
      delete m_item_list;
      m_item_list = 0;   
   }
}
// -----------------------------------------------------------------------------------------------------------------
void TokenizeEx_t::ClearItemList(void)
{
   if( m_item_list )
   {
      UINT n,nn;
      for( n=0,nn=m_item_list->Count();n<nn;n++ )
      {
         item_t* item = (item_t*) m_item_list->Replace(n,0);
         if( item ){ delete item; }
      }
      m_item_list->Truncate(0);
   }   
}
// -----------------------------------------------------------------------------------------------------------------
void TokenizeEx_t::FreeBuffer(void)
{
   ClearItemList();
   if( m_buffer ){ _xfree((void*) m_buffer); m_buffer = 0; }
   m_cb = 0;
}
// -----------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------
void TokenizeEx_t::SetBuffer( LPBYTE buffer , int cb )
{
   FreeBuffer();
   if( buffer && (cb > 0) )
   {
      m_buffer = _bdup(m_buffer,(UINT) cb);
      m_cb = (UINT) cb;
   }
}
// -----------------------------------------------------------------------------------------------------------------
void TokenizeEx_t::AddSeparator( LPBYTE s , int cb )
{
   if( s && (cb > 0) )
   {
      m_sep_list->Add( (void*) ( new separator_t(s,cb) ) );
   }
}
// -----------------------------------------------------------------------------------------------------------------
int TokenizeEx_t::test_sep( LPBYTE p , int cb )
{
   if( p && ( cb > 0 ) && m_sep_list )
   {
      UINT n,nn;
      for( n=0,nn=m_sep_list->Count();n<nn;n++ )
      {
         separator_t* sep = (separator_t*) m_sep_list->Get(n);
         if( sep->test(p,cb) ){ return sep->m_cb; }
      }
   }
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
void TokenizeEx_t::run(void)
{
   ClearItemList();
   if( m_buffer && m_cb && m_sep_list )
   {
      LPBYTE  p  = m_buffer;
      int     cb = m_cb;
      item_t* item = new item_t(p,0);
      m_item_list->Add( (void*) item );
      
      while( cb > 0 )
      {
         int cbs = test_sep(p,cb);
         if( cbs > 0 )
         {
            cb -= cbs; p = _mk_ptr_(LPBYTE,p,cbs);
            item = new item_t(p,0);
            m_item_list->Add( (void*) item );
         }
         else
         {
            item->m_cb++;
            p++; cb--;
         }
      }
   }
}
// -----------------------------------------------------------------------------------------------------------------
void TokenizeEx_t::SetBuffer( XppParamList pl , ULONG nParam)
{
   FreeBuffer();
   if( pl && nParam )
   {
      if( _partype(pl,nParam) & XPP_CHARACTER )
      {
         m_cb = (ULONG) _parclen(pl,nParam,0);
         if( m_cb == 0 ){ return; }
         m_buffer = (LPBYTE) _xgrab((UINT) m_cb+1);
         _parc((LPSTR) m_buffer,((UINT) m_cb+1),pl,nParam,0);
      }
   }
}
// -----------------------------------------------------------------------------------------------------------------
void TokenizeEx_t::run_xbase( XppParamList pl )
{
   SetBuffer(pl,1);
   if( _partype(pl,2) & XPP_ARRAY )
   {
      BOOL bByRef = FALSE;
      ContainerHandle cona = _conParam(pl,2,&bByRef);
      ULONG nn = _conGetArrayLen(cona);
      ULONG n;
      for( n=1; n<= nn; n++ )
      {
         ContainerHandle con = _conNew(NULLCONTAINER); 
         _conArrayGet(cona,con,n,0);
         LPSTR  p  = 0;
         ULONG   cb = 0;
         if( ot4xb_conRLockC(con,&p,&cb) == 0 )
         {
            AddSeparator((LPBYTE) p,(int) cb);
            ot4xb_conUnlockC(con);
         }
         _conRelease(con);
      }
      if( !bByRef ){ _conRelease(cona); }
      cona = 0;
   }
   else
   {
      BOOL bByRef = FALSE;
      ContainerHandle con = _conTParam(pl,2,&bByRef,XPP_CHARACTER);
      if( con )
      {
         LPSTR  p  = 0;
         ULONG   cb = 0;
         if( ot4xb_conRLockC(con,&p,&cb) == 0 )
         {
            AddSeparator((LPBYTE) p,(int) cb);
            ot4xb_conUnlockC(con);
         }
         if( !bByRef){ _conRelease(con); }
      }
   }
   run();
   ULONG nn = m_item_list->Count();
   ContainerHandle cona = _conNewArray(1,nn);
   ULONG n;
   for( n=0; n < nn; n++ )
   {
      ContainerHandle con = _conPutC(NULLCONTAINER,"");
      item_t* item = (item_t*) m_item_list->Get(n);
      if( item )
      {
         if( (item->m_cb > 0) && item->m_start )
         {
            _conPutCL(con,(LPSTR) item->m_start , (ULONG) item->m_cb );
         }
      }
      _conArrayPut(cona,con,n+1,0);
      _conRelease(con);
      con = 0;
   }
   _conReturn(pl,cona);
   _conRelease(cona);
}
// --------------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_( __AJOIN ) // __ajoin( array , delimiter )
{
   TXppParamList xpp( pl, 2 );
   TZString s( 1024 );

   if( xpp[ 1 ]->CheckType( XPP_ARRAY ) )
   {
      ULONG item_count = xpp[ 1 ]->con_size();
      if( item_count )
      {
         char default_delimiter[ ] = ",";
         LPSTR delimiter = ( xpp[ 2 ]->CheckType( XPP_CHARACTER ) ? xpp[ 2 ]->LockStr() : default_delimiter );
         ContainerHandle con = _conNew( NULLCONTAINER );
         DWORD dw = 0;
         for( ULONG item_pos = 1; item_pos <= item_count; item_pos++ )
         {
            if( _conArrayGet( xpp[ 1 ]->con(), con, item_pos, 0 ) )
            {
               DWORD cb = 0;
               LPSTR p = 0;
               if( !_conRLockC( con, &p, &cb ) )
               {
                  if(dw)
                  {
                     s += delimiter;
                  }
                  s += p;
                  _conUnlockC( con );
                  p = 0;
                  dw++;
               }
            }
         }
         _conRelease( con );
         con = NULLCONTAINER;
      }
   }
   xpp[ 0 ]->PutStr( s.GetBuffer() );

}


