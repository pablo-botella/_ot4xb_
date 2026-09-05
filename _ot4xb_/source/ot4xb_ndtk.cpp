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
/*{{begin-c-function}}*/
/*{{c-function_: ndtk_new
            | syntax_: `void * ndtk_new( void )`
            | category: c-api/node-token
            | header: ot4xb_c_exported.h
            | mangled-name: ndtk_new
            | _kw_: node token, node path, tree path, backslash path
   }}*/
/*{{|desc: Creates a node token path: a text buffer that identifies a node inside a tree by listing the
      node names from the root separated by backslashes, like `a\b\c`. The buffer is 4096 bytes and comes
      zero filled, so the path starts empty. Release it with ndtk_delete.

    Returns void * - Pointer to the new path buffer, ready to fill with ndtk_add. }}*/
extern "C" LPVOID OT4XB_API ndtk_new(void){ return _xgrab(NDTK_MAX_CB);}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ndtk_delete
            | syntax_: `void ndtk_delete( void * p )`
            | category: c-api/node-token
            | header: ot4xb_c_exported.h
            | mangled-name: ndtk_delete
            | _kw_: node token, node path, release
   }}*/
/*{{|desc: Releases a node token path buffer created with ndtk_new.
    | params:
    - `p` void * - Path buffer returned by ndtk_new.

    Returns void }}*/
extern "C" void  OT4XB_API ndtk_delete(void* p){ _xfree(p);}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ndtk_get_depth
            | syntax_: `LONG ndtk_get_depth( LPSTR pRoot )`
            | category: c-api/node-token
            | header: ot4xb_c_exported.h
            | mangled-name: ndtk_get_depth
            | _kw_: node token, depth, nesting level, path
   }}*/
/*{{|desc: Returns the depth of a node token path, counting its backslash separators: 0 for a single
      name, 1 for `a\b`, and so on. An empty path returns -1.
    | params:
    - `pRoot` LPSTR - Zero terminated node token path to inspect.

    Returns LONG - Number of separators in the path, or -1 when the path is empty. }}*/
extern "C" LONG OT4XB_API ndtk_get_depth(LPSTR pRoot)
{
   ULONG nLevel = 0;
   if( !*pRoot ) return -1;
   for( ; *pRoot; pRoot++ ){ if( *pRoot == '\\' ){ nLevel++; } }
   return nLevel;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ndtk_set_depth
            | syntax_: `BOOL ndtk_set_depth( LPSTR pRoot, LONG nLevel )`
            | category: c-api/node-token
            | header: ot4xb_c_exported.h
            | mangled-name: ndtk_set_depth
            | _kw_: node token, truncate path, depth, parent path
   }}*/
/*{{|desc: Truncates a node token path in place at its nLevel-th backslash separator, keeping only the
      first nLevel node names. A negative nLevel empties the path; nLevel 0 does nothing (use a negative
      value to empty the path).
    | params:
    - `pRoot` LPSTR - Zero terminated node token path, modified in place.
    - `nLevel` LONG - Number of node names to keep; a negative value empties the path.

    Returns BOOL - TRUE when the path was cut or emptied; FALSE when it is empty or does not have more
      than nLevel names, in which case it is left unchanged. }}*/
extern "C" BOOL OT4XB_API ndtk_set_depth(LPSTR pRoot , LONG nLevel)
{
   LONG  nn = 0;
   if( nLevel < 0 ){  *pRoot = 0; return TRUE; }
   if( !*pRoot ) return 0;
   for( ; *pRoot; pRoot++ ){if( *pRoot == '\\' ){nn++; if( nn == nLevel ){*pRoot = 0;return TRUE;}}}
   return FALSE;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ndtk_dec_depth
            | syntax_: `void ndtk_dec_depth( LPSTR pRoot )`
            | category: c-api/node-token
            | header: ot4xb_c_exported.h
            | mangled-name: ndtk_dec_depth
            | _kw_: node token, parent, remove last name, path
   }}*/
/*{{|desc: Removes the last node name from a node token path, cutting it in place at its last backslash
      separator. A path with a single name becomes empty; an empty path stays empty.
    | params:
    - `pRoot` LPSTR - Zero terminated node token path, modified in place.

    Returns void }}*/
extern "C" void OT4XB_API ndtk_dec_depth(LPSTR pRoot)
{
   LPSTR pLast = pRoot;
   if( !*pRoot ) return;
   for( ; *pRoot; pRoot++ ){if( *pRoot == '\\' ){pLast = pRoot;}}
   *pLast = 0;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ndtk_add
            | syntax_: `void ndtk_add( LPSTR pRoot, LPSTR pNode )`
            | category: c-api/node-token
            | header: ot4xb_c_exported.h
            | mangled-name: ndtk_add
            | _kw_: node token, append name, child path
   }}*/
/*{{|desc: Appends a node name at the end of a node token path, writing a backslash separator first
      unless the path is empty. There is no room check: the path buffer must be large enough to hold the
      result (ndtk_new allocates 4096 bytes).
    | params:
    - `pRoot` LPSTR - Zero terminated node token path, modified in place.
    - `pNode` LPSTR - Node name to append. NULL or an empty string leaves the path untouched.

    Returns void }}*/
extern "C" void OT4XB_API ndtk_add(LPSTR pRoot , LPSTR pNode)
{
   ULONG cb = _xstrlen(pRoot);
   if(!pNode) return;
   if(!(*pNode)) return;
   if(cb){pRoot[cb] = '\\'; cb++; pRoot[cb] = 0;}
   for( ; *pNode; pNode++ ){pRoot[cb] = *pNode; cb++; pRoot[cb] = 0;}
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ndtk_ischild
            | syntax_: `BOOL ndtk_ischild( LPSTR pParent, LPSTR pChild, BOOL * pbIdentical )`
            | category: c-api/node-token
            | header: ot4xb_c_exported.h
            | mangled-name: ndtk_ischild
            | _kw_: node token, is child, descendant, path prefix
   }}*/
/*{{|desc: Tests whether pChild is pParent itself or lies anywhere below it: TRUE when both paths are
      identical, or when pChild starts with pParent followed by a backslash, at any depth. Names are
      compared byte by byte, case sensitive.
    | params:
    - `pParent` LPSTR - Zero terminated node token path of the candidate ancestor.
    - `pChild` LPSTR - Zero terminated node token path to test.
    - `pbIdentical` BOOL * - Optional output, may be NULL. When given it is always written: TRUE
      only when both paths are identical.

    Returns BOOL - TRUE when pChild equals pParent or is one of its descendants; FALSE otherwise. }}*/
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
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------


