//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
// Node Token API
//------------------------------------------------------------
#include <ot4xb_api.h>
// -----------------------------------------------------------------------------------------------------------------
#define NDTK_MAX_CB    4096
// -----------------------------------------------------------------------------------------------------------------
extern "C" LPVOID OT4XB_API ndtk_new(void){ return _xgrab(NDTK_MAX_CB);}
extern "C" void  OT4XB_API ndtk_delete(void* p){ _xfree(p);}
// -----------------------------------------------------------------------------------------------------------------
extern "C" LONG OT4XB_API ndtk_get_depth(LPSTR pRoot)
{
   ULONG nLevel = 0;
   if( !*pRoot ) return -1;
   for( ; *pRoot; pRoot++ ){ if( *pRoot == '\\' ){ nLevel++; } }
   return nLevel;
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" BOOL OT4XB_API ndtk_set_depth(LPSTR pRoot , LONG nLevel)
{
   LONG  nn = 0;
   if( nLevel < 0 ){  *pRoot = 0; return TRUE; }
   if( !*pRoot ) return 0;
   for( ; *pRoot; pRoot++ ){if( *pRoot == '\\' ){nn++; if( nn == nLevel ){*pRoot = 0;return TRUE;}}}
   return FALSE;
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" void OT4XB_API ndtk_dec_depth(LPSTR pRoot)
{
   LPSTR pLast = pRoot;
   if( !*pRoot ) return;
   for( ; *pRoot; pRoot++ ){if( *pRoot == '\\' ){pLast = pRoot;}}
   *pRoot = 0;
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" void OT4XB_API ndtk_add(LPSTR pRoot , LPSTR pNode)
{
   ULONG cb = _xstrlen(pRoot);
   if(!pNode) return;
   if(!(*pNode)) return;
   if(cb){pRoot[cb] = '\\'; cb++; pRoot[cb] = 0;}
   for( ; *pNode; pNode++ ){pRoot[cb] = *pNode; cb++; pRoot[cb] = 0;}
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" BOOL OT4XB_API ndtk_ischild(LPSTR pParent , LPSTR pChild , BOOL* pbIdentical )
{
   UINT cbp = _xstrlen(pParent);
   UINT cbc = _xstrlen(pChild);
   BOOL bIdentical = 0;
   if( !pbIdentical ) pbIdentical = &bIdentical;
   pbIdentical[0] = FALSE;
   if( cbp >  cbc ) return FALSE;
   if( cbp == cbc )
   {
      pbIdentical[0] = (BOOL) (_bcmp((LPBYTE) pParent , (LPBYTE) pChild , cbp) == 0);
      return pbIdentical[0];
   }
   pbIdentical[0] = FALSE;
   if( pChild[cbp] == '\\'){ return (BOOL) (_bcmp((LPBYTE) pParent , (LPBYTE) pChild , cbp) == 0);}
   return FALSE;
}
//----------------------------------------------------------------------------------------------------------------------


