// #define OT4XB_DEBUG
//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
static void _conPutDouble_pv_( ContainerHandle con , void* pValue)
{
   _conPutND(con, reinterpret_cast<double*>(pValue)[0] );
}
// -----------------------------------------------------------------------------------------------------------------
static void _conPutFloat_pv_( ContainerHandle con , void* pValue)
{
   _conPutND(con, (double)reinterpret_cast<FLOAT*>(pValue)[0] );
}
//----------------------------------------------------------------------------------------------------------------------
static void _conPutLong_pv_( ContainerHandle con , void* pValue)
{
   _conPutNL(con, reinterpret_cast<LONG*>(pValue)[0] );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ULONG _conaGetLen(ContainerHandle cona , ULONG * pIndex, ULONG nDepth)
{
   ULONG    ul  = 0;
   LONG sp1;
   DWORD dw;

   
   __asm 
   {
      mov sp1 ,esp;
      push 0; 
   }
   if( pIndex )
   {
      while(nDepth)
      {
         nDepth--;                
         dw = (DWORD) pIndex[nDepth];
         __asm
         {
            mov eax, dw;
            push eax;
         }
      }
   }
   dw = (DWORD) &ul;
   __asm
   {
      mov eax, dw;
      push eax;
      mov eax, cona;
      push eax;
      mov eax, _conSizeA;
      call eax;
      mov esp , sp1;
   }
   
   return ul;
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ULONG _conaGetType(ContainerHandle cona , ULONG * pIndex, ULONG nDepth)
{
   ULONG    ul  = 0;
   LONG sp1;
   DWORD dw;

   
   __asm 
   {
      mov sp1 ,esp;
      push 0; 
   }
   if( pIndex )
   {
      while(nDepth)
      {
         nDepth--;                
         dw = (DWORD) pIndex[nDepth];
         __asm
         {
            mov eax, dw;
            push eax;
         }
      }
   }
   dw = (DWORD) &ul;
   __asm
   {
      mov eax, dw;
      push eax;
      mov eax, cona;
      push eax;
      mov eax, _conTypeA;
      call eax;
      mov esp , sp1;
   }
   
   return ul;
}
//----------------------------------------------------------------------------------------------------------------------
TList * _conRecurseArrayIndex(ContainerHandle cona, ULONG* pBase, ULONG nDepth, TList * pList)
{
   ULONG  nBuffSize = ( sizeof(ULONG) * ( nDepth + 2 ) );
   ULONG* pIndex = (ULONG*) _xgrab( nBuffSize );
   ULONG  nItems = 0;
   ULONG n;
   if( !pList ) pList = new TList;
   
   for( n = 0; n < nDepth; n++ ) pIndex[n] = pBase[n];
   
   nItems = _conaGetLen(cona,pBase,nDepth);
   
   for( n = 1; n <= nItems; n++ )
   {
      ULONG nType;
      
      pIndex[nDepth] = n;
      
      nType = _conaGetType(cona,pIndex,nDepth+1);
      
      if( nType & XPP_ARRAY )
      {
          
          _conRecurseArrayIndex(cona,pIndex,nDepth+1,pList);
          
      }
      else pList->Add(reinterpret_cast<void*>( _bdup(reinterpret_cast<BYTE*>(pIndex),nBuffSize) ) );
   }
   _xfree( (void*) pIndex);
   
   
   return pList;
}
//----------------------------------------------------------------------------------------------------------------------
void _delete_complex_array_index_(TList ** ppList)
{
   if( ppList )
   {
      TList* pList = ppList[0];
      if( pList )
      {
         ULONG n;
         ULONG nItems = pList->Count();
         for( n = 0; n < nItems; n++)
         {
            void * pt = pList->Replace(n,0);
            if( pt ) _xfree(pt);
         }
         delete pList;
         ppList[0] = 0;
      }
   }
}
// -----------------------------------------------------------------------------------------------------------------
LPSTR _cona_LockStrEx_(ContainerHandle cona,TList ** ppList,ULONG * pnSize, ULONG nCntType)
{
   ULONG nItems  = _conGetArrayLen(cona);
   ULONG nType   = 0;
   LPSTR pBuffer = 0;
   ULONG  n;
   ContainerHandle con = NULLCONTAINER;
   ULONG nItemSize   = sizeof(LONG);
   DWORD dwfp        = (DWORD) _conGetLong;
   DWORD dw;
   DWORD sp1;

   ppList[0] = 0;
   pnSize[0] = 0;
   if( !nItems ) return 0;

   switch( nCntType )
   {
      case 1:{  nItemSize = sizeof(FLOAT); dwfp = (DWORD) _conGetFloat; break;}
      case 2:{  nItemSize = sizeof(double); dwfp = (DWORD) _conGetND; break;}
   }
   
   _conTypeA( cona , &nType , 1, 0);

   if( nType & XPP_ARRAY )
   {
      TList * pList = ppList[0] = _conRecurseArrayIndex(cona);
      nItems = pList->Count();
      pnSize[0]  = (ULONG) (nItems * nItemSize);
      pBuffer    = (LPSTR) _xgrab( pnSize[0] + nItemSize );
      dw         = (DWORD) pBuffer;
      for( n = 0; n < nItems; n++ , dw += nItemSize)
      {
         con = _conArrayGetA(cona,con,reinterpret_cast<int*>(pList->Get(n)));
         __asm
         {
            mov sp1 ,esp;
            mov eax, dw;
            push eax;
            mov eax, con;
            push eax;
            mov eax, dwfp;
            call eax;
            mov eax ,sp1;
            mov esp ,eax;
         }
      }
   }
   else
   {
      pnSize[0]  = (ULONG) (nItems * nItemSize);
      pBuffer    = (LPSTR) _xgrab( pnSize[0] + nItemSize );
      dw         = (DWORD) pBuffer;
      for( n = 0; n < nItems; n++ , dw += nItemSize)
      {
         con = _conArrayGet(cona,con,n+1,0);
         __asm
         {
            mov sp1 ,esp;
            mov eax, dw;
            push eax;
            mov eax, con;
            push eax;
            mov eax, dwfp;
            call eax;
            mov eax ,sp1;
            mov esp ,eax;
         }
      }
   }
   if( con ) _conRelease(con);
   return (LPSTR) pBuffer;
}
//----------------------------------------------------------------------------------------------------------------------
void _cona_UnLockStrEx_(ContainerHandle cona,TList ** ppList, LPSTR * ppStr , ULONG nCntType, BOOL bWrite)
{
   TList * pList = ppList[0];
   ULONG nItems  = ( pList ? pList->Count() : _conGetArrayLen(cona) );
   ULONG  n;
   ULONG nItemSize   = sizeof(LONG);
   DWORD dwfp        = (DWORD) _conPutLong_pv_;
   DWORD dw          = (DWORD) ppStr[0];
   DWORD sp1;

   switch( nCntType )
   {
      case 1:{  nItemSize = sizeof(FLOAT); dwfp = (DWORD) _conPutFloat_pv_; break;}
      case 2:{  nItemSize = sizeof(double); dwfp = (DWORD) _conPutDouble_pv_; break;}
   }

   if( bWrite && dw )
   {
      if( pList )
      {
         for( n = 0; n < nItems; n++ , dw += nItemSize)
         {
            ContainerHandle con = _conNew( NULLCONTAINER);
            __asm
            {
               mov sp1 ,esp;
               mov eax, dw;
               push eax;
               mov eax, con;
               push eax;
               mov eax, dwfp;
               call eax;
               mov eax ,sp1;
               mov esp ,eax;
            }
            _conArrayPutA(cona,con,reinterpret_cast<int*>(pList->Get(n)));
            _conRelease( con );
         }
      }
      else
      {
         for( n = 0; n < nItems; n++ , dw += nItemSize)
         {
            ContainerHandle con = _conNew( NULLCONTAINER);
            __asm
            {
               mov sp1 ,esp;
               mov eax, dw;
               push eax;
               mov eax, con;
               push eax;
               mov eax, dwfp;
               call eax;
               mov eax ,sp1;
               mov esp ,eax;
            }
            _conArrayPut(cona,con,n+1,0);
            _conRelease( con );
         }
      }
   }
   if(ppStr[0]){ _xfree( (void*) ppStr[0] ); ppStr[0] = 0; }
   _delete_complex_array_index_(ppList);
}
//----------------------------------------------------------------------------------------------------------------------
