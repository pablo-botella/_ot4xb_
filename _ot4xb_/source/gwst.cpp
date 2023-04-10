//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//-----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
#define PXERROR( n , m , d )  px->GenError();px->SetErrorSubSystem("ot4xb"); \
                              px->SetErrorOperation("gwst::"  ##m  "()"); \
                              px->SetErrorDescription( d ); \
                              px->SetErrorGenCode(0x00101000 + n);
//----------------------------------------------------------------------------------------------------------------------
static GWST_SORT_ITEM * _gwst_get_member_info_array_( ContainerHandle conoGwst , ContainerHandle conaMNames );

//-----------------------------------------------------------------------------------------------------------------------
static void gwst_xb_gwst       ( TXbClsParams * px ); // 2 // ::_gwst_(oParent,nShift)
static void gwst_xb_alloc      ( TXbClsParams * px ); // 2 // ::_alloc_(lCopy,pMem)
static void gwst_xb_free       ( TXbClsParams * px ); // 1 // ::_free_(lCopy)
static void gwst_xb_link       ( TXbClsParams * px ); // 2 // ::_link_(pMem,lCopy)
static void gwst_xb_unlink     ( TXbClsParams * px ); // 1 // ::_unlink_(lCopy)
static void gwst_xb_read       ( TXbClsParams * px ); // 2 // ::_read_(cBuffer,nPos)
static void gwst_xb_write      ( TXbClsParams * px ); // 2 // ::_write_(cBuffer,nPos)
static void gwst_xb_zeromemory ( TXbClsParams * px ); // 1 // ::_zeromemory_([member])
static void gwst_xb_sizeof        ( TXbClsParams * px ); // 1 // ::_sizeof_([member])
static void gwst_xb_addressof     ( TXbClsParams * px ); // 1 // ::_addressof_([member])
static void gwst_xb_lock          ( TXbClsParams * px ); // 1 // ::_lock_(@nLen) // -> nAddress
static void gwst_xb_unlock        ( TXbClsParams * px ); // 0 // ::_unlock_()
static void gwst_xb_nExtraSize_( TXbClsParams * px );// 1 // ::_nExtraSize_

//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY GWST(XppParamList pl)
{
   ContainerHandle conco = _conClsObj("GWST");
   // ---------------------------------------------------------------------------------
   if( conco == NULLCONTAINER )
   {
      TXbClass * pc = new TXbClass;
      pc->ClassName( "GWST" );
      pc->EXPORTED();
      // ---------------------------------------------------------------------------------
      pc->SharedClassVar( "_mc__chdef_" ); // {{1class,2shift,3size},...}     // Nested structure members
      pc->SharedClassVar( "_mc__mdef_" );  // "Crc32(MName)+SHIFT+SIZE+CHPOS" // Member Attributes
      pc->SharedClassVar( "_mc__size_"  ); // Default Structure size
      pc->Var( "_m__size_"  );  // Object Structure size ::_mc__size_ by default but can be changed within instances
      pc->Var( "_m__shift_" );  // Offset from the owner of the memory pointer
      pc->Var( "_m__child_" );  // array of child objects of the instance
      pc->Var( "_m__pto_"   );  // Owner object of the memory pointer
      pc->Var( "_m__pt_"    );  // memory pointer ,character buffer or parent object
      pc->Var( "_m__lk_"    );  // Lock Counter
      pc->Var( "_m__con_"   );  // ContainerHandle if buffer is character and locked
      pc->Var( "_m__ghpt_"   ); 
      // ---------------------------------------------------------------------------------
      pc->ClassMethodCB( "_xgrab_array_" ,"{|s,n| iif(Empty(n),0,_xgrab( n * s:_mc__size_ ))}");            
    // ---------------------------------------------------------------------------------
      pc->MethodCB( "init"       , "{|s,p1,p2| s:_gwst_(p1,p2),s}");
      pc->Method( "_gwst_"       , gwst_xb_gwst       , 2 ,",@s:_mc__chdef_"   );         // ::_gwst_(oParent,nShift)
      pc->Method( "_alloc_"      , gwst_xb_alloc      , 2 ,",@s:_m__pt_ ,@s:_m__lk_");    // ::_alloc_(lCopy,pMem)
      pc->Method( "_free_"       , gwst_xb_free       , 1 ,",@s:_m__pt_ ,@s:_m__lk_");    // ::_free_(lCopy)
      pc->Method( "_link_"       , gwst_xb_link       , 2 ,",@s:_m__pt_ ,@s:_m__lk_");    // ::_link_(pMem,lCopy)
      pc->MethodCB( "_scast_"    , "{|s,oc,oo| oo := iif( Valtype(oc) == 'O',oc:New(),),"
                                               "iif( oo != NIL , oo:_link_(s:_addressof_(),.F.),),"
                                               "oo }");
      pc->Method( "_unlink_"     , gwst_xb_unlink     , 1 ,",@s:_m__pt_ ,@s:_m__lk_");    // ::_unlink_(lCopy)
      pc->Method( "_lock_"       , gwst_xb_lock       , 1 ,",@s:_m__pto_:_m__pt_"    // e1
                                                           ",@s:_m__pto_:_m__lk_"    // e2
                                                           ",@s:_m__pto_:_m__con_"   // e3
                                                           ",@s:_m__pto_:_m__size_"  // e4
                                                           ",@s:_m__size_"           // e5
                                                           ",@s:_m__shift_"          // e6
                                                                                          ); //::_lock_(@n)// -> p
      pc->Method( "_unlock_"     , gwst_xb_unlock     , 0 ,",@s:_m__pto_:_m__pt_"    // e1
                                                           ",@s:_m__pto_:_m__lk_"    // e2
                                                           ",@s:_m__pto_:_m__con_"   // e3
                                                                                          ); //::_unlock_()
      pc->Method( "_zeromemory_" , gwst_xb_zeromemory , 0 , ",@s:_m__size_"                ); // ::_zeromemory_()
      pc->Method( "_sizeof_"     , gwst_xb_sizeof     , 1 ,",@s:_m__size_,@s:_mc__mdef_");// ::_sizeof_([member])
      pc->Method( "_addressof_"  , gwst_xb_addressof  , 3 ,",@s:_m__pto_:_m__pt_ "   // e1
                                                           ",@s:_m__shift_"          // e2
                                                           ",@s:_mc__mdef_"          // e3
                                                            );// ::_addressof_([member],[@shift]) -> pMem
      pc->Method( "_read_"       , gwst_xb_read       , 3 ,",@s:_m__size_"); // ::_read_(@cBuffer,[nPos][,nBytes])
      pc->Method( "_write_"      , gwst_xb_write      , 3 ,",@s:_m__size_"); // ::_write_(cBuffer,[nPos][,nBytes])

      pc->Property( "_nExtraSize_" , gwst_xb_nExtraSize_ , 1, ",@s:_m__pt_"         // e1
                                                              ",@s:_m__lk_"         // e2
                                                              ",@s:_m__size_"       // e3
                                                              ",@s:_mc__size_" );   // e4
      // ---------------------------------------------------------------------------------
      pc->MethodCB("_offsetof_","{|s,m,n| n := 0 , s:_addressof_(m,@n) , n}");
      // ---------------------------------------------------------------------------------
      
      conco = pc->Create();
      delete pc;
      if( conco == NULLCONTAINER )
      {
         if(pl){ _ret(pl); }
         return;
      }
   }
   // ---------------------------------------------------------------------------------
   if(pl) _conReturn(pl,conco);
   _conRelease(conco);
}
//-----------------------------------------------------------------------------------------------------------------------
static void gwst_xb_gwst( TXbClsParams * px ) // 2 // ::_gwst_(1oParent,2nShift) // e1 := @s:_mc__chdef_
{
   ContainerHandle Self        = px->GetSelf();
   ContainerHandle conPto      = ( px->CheckParamType(1,XPP_OBJECT) ? px->GetParam(1) : Self );
   LONG            nShift      = px->GetParamLong(2);

   _conSetNLMember( Self , "_m__size_",  _conGetNLMember( Self , "_mc__size_"));
   _conSetNLMember( Self , "_m__shift_", nShift);
   _conSetMember(   Self , "_m__pto_"  , conPto );
   _conSetNLMember(   Self , "_m__lk_"   , 0 );
   _conSetNLMember(   Self , "_m__ghpt_"   , 0 );
   _conSetNLMember(   Self , "_m__con_"  , 0 );

   if( conPto == Self )
   {
      _conSetNILMember( Self , "_m__pt_");
   }
   else
   {
      _conSetMember(   Self , "_m__pt_" ,  conPto );
   }

   if( px->CheckExtraType(1,XPP_ARRAY) )
   {
      ContainerHandle conaDef = px->GetExtra(1);
      ULONG           nLen    = _conGetArrayLen( conaDef );
      conaDef;nLen;
      ContainerHandle cona    = _conNewArray(1,nLen);
      ULONG n;
      for( n = 1 ; n <= nLen ; n++ )
      {
         ContainerHandle conco       = _conArrayGet( conaDef , NULLCONTAINER ,n,1,0);
         LONG            nTotalShift = _conArrayGetNL(conaDef,n,2,0) + nShift ;
         ContainerHandle cono = _conMCallConNR("New",conco,2,_conNew(conPto),_conPutNL(NULLCONTAINER,nTotalShift));
         _conArrayPut(cona,cono,n,0);
         _conRelease( cono );      
         _conRelease(conco); nTotalShift;
      }
      _conSetMember(Self,"_m__child_",cona);
      _conRelease(cona);      
   }
   else
   {
      ContainerHandle cona    = _conNewArray(1,0);
      _conSetMember(Self,"_m__child_",cona);
      _conRelease(cona);
   }
   px->PutReturnSelf();
}
//-----------------------------------------------------------------------------------------------------------------------
static void gwst_xb_alloc( TXbClsParams * px ) // 2 // ::_alloc_(lCopy,@pMem) // e1 := @s:_m__pt_; e2 := @_m__lk_
{
   px->PutReturnSelf();
   px->PutParamLong(2,0); // pMem := 0
   if( px->CheckExtraType(1,XPP_OBJECT) ){ PXERROR( 2 , "_alloc_" , "Child structures cannot alloc memory." );return; }
   else if( px->GetExtraLong(2) ){ PXERROR( 12 , "_alloc_" , "Structure is locked." ); return; }
   else
   {
      ContainerHandle Self        = px->GetSelf();
      BOOL   bCopy   = ( px->CheckParamType(1,XPP_LOGICAL)?px->GetParamBool(1):TRUE);
      UINT   nSize   = (UINT) _conGetNLMember( Self , "_m__size_" );
      void*  pMem    = _xgrab( nSize ) ;
      if( bCopy && px->CheckExtraType(1,XPP_CHARACTER) )
      {
        ULONG ul = 0;
         _conGetCL(px->GetExtra(1),&ul,(LPSTR)pMem,nSize);
      }
      px->PutExtraLong(1 ,(LONG) pMem);
      px->PutParamLong(2 ,(LONG) pMem);
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void gwst_xb_free( TXbClsParams * px ) // 1 // ::_free_(lCopy) // e1 := @s:_m__pt_; e2 := @_m__lk_
{
   ContainerHandle Self        = px->GetSelf();
   ContainerHandle conpt       = px->GetExtra(1);
   BOOL            bCopy   = ( px->CheckParamType(1,XPP_LOGICAL)?px->GetParamBool(1):TRUE);
   UINT            nSize   = (UINT) _conGetNLMember( Self , "_m__size_" );

   px->PutReturnSelf();
   if( px->CheckExtraType(1,XPP_OBJECT) ){ PXERROR( 3 , "_free_" , "Child structures cannot release memory." );return; }
   else if( px->GetExtraLong(2) ){ PXERROR( 12 , "_free_" , "Structure is locked." ); return; }
   if( px->CheckExtraType(1,XPP_NUMERIC) )
   {
      void*  pMem    = (void*) px->GetExtraLong(1);
      if( pMem )
      {
         if( bCopy ) _conPutCL( conpt , (LPSTR) pMem , nSize);
         else _conPutZeroString(conpt,nSize);
         _xfree(pMem);
      }
      else _conPutZeroString(conpt,nSize);
   }
   else _conPutZeroString(conpt,nSize);
}
//-----------------------------------------------------------------------------------------------------------------------
static void gwst_xb_link( TXbClsParams * px ) // 2 // ::_link_(pMem,lCopy) // e1 := @s:_m__pt_; e2 := @_m__lk_
{

   px->PutReturnSelf();
   if( px->CheckExtraType(1,XPP_OBJECT)){PXERROR(4,"_link_","Child structures cannot attach memory." );return;}
   else if( px->GetExtraLong(2) ){PXERROR( 12 , "_link_" , "Structure is locked." );return; }
   else
   {
      void *  pMem    = ( void*) px->GetParamLong(1);
      BOOL    bCopy   = ( px->CheckParamType(2,XPP_LOGICAL)?px->GetParamBool(2):TRUE);
      ContainerHandle conpt       = px->GetExtra(1);
      if( bCopy )
      {
         ContainerHandle Self    = px->GetSelf();
         UINT nSize = (UINT) _conGetNLMember( Self , "_m__size_" );
         if( pMem )
         {
            if( px->CheckExtraType(1,XPP_CHARACTER ) )
            {
               ULONG ul = 0;
               _conGetCL(conpt,&ul,(LPSTR)pMem,nSize);
            }
            else if( px->CheckExtraType(1,XPP_NUMERIC ) )
            {
               LPBYTE pOld = (LPBYTE) px->GetExtraLong(1);
               if( pOld ) _bcopy((LPBYTE) pMem , pOld , nSize );
               else _bset((LPBYTE) pMem , 0 , nSize );
            }
            else _bset((LPBYTE) pMem , 0 , nSize );
         }
      }
      if( pMem ) px->PutExtraLong(1 ,(LONG) pMem);
      else _conPut( conpt , NULLCONTAINER );
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void gwst_xb_unlink( TXbClsParams * px ) // 1 // ::_unlink_(lCopy)  // e1 := @s:_m__pt_; e2 := @_m__lk_
{

   ContainerHandle Self        = px->GetSelf();
   ContainerHandle conpt       = px->GetExtra(1);
   UINT            nSize       = (UINT) _conGetNLMember( Self , "_m__size_" );
   LONG            nFlags      = 1;
   
   if( px->CheckParamType(1,XPP_LOGICAL) )
   {
      nFlags = ( px->GetParamBool(1) ? 1 : 0);
   }
   else 
   {
      if( px->CheckParamType(1,XPP_NUMERIC) )   
      {
         nFlags = px->GetParamLong(1);
      }
   }

   if( nFlags >=  0 ){ px->PutReturnSelf(); }
   
   if( px->CheckExtraType(1,XPP_OBJECT) ){ PXERROR( 5 , "_unlink_" , "Child structures cannot detach memory." );return; }
   else if( px->GetExtraLong(2) ){ PXERROR( 12 , "_unlink_" , "Structure is locked." ); return; }
   if( nFlags < 0 )
   {
      
      if( px->CheckExtraType(1,XPP_NUMERIC) ){px->PutReturnLong( px->GetExtraLong(1) );}
      else {px->PutReturnLong( 0 );}
      _conPut(conpt , NULLCONTAINER);
   }
   else
   {
      if( px->CheckExtraType(1,XPP_NUMERIC) )
      {
         void*  pMem    = (void*) px->GetExtraLong(1);
         if( pMem )
         {
            if( nFlags > 0 ) _conPutCL( conpt , (LPSTR) pMem , nSize);
            else _conPutZeroString(conpt,nSize);
         }
         else _conPutZeroString(conpt,nSize);
      }
      else _conPutZeroString(conpt,nSize);
   }
   
}
//-----------------------------------------------------------------------------------------------------------------------
// e1 := @s:_m__pto_:_m__pt_   // e2 := @s:_m__pto_:_m__lk_ // e3 := @s:_m__pto_:_m__con_
// e4 := @s:_m__pto_:_m__size_ // e5 := @s:_m__size_        // e6 := @s:_m__shift_
static void gwst_xb_lock( TXbClsParams * px )//1//::_lock_(@nLen) // -> p
{
   LONG             nCounter      = px->GetExtraLong(2); // e2 := @s:_m__pto_:_m__lk_
   DWORD            dwShift       = px->GetExtraDWord(6);

   px->PutParamDWord(1, px->GetExtraDWord(5)); // e5 := @s:_m__size_

   if( nCounter == 0)
   {
      if( px->CheckExtraType(1,XPP_NUMERIC) ) // e1 := @s:_m__pto_:_m__pt_
      {
         px->PutExtraLong(2, 0 ); // e2 := @s:_m__pto_:_m__lk_
         px->PutReturnDWord(px->GetExtraDWord(1) + dwShift);
      }
      else if( px->CheckExtraType(1,XPP_CHARACTER) )
      {
         ContainerHandle con = _conNew( px->GetExtra(1) );
         LPSTR p  = 0;
         ULONG ul = 0;
         px->PutExtraLong(1,0); // unlink the character buffer from the container to allow ot4xb_conWLockC(con,...) reuse it
         ot4xb_conWLockC( con , &p , &ul );
         px->PutExtraLong(1 ,(LONG) p);
         px->PutExtraLong(3, (LONG) con ); // e3 := @s:_m__pto_:_m__con_
         px->PutExtraLong(2, 1 ); // e2 := @s:_m__pto_:_m__lk_
         px->PutReturnDWord( ((DWORD) p) + dwShift );

      }
      else
      {
         ContainerHandle con = _conPutZeroString(NULLCONTAINER,px->GetExtraDWord(4));
         LPSTR p  = 0;
         ULONG ul = 0;
         ot4xb_conWLockC( con , &p , &ul );
         px->PutExtraLong(1 ,(LONG) p);
         px->PutExtraLong(3, (LONG) con ); // e3 := @s:_m__pto_:_m__con_
         px->PutExtraLong(2, 1 ); // e2 := @s:_m__pto_:_m__lk_
         px->PutReturnDWord( ((DWORD) p) + dwShift );
      }
   }
   else
   {
      px->PutReturnDWord(px->GetExtraDWord(1) + dwShift);
      px->PutExtraLong(2,1);
   }
}
//-----------------------------------------------------------------------------------------------------------------------
// e1 := @s:_m__pto_:_m__pt_   // e2 := @s:_m__pto_:_m__lk_ // e3 := @s:_m__pto_:_m__con_
static void gwst_xb_unlock( TXbClsParams * px ) // 0 // ::_unlock_()
{
   LONG             nCounter      = px->GetExtraLong(2); // e2 := @s:_m__pto_:_m__lk_
   if( nCounter != 0 )
   {
      ContainerHandle con = (ContainerHandle) px->GetExtraLong(3); // e3 := @s:_m__pto_:_m__con_
      if( con != NULLCONTAINER ) 
      {
         ot4xb_conUnlockC( con );
         _conPut( px->GetExtra(1) , con);
         _conRelease( con); con = NULLCONTAINER;
      }
      px->PutExtraLong(3,0);
      px->PutExtraLong(2,0);
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void gwst_xb_zeromemory(TXbClsParams * px)//1//::_zeromemory_() // e1 := s:_m__size_
{
   ContainerHandle Self          = px->GetSelf();
   UINT            nSize         = (UINT) px->GetExtraDWord(1);
   LPBYTE          pMem          = (LPBYTE) _conMCallLong(Self,"_lock_");
   if( pMem ) _bset( pMem , 0 , nSize );
   _conMCallVoid(Self,"_unlock_");
   px->PutReturnSelf();
}
//-----------------------------------------------------------------------------------------------------------------------
DWORD gwst_x_name2crc( LPSTR pName,ULONG nNameLen)
{
   DWORD dw  = 0;
   LPSTR pp  = (LPSTR) _xgrab( nNameLen +1);
   _bcopy((LPBYTE)pp, (LPBYTE) pName, nNameLen);
   CharLowerBuff(pp,nNameLen);
   dw = dwCrc32(0,(LPBYTE)pp,nNameLen);
   _xfree( (void*) pp );
   return dw;
}
//-----------------------------------------------------------------------------------------------------------------------
BOOL gwst_x_mdef_scan( LPSTR pStrDef,ULONG nDefSize,LPSTR pName,ULONG nNameLen,GWST_DEF_MEMBER_ITEM * pItem)
{
   if( pStrDef && nDefSize && pName && nNameLen && pItem )
   {
      GWST_DEF_MEMBER_ITEM * pItems = (GWST_DEF_MEMBER_ITEM *) pStrDef;
      ULONG nItems   = (ULONG) ( nDefSize / sizeof( GWST_DEF_MEMBER_ITEM ) );
      DWORD dwSearch = gwst_x_name2crc(pName,nNameLen);
      ULONG n;

      for( n = 0 ; n < nItems; n++ )
      {
         if( pItems[n].dwCrc32 == dwSearch )
         {
            pItem->dwCrc32      = pItems[n].dwCrc32;
            pItem->dwShift      = pItems[n].dwShift;
            pItem->dwSize       = pItems[n].dwSize;
            pItem->wMemPos      = pItems[n].wMemPos;
            pItem->wGwstType    = pItems[n].wGwstType;
            return TRUE;
         }
      }
   }
   return FALSE;
}
//-----------------------------------------------------------------------------------------------------------------------
static void gwst_xb_sizeof( TXbClsParams * px ) // 1 // ::_sizeof_([member]) // e1 := @s:_m__size_ ; e2 := @s:_mc__mdef_
{
   if( px->PCount() == 0 ) px->PutReturnLong( px->GetExtraLong(1) );
   else if( px->CheckParamType(1 , XPP_NUMERIC ) )
   {
      LONG nFlags = px->GetParamLong(1);
      LONG nSize  = 0;
      if( nFlags & 1 ) nSize += px->GetMemberLong( "_mc__size_"  );
      if( nFlags & 2 ) nSize += px->GetExtraLong(1);
      px->PutReturnLong( nSize );
   }
   else if( px->CheckParamType(1 , XPP_CHARACTER ) && px->CheckExtraType(2 , XPP_CHARACTER ) )
   {
      GWST_DEF_MEMBER_ITEM item;
      ULONG ulNameLen = 0;
      LPSTR pName     = px->ParamLockStr(1,&ulNameLen);
      ULONG ulDefLen  = 0;
      LPSTR pDefStr   = px->ExtraLockStr(2,&ulDefLen);
      item.dwSize = 0;
      gwst_x_mdef_scan(pDefStr,ulDefLen,pName,ulNameLen, &item);
      px->PutReturnDWord(item.dwSize);
      px->ParamUnlockStr(1);
      px->ExtraUnlockStr(2);
   }
   else px->PutReturnLong(0);
}
//-----------------------------------------------------------------------------------------------------------------------
// e1 := @s:_m__pto_:_m__pt_ // e2 := @s:_m__shift_ // e3 := @s:_mc__mdef_
static void gwst_xb_addressof( TXbClsParams * px ) // ::_addressof_([member],[@shift],[@itemdef]) -> pMem
{
   DWORD dwShift    = px->GetExtraDWord( 2 );
   DWORD dwAddress  = ( px->CheckExtraType(1 , XPP_NUMERIC) ? px->GetExtraDWord(1) : 0 );
   if( px->CheckParamType(1 , XPP_CHARACTER ) )
   {
      if( px->CheckExtraType(3 , XPP_CHARACTER ) )
      {
         GWST_DEF_MEMBER_ITEM item;
         ULONG ulNameLen = 0;
         LPSTR pName     = px->ParamLockStr(1,&ulNameLen);
         ULONG ulDefLen  = 0;
         LPSTR pDefStr   = px->ExtraLockStr(3,&ulDefLen);
         BOOL bOk        = gwst_x_mdef_scan(pDefStr,ulDefLen,pName,ulNameLen, &item);
         px->ParamUnlockStr(1); px->ExtraUnlockStr(3);
         if( bOk )
         {
            if( px->PCount() == 3 )
            {
               GWST_SORT_ITEM si;                 
               si.dwGwstType = MAKELONG(item.wGwstType,0);
               si.dwShift    = dwShift + item.dwShift;
               si.dwSize     = item.dwSize;
               si.dwFlags = si.dw0 = si.dw1 = si.dwTable = si.dwCompare = 0;
               px->ParamPutStrLen(3,(LPSTR) ( (void*) &si),sizeof(GWST_SORT_ITEM));
            }
            dwShift += item.dwShift;
         }
         else return; // -> NIL
      }
   }
   px->PutParamDWord( 2 , dwShift );
   if( px->CheckParamType(1 , XPP_NUMERIC ) )   
   {
      LONG nTarget = px->GetParamLong(1);   
      switch( nTarget )
      {
         case 0: { px->PutReturnBool((BOOL) dwAddress ); return;}
         case 1: { px->PutReturnDWord( dwAddress + dwShift ); return;}
         case 2: { px->PutReturnDWord( dwAddress + dwShift  + px->GetMemberDWord( "_mc__size_"  ) ); return;}
      }
   }
   else { if( dwAddress ) { px->PutReturnDWord( dwAddress + dwShift ); return;} }
   px->PutReturnDWord( 0 );
}
//-----------------------------------------------------------------------------------------------------------------------
// ::_read_(pBuffer,[nPos],nBytes) -> nBytesRead
// ::_read_(@cBuffer,[nPos],[nBytes]) -> nBytesRead
// ::_read_(oGwst,[nPos],[nBytes]) -> nBytesRead
// ::_read_(,[nPos],nBytes) -> cStr
static void gwst_xb_read( TXbClsParams * px ) // 3 // ::_read_(1@cBuffer,2nPos[,3nBytes]) // e1 := s:_m__size_
{
   ContainerHandle Self          = px->GetSelf();
   UINT            nSize         = (UINT) px->GetExtraDWord(1);
   LPBYTE          pMem          = (LPBYTE) _conMCallLong(Self,"_lock_");
   LONG            nlPos         =  px->GetParamLong(2);
   UINT            nPos;
   
   if( nlPos < 0 )    nlPos = ((0 - nlPos) + px->GetMemberLong( "_mc__size_"  )) - 1;
   nPos          = (UINT) nlPos;
   if( nPos > nSize ) return; // -> NIL
   nSize -= nPos;
   pMem = (  (LPBYTE) (((DWORD) pMem) + ((DWORD) nPos ) ) );

   if( pMem )
   {
       if( px->CheckParamType(1,(XPP_CHARACTER | XPP_OBJECT | XPP_ARRAY)) )
       {
          LPBYTE pOut      = (LPBYTE) px->ParamWLockStrEx(1);
          if( pOut )
          {
             UINT   nBuffSize = (UINT) px->ParamExLen(1);
             UINT   nBytes    = ( px->CheckParamType(3,XPP_NUMERIC)  ? ((UINT)px->GetParamDWord(3)) : nBuffSize );
             if( nBytes > nBuffSize ) nBytes = nBuffSize;
             if( nBytes > nSize ) nBytes = nSize;
             if( nBytes ) _bcopy(pOut,pMem,nBytes);
             px->PutReturnDWord( (DWORD) nBytes );
          }
          px->ParamUnLockStrEx(1);
       }
       else if( px->CheckParamType(1,XPP_NUMERIC) )
       {
          LPBYTE pOut      = (LPBYTE) px->GetParamLong(1);
          if( pOut )
          {
             UINT   nBytes    = (UINT)px->GetParamDWord(3);
             if( nBytes > nSize ) nBytes = nSize;
             if( nBytes ) _bcopy(pOut,pMem,nBytes);
             px->PutReturnDWord( (DWORD) nBytes );
          }
       }
       else if( (px->PCount() < 1) || px->CheckParamType(1,XPP_UNDEF) )
       {
          ULONG nBytes    = (ULONG)( px->CheckParamType(3,XPP_NUMERIC) ? ((ULONG)px->GetParamDWord(3)) : nSize );
          if( nBytes > nSize ) nBytes = nSize;
          _conPutCL( px->GetReturn() ,(LPSTR) pMem , nBytes ); 
       }
   }
   _conMCallVoid(Self,"_unlock_");
}
//-----------------------------------------------------------------------------------------------------------------------
// ::_write_(pBuffer,[nPos],nBytes) -> nBytesWritten
// ::_write_(@cBuffer,[nPos],[nBytes]) -> nBytesWritten
// ::_write_(oGwst,[nPos],[nBytes]) -> nBytesWritten
static void gwst_xb_write ( TXbClsParams * px ) // 3 // ::_write_(cBuffer,nPos[,nBytes]) // e1 := s:_m__size_
{
   ContainerHandle Self          = px->GetSelf();
   UINT            nSize         = (UINT) px->GetExtraDWord(1);
   LPBYTE          pMem          = (LPBYTE) _conMCallLong(Self,"_lock_");
   LONG            nlPos         =  px->GetParamLong(2);
   UINT            nPos;
   
   if( nlPos < 0 )    nlPos = ((0 - nlPos) + px->GetMemberLong( "_mc__size_"  )) - 1;
   nPos          = (UINT) nlPos;
   if( nPos > nSize ) return; // -> NIL
   nSize -= nPos;
   pMem = (  (LPBYTE) (((DWORD) pMem) + ((DWORD) nPos ) ) );

   if( pMem )
   {
       if( px->CheckParamType(1,(XPP_CHARACTER | XPP_OBJECT | XPP_ARRAY)) )
       {
          LPBYTE pSrc      = (LPBYTE) px->ParamRLockStrEx(1);
          if( pSrc )
          {
             UINT   nBuffSize = (UINT) px->ParamExLen(1);
             UINT   nBytes    = ( px->CheckParamType(3,XPP_NUMERIC)  ? ((UINT)px->GetParamDWord(3)) : nBuffSize );
             if( nBytes > nBuffSize ) nBytes = nBuffSize;
             if( nBytes > nSize ) nBytes = nSize;
             if( nBytes ) _bcopy(pMem,pSrc,nBytes);
             px->PutReturnDWord( (DWORD) nBytes );
          }
          px->ParamUnLockStrEx(1);          
       }
       else if( px->CheckParamType(1,XPP_NUMERIC) )
       {
          LPBYTE pSrc      = (LPBYTE) px->GetParamLong(1);
          if( pSrc )
          {
             UINT   nBytes    = (UINT)px->GetParamDWord(3);
             if( nBytes > nSize ) nBytes = nSize;
             if( nBytes ) _bcopy(pMem,pSrc,nBytes);
             px->PutReturnDWord( (DWORD) nBytes );
          }
       }
   }
   _conMCallVoid(Self,"_unlock_");
}
//-----------------------------------------------------------------------------------------------------------------------
//Params: 1[nValue]  // Extra: 1[_m__pt_], 2[_m__lk_], 3[_m__size_], 4[_mc__size_]
static void gwst_xb_nExtraSize_( TXbClsParams * px ) // 1 // ::_nExtraSize_ | ::_nExtraSize_ := n
{
   if( px->PCount() > 0 )
   {
      LONG nExtra;
      if( px->CheckExtraType(1,XPP_OBJECT) )
      {
         PXERROR(15,"_nExtraSize_","Child structures cannot have extra size");
         return;
      }
      if( px->CheckExtraType(1,XPP_NUMERIC) )
      {
         PXERROR(16,"_nExtraSize_","Unable to set extra size while object is attached to a memory pointer");
         return;
      }

      nExtra = px->GetParamLong(1);
      if( nExtra < 0 )
      {
         PXERROR(17,"_nExtraSize_","_nExtraSize_ cannot be negative");
         return;
      }
      else
      {
         LONG nNewSize  = px->GetExtraLong(4) + nExtra;
         if( px->CheckExtraType(1,XPP_CHARACTER) )
         {
            if( ! (nNewSize ==  px->GetExtraLong(3)) )
            {
               LPSTR pBuffer = (LPSTR) _xgrab( nNewSize );
               px->ExtraGetCL(1,pBuffer,(ULONG) nNewSize);
               px->ExtraPutStrLen(1,pBuffer,(ULONG) nNewSize);
               _xfree( pBuffer );
            }
         }
         px->PutExtraLong( 1 , nNewSize );
      }
   }
   else px->PutReturnLong( px->GetExtraLong(3) - px->GetExtraLong(4) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API GWST_SORT_ITEM * _gwst_get_member_info( ContainerHandle conoGwst , ContainerHandle conMName )
{
   if( !_conCheckType(conoGwst, XPP_OBJECT)  ) return 0;
   if( _conCheckType(conMName, XPP_ARRAY) ) return _gwst_get_member_info_array_(conoGwst,conMName);
   if( _conCheckType(conMName, XPP_CHARACTER) )
   {
      ContainerHandle conShift = _conNew( NULLCONTAINER);
      ContainerHandle conInfo  = _conNew(NULLCONTAINER);
      ContainerHandle conr     = _conMCallConN( "_addressof_", conoGwst,3,conMName,conShift,conInfo);
      _conReleaseM(conShift,conr,NULLCONTAINER);
      return (GWST_SORT_ITEM*) _conRelease_ret_LPSTR( conInfo );
   }
   return 0;
}
//----------------------------------------------------------------------------------------------------------------------
static GWST_SORT_ITEM * _gwst_get_member_info_array_( ContainerHandle conoGwst , ContainerHandle conaMName )
{
   ULONG nItems = 0;    
   ULONG n; 
   GWST_SORT_ITEM * psi = 0;
   ContainerHandle cono = NULLCONTAINER;
   if( _conSizeA( conaMName , &nItems, 0 ) ) return 0;
   _conPut(cono,conoGwst );
   for( n = 1; n < nItems; n++ )
   {
      LPSTR pMName = _conArrayGetXStrDup(conaMName,n,0);
      if( pMName ) 
      {
         ContainerHandle conr = _conNew(NULLCONTAINER);
         _conGetMember( cono , pMName , conr );
         _conRelease( cono ); cono = conr;
         _xfree( (void*) pMName );
         if( !_conCheckType(cono, XPP_OBJECT)  ){ _conRelease(cono); return 0; }
      }
      else { _conRelease(cono); return 0; }
   }
   if( _conCheckType(cono, XPP_OBJECT) )
   {
      ContainerHandle conc = _conNew(NULLCONTAINER);
      _conArrayGet( conaMName , conc , nItems , 0 );
      psi = _gwst_get_member_info( cono , conc );
      _conRelease( conc );
   }
   _conRelease( cono );
   return psi;
}
//----------------------------------------------------------------------------------------------------------------------

