//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
#define PXERROR( n , m , d )  px->GenError();px->SetErrorSubSystem("ot4xb"); \
                              px->SetErrorOperation("TldList::"  ##m  "()"); \
                              px->SetErrorDescription( d ); \
                              px->SetErrorGenCode(0x00300000 + n);
//----------------------------------------------------------------------------------------------------------------------
static void TLdList_Init( TXbClsParams* px );
static void TLdList_Destroy( TXbClsParams* px );
static void TLdList_Bof( TXbClsParams* px);
static void TLdList_Eof( TXbClsParams* px);
static void TLdList_LastRec( TXbClsParams * px);
static void TLdList_GoEof( TXbClsParams * px);
static void TLdList_GoBof( TXbClsParams * px);
static void TLdList_RecNo( TXbClsParams* px);
static void TLdList_GoTop( TXbClsParams* px);
static void TLdList_GoBottom( TXbClsParams* px);
static void TLdList_Skip( TXbClsParams* px);
static void TLdList_Skipper( TXbClsParams* px);
static void TLdList_Goto( TXbClsParams* px);
static void TLdList_Insert( TXbClsParams* px);
static void TLdList_Append( TXbClsParams* px);
static void TLdList_Delete( TXbClsParams* px);
static void TLdList_CloneItems( TXbClsParams* px);
static void TLdList_DetachItems( TXbClsParams* px);
static void TLdList_AttachItems( TXbClsParams* px);
static void TLdList_StealItems( TXbClsParams* px);
static void TLdList_MergeClone( TXbClsParams* px);
static void TLdList_EatList( TXbClsParams* px);
static void TLdList_SwapRecords( TXbClsParams* px);
static void TLdList_pf_OnDestroyItem( TXbClsParams* px);
static void TLdList_pf_OnDestroy( TXbClsParams* px);
static void TLdList_pf_OnCloneItem( TXbClsParams* px);
static void TLdList_dwpfCargo( TXbClsParams* px);
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>TldList</name>
      <export>TLDLIST</export>
      <source>TldList.cpp:TLDLIST</source>
      <inheritance>
         <parent>GWST</parent>
      </inheritance>
      <category>container/list</category>
      <description>
         TldList is a base ot4xb structure-list class intended to be
         subclassed. It is a wrapper used to manage data stored with the
         inherited structure layout over a doubly linked list of memory blocks.
      </description>
      <constructor>
         <syntax>TldList():New() -> Self</syntax>
         <description>
            Creates a TldList instance and initializes its structure storage and
            list controller.
         </description>
      </constructor>
      <remarks>
         Derived classes define the structure members stored in each memory
         block. The item size is taken from the GWST structure size of the
         actual instance, so each list item uses the binary layout defined by
         the subclass.
      </remarks>
      <remarks>
         A single TldList object manages all nodes in the list. Structure member
         access is bound to the current node, so moving the list changes which
         memory block is exposed through the inherited structure members.
      </remarks>
      <remarks>
         Create instances with :New(). Do not call ::init() again on an
         initialized object; doing so can abandon the internal list state
         already owned by the instance.
      </remarks>
      <example>
         <code><![CDATA[
            // Structure declaration at module level, outside any function.
            BEGIN STRUCTURE TPointList EXTENDING TldList
               MEMBER LONG x
               MEMBER LONG y
            END STRUCTURE

            FUNCTION DemoPointList()
               LOCAL oPoints := TPointList():New()

               oPoints:Append()
               oPoints:x := 10
               oPoints:y := 20

               oPoints:Append()
               oPoints:x := 30
               oPoints:y := 40

               oPoints:GoTop()
               ? oPoints:x, oPoints:y   // 10, 20

               oPoints:Skip()
               ? oPoints:x, oPoints:y   // 30, 40

               oPoints:Destroy()
            RETURN NIL
         ]]></code>
      </example>
      <methods>
         <method-ref>TldList::Destroy</method-ref>
         <method-ref>TldList::Bof</method-ref>
         <method-ref>TldList::Eof</method-ref>
         <method-ref>TldList::RecNo</method-ref>
         <method-ref>TldList::LastRec</method-ref>
         <method-ref>TldList::GoTop</method-ref>
         <method-ref>TldList::GoBottom</method-ref>
         <method-ref>TldList::GoBof</method-ref>
         <method-ref>TldList::GoEof</method-ref>
         <method-ref>TldList::Skip</method-ref>
         <method-ref>TldList::Skipper</method-ref>
         <method-ref>TldList::Goto</method-ref>
         <method-ref>TldList::Insert</method-ref>
         <method-ref>TldList::Append</method-ref>
         <method-ref>TldList::Delete</method-ref>
         <method-ref>TldList::CloneItems</method-ref>
         <method-ref>TldList::DetachItems</method-ref>
         <method-ref>TldList::AttachItems</method-ref>
         <method-ref>TldList::StealItems</method-ref>
         <method-ref>TldList::MergeClone</method-ref>
         <method-ref>TldList::EatList</method-ref>
         <method-ref>TldList::SwapRecords</method-ref>
      </methods>
      <properties>
         <property-ref>TldList::pf_OnDestroyItem</property-ref>
         <property-ref>TldList::pf_OnCloneItem</property-ref>
         <property-ref>TldList::pf_OnDestroy</property-ref>
         <property-ref>TldList::dwpfCargo</property-ref>
      </properties>
   </class>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY TLDLIST( XppParamList pl )
{
   ContainerHandle conco = _conClsObj("TldList");
   if( conco == NULLCONTAINER )
   {
      TXbClass * pc = new TXbClass;
      pc->ClassName("TldList");
      pc->GwstParent(); // inherits from GWST as an ot4xb structure class
      pc->EXPORTED();
      pc->GwstReadWrite();
      // ---------------------------
      pc->Member_DWord("m_pPrev");
      pc->Member_DWord("m_pNext");
      // ---------------------------
      pc->Var( "_m__pControlSt_" );
      // ---------------------------
      pc->MethodCB( "init"      , "{|s| s:_gwst_(),s:_tld_init_(),s}"); // doc with TldList constructor
      pc->Method( "_tld_init_"  , TLdList_Init       ,0 ); // internal init used by TldList():New()
      pc->Method( "Destroy"    , TLdList_Destroy     ,0 ); // -> NIL
      pc->Method( "Bof"        , TLdList_Bof         ,0 ); // -> lBof
      pc->Method( "Eof"        , TLdList_Eof         ,0 ); // -> lEof
      pc->Method( "RecNo"      , TLdList_RecNo       ,0 ); // -> nRecord
                                                        
      pc->Method( "LastRec"    , TLdList_LastRec     ,0 ); // -> nLastRec
      pc->Method( "GoEof"      , TLdList_GoEof       ,0 ); // -> GoEof()->Self
      pc->Method( "GoBof"      , TLdList_GoBof       ,0 ); // -> GoBof()->Self
                                                        
      pc->Method( "GoTop"      , TLdList_GoTop       ,0 ); // -> !lEofBof
      pc->Method( "GoBottom"   , TLdList_GoBottom    ,0 ); // -> !lEofBof
      pc->Method( "Skip"       , TLdList_Skip        ,1 ); // -> !lEofBof
      pc->Method( "Skipper"    , TLdList_Skipper     ,1 ); // -> nSkipped
      pc->Method( "Goto"       , TLdList_Goto        ,1 ); // -> !lEofOrBof
      pc->Method( "Insert"     , TLdList_Insert      ,0 ); // -> lOk
      pc->Method( "Append"     , TLdList_Append      ,0 ); // -> lOk
      pc->Method( "Delete"     , TLdList_Delete      ,0 ); // -> lOk
      pc->Method( "CloneItems" , TLdList_CloneItems  ,2 ); // -> pFirstClonItem
      pc->Method( "DetachItems", TLdList_DetachItems ,2 ); // -> pFirstFosterItem
      pc->Method( "AttachItems", TLdList_AttachItems ,1 ); // ::AtachItems( pItem) -> nItems
      pc->Method( "StealItems" , TLdList_StealItems  ,2 ); // ::StealItems(oList,nItems) -> nSItems
      pc->Method( "MergeClone" , TLdList_MergeClone  ,1 ); // ::MergeClone(oList) -> nItems
      pc->Method( "EatList"    , TLdList_EatList     ,1 ); // ::EatList(oList) -> nSItems
      pc->Method( "SwapRecords", TLdList_SwapRecords ,2 ); // ::SwapRecords(n1,n2) -> lOk
      // ---------------------------------------------------------------------------------
      pc->Property( "pf_OnDestroyItem" , TLdList_pf_OnDestroyItem, 1 );
      pc->Property( "pf_OnCloneItem"   , TLdList_pf_OnCloneItem, 1 );
      pc->Property( "pf_OnDestroy"     , TLdList_pf_OnDestroy, 1 );
      pc->Property( "dwpfCargo"        , TLdList_dwpfCargo, 1 );
      // ---------------------------------------------------------------------------------
      pc->MethodCB( "_lock_"       , "{|s| s:_m__pt_ := PeekDWord(s:_m__ghpt_) }"); // current item memory
      pc->MethodCB( "_unlock_"     , "{|s| s:_m__pt_ := 0}");                       // release current item view
      pc->MethodCB( "_alloc_"      , "{|| NIL}"); // disabled; list methods own item memory
      pc->MethodCB( "_free_"       , "{|| NIL}"); // disabled; list methods own item memory
      pc->MethodCB( "_link_"       , "{|| NIL}"); // disabled; list methods own item memory
      pc->MethodCB( "_unlink_"     , "{|| NIL}"); // disabled; list methods own item memory
      pc->MethodCB( "_zeromemory_" , "{|| NIL}"); // disabled; list methods own item memory
      pc->MethodCB( "_read_"       , "{|| NIL}"); // disabled; list methods own item memory
      pc->MethodCB( "_write_"      , "{|| NIL}"); // disabled; list methods own item memory
      // ---------------------------------------------------------------------------------



      conco = pc->Create();
      delete pc;
      if( conco == NULLCONTAINER ){_ret(pl); return;}
   }
   _conReturn(pl,conco);
   _conRelease(conco);
}
//----------------------------------------------------------------------------------------------------------------------
static void TLdList_Init( TXbClsParams* px )
{
   TLdList_Master* pMaster = (TLdList_Master*) px->GetMemberLong("_m__pControlSt_");
   if( pMaster ){ PXERROR( 1 , "init" , "Object already initialized." ); }
   else if( px->GetParamLong(1) == -1 ) // dummy list
   {
      px->PutMemberLong("_m__pt_",0);
      px->PutMemberLong("_m__ghpt_", 0 );
   }
   else
   {
      LPSTR pClsName    = _pszGetClassName( px->GetSelf() );
      DWORD dwItemSize  = px->GetMemberDWord( "_m__size_" );
      pMaster = new TLdList_Master( pClsName , dwItemSize );
      _xfree((void*) pClsName); pClsName = 0;
      px->PutMemberLong("_m__pControlSt_",(LONG) pMaster);
      px->PutMemberLong("_m__pt_",0);
      px->PutMemberLong("_m__ghpt_", pMaster->GetGhPt() );
   }
}
//----------------------------------------------------------------------------------------------------------------------
static void TLdList_Destroy( TXbClsParams* px )
{
   TLdList_Master* pMaster = (TLdList_Master*) px->GetMemberLong("_m__pControlSt_");
   if( !pMaster ){ PXERROR( 2 , "Destroy" , "Object not properly initialized." ); }
   else
   {   
      delete pMaster;
      px->PutMemberLong("_m__pControlSt_",0);
      px->PutMemberLong("_m__pt_",0);
      px->PutMemberLong("_m__ghpt_", 0 );
   }
}
//----------------------------------------------------------------------------------------------------------------------
static void TLdList_Bof( TXbClsParams* px)
{
   TLdList_Master* pMaster = (TLdList_Master*) px->GetMemberLong("_m__pControlSt_");
   if( !pMaster ){ PXERROR( 2 , "Bof" , "Object not properly initialized." ); }
   else px->PutReturnBool( pMaster->Bof());
}
//----------------------------------------------------------------------------------------------------------------------
static void TLdList_Eof( TXbClsParams* px)
{
   TLdList_Master* pMaster = (TLdList_Master*) px->GetMemberLong("_m__pControlSt_");
   if( !pMaster ){ PXERROR( 2 , "Eof" , "Object not properly initialized." ); }
   else px->PutReturnBool( pMaster->Eof());
}
//----------------------------------------------------------------------------------------------------------------------
static void TLdList_RecNo( TXbClsParams* px)
{
   TLdList_Master* pMaster = (TLdList_Master*) px->GetMemberLong("_m__pControlSt_");
   if( !pMaster ){ PXERROR( 2 , "RecNo" , "Object not properly initialized." ); }
   else px->PutReturnLong( pMaster->RecNo());
}
//----------------------------------------------------------------------------------------------------------------------
static void TLdList_GoTop( TXbClsParams* px)
{
   TLdList_Master* pMaster = (TLdList_Master*) px->GetMemberLong("_m__pControlSt_");
   if( !pMaster ){ PXERROR( 2 , "GoTop" , "Object not properly initialized." ); }
   else px->PutReturnBool( pMaster->GoTop());
}
//----------------------------------------------------------------------------------------------------------------------
static void TLdList_GoBottom( TXbClsParams* px)
{
   TLdList_Master* pMaster = (TLdList_Master*) px->GetMemberLong("_m__pControlSt_");
   if( !pMaster ){ PXERROR( 2 , "GoBottom" , "Object not properly initialized." ); }
   else px->PutReturnBool( pMaster->GoBottom());
}
//----------------------------------------------------------------------------------------------------------------------
static void TLdList_Skip( TXbClsParams* px)
{
   TLdList_Master* pMaster = (TLdList_Master*) px->GetMemberLong("_m__pControlSt_");
   if( !pMaster ){ PXERROR( 2 , "Skip" , "Object not properly initialized." ); }
   else px->PutReturnBool( pMaster->Skip(px->CheckParamType(1,XPP_NUMERIC) ? px->GetParamLong(1) : 1) );
}
//----------------------------------------------------------------------------------------------------------------------
static void TLdList_Skipper( TXbClsParams* px)
{
   TLdList_Master* pMaster = (TLdList_Master*) px->GetMemberLong("_m__pControlSt_");
   if( !pMaster ){ PXERROR( 2 , "Skipper" , "Object not properly initialized." ); }
   else px->PutReturnLong( pMaster->Skipper(px->GetParamLong(1)) );
}
//----------------------------------------------------------------------------------------------------------------------
static void TLdList_Goto( TXbClsParams* px)
{
   TLdList_Master* pMaster = (TLdList_Master*) px->GetMemberLong("_m__pControlSt_");
   if( !pMaster ){ PXERROR( 2 , "Goto" , "Object not properly initialized." ); }
   else px->PutReturnBool( pMaster->Goto(px->GetParamLong(1)) );
}
//----------------------------------------------------------------------------------------------------------------------
static void TLdList_Insert( TXbClsParams* px)
{
   TLdList_Master* pMaster = (TLdList_Master*) px->GetMemberLong("_m__pControlSt_");
   if( !pMaster ){ PXERROR( 2 , "Insert" , "Object not properly initialized." ); }
   else px->PutReturnBool( pMaster->Insert() );
}
//----------------------------------------------------------------------------------------------------------------------
static void TLdList_Append( TXbClsParams* px)
{
   TLdList_Master* pMaster = (TLdList_Master*) px->GetMemberLong("_m__pControlSt_");
   if( !pMaster ){ PXERROR( 2 , "Append" , "Object not properly initialized." ); }
   else px->PutReturnBool( pMaster->Append() );
}
//----------------------------------------------------------------------------------------------------------------------
static void TLdList_Delete( TXbClsParams* px)
{
   TLdList_Master* pMaster = (TLdList_Master*) px->GetMemberLong("_m__pControlSt_");
   if( !pMaster ){ PXERROR( 2 , "Delete" , "Object not properly initialized." ); }
   else px->PutReturnBool( pMaster->Delete() );
}
//----------------------------------------------------------------------------------------------------------------------
static void TLdList_CloneItems( TXbClsParams* px)
{
   TLdList_Master* pMaster = (TLdList_Master*) px->GetMemberLong("_m__pControlSt_");
   if( !pMaster ){ PXERROR( 2 , "CloneItems" , "Object not properly initialized." ); }
   else
   {
      LONG nCount = 0;
      px->PutReturnLong( (LONG) pMaster->CloneItems(px->GetParamLong(1),&nCount) );
      px->PutParamLong(1,nCount);
   }
}
//----------------------------------------------------------------------------------------------------------------------
static void TLdList_DetachItems( TXbClsParams* px)
{
   TLdList_Master* pMaster = (TLdList_Master*) px->GetMemberLong("_m__pControlSt_");
   if( !pMaster ){ PXERROR( 2 , "DetachItems" , "Object not properly initialized." ); }
   else
   {
      LONG nCount = 0;
      px->PutReturnLong( (LONG) pMaster->DetachItems(px->GetParamLong(1),&nCount) );
      px->PutParamLong(1,nCount);
   }
}
//----------------------------------------------------------------------------------------------------------------------
static void TLdList_AttachItems( TXbClsParams* px)
{
   TLdList_Master* pMaster = (TLdList_Master*) px->GetMemberLong("_m__pControlSt_");
   if( !pMaster ){ PXERROR( 2 , "AttachItems" , "Object not properly initialized." ); }
   else
   {
      px->PutReturnLong( (LONG) pMaster->AttachItems( (TLdList_Item*) px->GetParamLong(1)) );
   }
}
//----------------------------------------------------------------------------------------------------------------------
static void TLdList_StealItems( TXbClsParams* px)
{
   TLdList_Master* pMaster = (TLdList_Master*) px->GetMemberLong("_m__pControlSt_");
   if( !pMaster ){ PXERROR( 2 , "StealItems" , "Object not properly initialized." ); }
   else if( !px->CheckParamType(1,XPP_OBJECT) )
   {
      PXERROR( 3 , "StealItems" , "First Param Must Be a TldList Object");
   }
   else
   {
      TLdList_Master* pList = (TLdList_Master*) _conGetNLMember( px->GetParam(1),"_m__pControlSt_");
      if( !pList )
      {
         PXERROR( 4 , "StealItems" , "First Param not a TldList Object or not properly initialized");
         return;
      }
      if( pList == pMaster )
      {
         PXERROR( 5 , "StealItems" , "TldList Object cannot steal items to itself");
         return;
      }
      px->PutReturnLong( (LONG) pMaster->StealItems(pList , px->GetParamLong(2)) );
   }
}
//----------------------------------------------------------------------------------------------------------------------
static void TLdList_MergeClone( TXbClsParams* px)
{
   TLdList_Master* pMaster = (TLdList_Master*) px->GetMemberLong("_m__pControlSt_");
   if( !pMaster ){ PXERROR( 2 , "MergeClone" , "Object not properly initialized." ); }
   else if( !px->CheckParamType(1,XPP_OBJECT) )
   {
      PXERROR( 3 , "MergeClone" , "First Param Must Be a TldList Object");
   }
   else
   {
      TLdList_Master* pList = (TLdList_Master*) _conGetNLMember( px->GetParam(1),"_m__pControlSt_");
      if( !pList )
      {
         PXERROR( 4 , "MergeClone" , "First Param not a TldList Object or not properly initialized");
         return;
      }
      px->PutReturnLong( (LONG) pMaster->MergeClone(pList) );
   }
}
//----------------------------------------------------------------------------------------------------------------------
static void TLdList_EatList( TXbClsParams* px)
{
   TLdList_Master* pMaster = (TLdList_Master*) px->GetMemberLong("_m__pControlSt_");
   if( !pMaster ){ PXERROR( 2 , "EatList" , "Object not properly initialized." ); }
   else if( !px->CheckParamType(1,XPP_OBJECT) )
   {
      PXERROR( 3 , "EatList" , "First Param Must Be a TldList Object");
   }
   else
   {
      TLdList_Master* pList = (TLdList_Master*) _conGetNLMember( px->GetParam(1),"_m__pControlSt_");
      if( !pList )
      {
         PXERROR( 4 , "EatList" , "First Param not a TldList Object or not properly initialized");
         return;
      }
      if( pList == pMaster )
      {
         PXERROR( 5 , "EatList" , "TldList Object cannot eat itself"); 
         return;
      }
      px->PutReturnLong( (LONG) pMaster->EatList(pList));
      _conMCallVoid( px->GetParam(1) , "Destroy");
   }
}
//----------------------------------------------------------------------------------------------------------------------
static void TLdList_LastRec( TXbClsParams * px)
{
   TLdList_Master* pMaster = (TLdList_Master*) px->GetMemberLong("_m__pControlSt_");
   if( !pMaster ){ PXERROR( 2 , "LastRec" , "Object not properly initialized." ); }
   else px->PutReturnLong( pMaster->m_nItems);
}
//----------------------------------------------------------------------------------------------------------------------
static void TLdList_GoEof( TXbClsParams * px)
{
   TLdList_Master* pMaster = (TLdList_Master*) px->GetMemberLong("_m__pControlSt_");
   if( !pMaster ){ PXERROR( 2 , "GoEof" , "Object not properly initialized." ); }
   else
   {
      pMaster->GoEof();
      px->PutReturnSelf();
   }
}
//----------------------------------------------------------------------------------------------------------------------
static void TLdList_GoBof( TXbClsParams * px)
{
   TLdList_Master* pMaster = (TLdList_Master*) px->GetMemberLong("_m__pControlSt_");
   if( !pMaster ){ PXERROR( 2 , "GoBof" , "Object not properly initialized." ); }
   else
   {
      pMaster->GoBof();
      px->PutReturnSelf();
   }
}
//----------------------------------------------------------------------------------------------------------------------
static void TLdList_SwapRecords( TXbClsParams* px)
{
   TLdList_Master* pMaster = (TLdList_Master*) px->GetMemberLong("_m__pControlSt_");
   if( !pMaster ){ PXERROR( 2 , "SwapRecords" , "Object not properly initialized." ); }
   else
   {
      px->PutReturnBool( pMaster->SwapRecords( px->GetParamLong(1) , px->GetParamLong(2)) );
   }
}
//----------------------------------------------------------------------------------------------------------------------
static void TLdList_pf_OnDestroyItem( TXbClsParams* px)
{
   TLdList_Master* pMaster = (TLdList_Master*) px->GetMemberLong("_m__pControlSt_");
   if( !pMaster ){ PXERROR( 2 , "pf_OnDestroyItem" , "Object not properly initialized." ); }
   else
   {
      if( px->PCount() > 0 )
      {
         pMaster->m_pf_OnDestroyItem = ( _PFN_TLDLIST_ ) px->GetParamLong(1);
      }
      else px->PutReturnLong( (LONG) pMaster->m_pf_OnDestroyItem );
   }
}
// -----------------------------------------------------------------------------------------------------------------
static void TLdList_pf_OnDestroy( TXbClsParams* px)
{
   TLdList_Master* pMaster = (TLdList_Master*) px->GetMemberLong("_m__pControlSt_");
   if( !pMaster ){ PXERROR( 2 , "pf_OnDestroy" , "Object not properly initialized." ); }
   else
   {
      if( px->PCount() > 0 )
      {
         pMaster->m_pf_OnDestroy = ( _PFN_TLDLIST_ ) px->GetParamLong(1);
      }
      else px->PutReturnLong( (LONG) pMaster->m_pf_OnDestroy );
   }
}
// -----------------------------------------------------------------------------------------------------------------
static void TLdList_pf_OnCloneItem( TXbClsParams* px)
{
   TLdList_Master* pMaster = (TLdList_Master*) px->GetMemberLong("_m__pControlSt_");
   if( !pMaster ){ PXERROR( 2 , "pf_OnCloneItem" , "Object not properly initialized." ); }
   else
   {
      if( px->PCount() > 0 )
      {
         pMaster->m_pf_OnCloneItem = ( _PFN_TLDLIST_ ) px->GetParamLong(1);
      }
      else px->PutReturnLong( (LONG) pMaster->m_pf_OnCloneItem );
   }
}
//----------------------------------------------------------------------------------------------------------------------
static void TLdList_dwpfCargo( TXbClsParams* px)
{
   TLdList_Master* pMaster = (TLdList_Master*) px->GetMemberLong("_m__pControlSt_");
   if( !pMaster ){ PXERROR( 2 , "pf_OnCloneItem" , "Object not properly initialized." ); }
   else
   {
      if( px->PCount() > 0 )
      {
         pMaster->m_dwpfCargo = px->GetParamDWord(1);
      }
      else px->PutReturnDWord(pMaster->m_dwpfCargo );
   }
}
//----------------------------------------------------------------------------------------------------------------------
