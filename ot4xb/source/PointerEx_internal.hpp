//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#pragma once
// ---------------------------------------------------------------------------
#ifdef _OT4XB_API_
// -----------------------------------------------------------------------------------------------------------------
TList * _conRecurseArrayIndex(ContainerHandle cona, ULONG* pBase = 0 , ULONG nDepth = 0 , TList * pList = 0);
void _delete_complex_array_index_(TList ** ppList);
LPSTR _cona_LockStrEx_(ContainerHandle cona,TList ** ppList,ULONG * pnSize, ULONG nCntType);
void _cona_UnLockStrEx_(ContainerHandle cona,TList ** ppList, LPSTR * ppStr , ULONG nCntType, BOOL bWrite);
// -----------------------------------------------------------------------------------------------------------------
#endif