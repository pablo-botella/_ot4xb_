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
/*{{begin-class}}*/
/*{{class-name_: TldList
            | _slug_: tldlist
            | class-function: TLDLIST
            | parent: {{ilink: <class gwst> gwst}}
            | category: container/list
            | desc: Base OT4XB structure-list class intended to be subclassed. It is a wrapper used to manage data
              stored with the inherited structure layout over a doubly linked list of memory blocks.
            | note: Derived classes declare the structure members stored in each list item. The item size is taken
              from the GWST structure size of the actual instance, so each item block uses the binary layout
              declared by the subclass, starting with the two link pointers of the list.
            | note: A single TldList object manages all the items of its list. Structure member access is bound to
              the current item, so moving the list changes which memory block is exposed through the inherited
              structure members. There is no current item at BOF or EOF and on an empty list; the structure
              members must not be accessed there.
            | note: Create instances with :New(). Do not call ::init() again on an initialized object; doing so can
              abandon the internal list state already owned by the instance.
            | note: Lists exchange raw item blocks through ::AttachItems(), ::StealItems(), ::MergeClone() and
              ::EatList(); the two lists involved are expected to use the same item layout.
            | note: The methods raise an ot4xb error when they are called on an object whose list controller was
              destroyed or not properly initialized.
            | see-also: {{ilink: <slug gwst> GWST}}
            | example: ```
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
              ```
   | _kw_: structure list, linked list, records, work area style, skip goto
   }}*/
XPPRET XPPENTRY TLDLIST( XppParamList pl )
{
   ContainerHandle conco = _conClsObj("TldList");
   if( conco == NULLCONTAINER )
   {
      TXbClass * pc = new TXbClass;
      pc->ClassName("TldList");
      pc->GwstParent();
      /*{{|:**BEGIN STRUCTURE  TldList** }}*/
      pc->EXPORTED();
      pc->GwstReadWrite();
      // ---------------------------
      /*{{|member_: - MEMBER TLdList_Item* m_pPrev
               | desc_: Address of the previous item block in the chain, stored at the start of every item
                 block.
               | note: Link pointer managed by the list controller, not meant to be manipulated outside the
                 class.
      }}*/
      pc->Member_DWord("m_pPrev");
      /*{{|member_: - MEMBER TLdList_Item* m_pNext
               | desc_: Address of the next item block in the chain, stored at the start of every item block.
               | note: Link pointer managed by the list controller, not meant to be manipulated outside the
                 class.
      }}*/
      pc->Member_DWord("m_pNext");
      // ---------------------------
      /*{{|ivar_: - VAR _m__pControlSt_
               | type: Numeric pointer
               | desc_: Internal instance variable holding the pointer to the native list controller that owns
                 the item chain and the record pointer.
               | note: Internal state, not meant to be manipulated outside the class.
      }}*/
      pc->Var( "_m__pControlSt_" );
      // ---------------------------
      /*{{|method_: - METHOD new()
               | return: Self
               | desc_: Creates a TldList instance and initializes its structure storage and list controller.
                 The new list is empty, positioned at BOF and EOF at the same time.
      }}*/
      pc->MethodCB( "init"      , "{|s| s:_gwst_(),s:_tld_init_(),s}");
      /*{{|method_: - METHOD _tld_init_()
               | return: NIL
               | desc_: Internal second stage of ::new(): creates the native list controller sized after the
                 GWST structure size of the actual instance. Raises an ot4xb error when the object is
                 already initialized.
      }}*/
      // internal: TLdList_Init with param 1 == -1 makes a dummy list (no native controller, _m__pt_ and
      // _m__ghpt_ left at 0); not part of the documented interface
      pc->Method( "_tld_init_"  , TLdList_Init       ,0 );
      /*{{|method_: - METHOD Destroy()
               | return: NIL
               | desc_: Destroys the native list: every item is destroyed firing pf_OnDestroyItem, then
                 pf_OnDestroy fires once and the list controller is released. Call it when the list is no
                 longer needed so internal resources are not left alive unnecessarily.
      }}*/
      pc->Method( "Destroy"    , TLdList_Destroy     ,0 );
      /*{{|method_: - METHOD Bof()
               | return: lBof
               | desc_: Returns .T. when the list is positioned before the first record. An empty list is at
                 BOF and EOF at the same time.
      }}*/
      pc->Method( "Bof"        , TLdList_Bof         ,0 );
      /*{{|method_: - METHOD Eof()
               | return: lEof
               | desc_: Returns .T. when the list is positioned after the last record. An empty list is at
                 BOF and EOF at the same time.
      }}*/
      pc->Method( "Eof"        , TLdList_Eof         ,0 );
      /*{{|method_: - METHOD RecNo()
               | return: nRecord
               | desc_: Returns the current record number, from 1 to ::LastRec(). Returns 0 at BOF and on an
                 empty list, and ::LastRec() + 1 at EOF.
      }}*/
      pc->Method( "RecNo"      , TLdList_RecNo       ,0 );
                                                        
      /*{{|method_: - METHOD LastRec()
               | return: nLastRec
               | desc_: Returns the number of records stored in the list.
      }}*/
      pc->Method( "LastRec"    , TLdList_LastRec     ,0 );
      /*{{|method_: - METHOD GoEof()
               | return: Self
               | desc_: Moves the record pointer after the last record. On an empty list the BOF flag is set
                 too.
      }}*/
      pc->Method( "GoEof"      , TLdList_GoEof       ,0 );
      /*{{|method_: - METHOD GoBof()
               | return: Self
               | desc_: Moves the record pointer before the first record. On an empty list the EOF flag is
                 set too.
      }}*/
      pc->Method( "GoBof"      , TLdList_GoBof       ,0 );
                                                        
      /*{{|method_: - METHOD GoTop()
               | return: lOk
               | desc_: Moves the record pointer to the first record and returns .T., or .F. on an empty
                 list.
      }}*/
      pc->Method( "GoTop"      , TLdList_GoTop       ,0 );
      /*{{|method_: - METHOD GoBottom()
               | return: lOk
               | desc_: Moves the record pointer to the last record and returns .T., or .F. on an empty list.
      }}*/
      pc->Method( "GoBottom"   , TLdList_GoBottom    ,0 );
      /*{{|method_: - METHOD Skip( [nRecords := 1] )
               | return: lOk
               | desc_: Moves the record pointer nRecords records forward, or backwards when nRecords is
                 negative. Returns .T. when the whole movement was possible; when it runs past an end of
                 the list the record pointer is left at EOF (forward) or BOF (backwards) and .F. is
                 returned.
               | note: At BOF the movement starts counting from the first record, at EOF from the last one.
      }}*/
      pc->Method( "Skip"       , TLdList_Skip        ,1 );
      /*{{|method_: - METHOD Skipper( nRecords )
               | return: nSkipped
               | desc_: Moves like ::Skip() but never leaves the record range: the movement stops at the
                 first or last record. Returns the signed number of records actually moved, 0 on an empty
                 list.
               | note: At BOF the movement starts counting from the first record, at EOF from the last one.
      }}*/
      pc->Method( "Skipper"    , TLdList_Skipper     ,1 );
      /*{{|method_: - METHOD Goto( nRecord )
               | return: lOk
               | desc_: Moves the record pointer to record nRecord and returns .T. When nRecord is lower
                 than 1 the list is left at BOF, when it is greater than ::LastRec() at EOF, and .F. is
                 returned; .F. is always returned on an empty list.
               | note: The list is a linked list: ::Goto() walks item by item choosing the shortest path
                 from the current position or from the nearest end of the list.
      }}*/
      pc->Method( "Goto"       , TLdList_Goto        ,1 );
      /*{{|method_: - METHOD Insert()
               | return: lOk
               | desc_: Inserts a new zero-filled record at the current position and makes it the current
                 record; the record that occupied the position is shifted after it. At EOF the new record
                 is appended at the end of the list, at BOF it becomes the first record. Returns .T.
      }}*/
      pc->Method( "Insert"     , TLdList_Insert      ,0 );
      /*{{|method_: - METHOD Append()
               | return: lOk
               | desc_: Adds a new zero-filled record at the end of the list and makes it the current
                 record. Returns .T.
      }}*/
      pc->Method( "Append"     , TLdList_Append      ,0 );
      /*{{|method_: - METHOD Delete()
               | return: lOk
               | desc_: Destroys the current record, firing pf_OnDestroyItem, and returns .T. The record
                 pointer moves to the record following the deleted one, or to the new last record when the
                 last one was deleted. Returns .F. at BOF or EOF and on an empty list.
      }}*/
      pc->Method( "Delete"     , TLdList_Delete      ,0 );
      /*{{|method_: - METHOD CloneItems( [@nRecords] )
               | return: pFirstClonedItem
               | desc_: Clones records into a detached chain of new item blocks and returns the address of
                 its first item, or 0 when nothing was cloned. nRecords == -1 clones the whole list from
                 any position; a positive nRecords clones up to nRecords records starting at the current
                 one, nothing at BOF or EOF. Passed by reference, nRecords receives the number of records
                 cloned.
               | note: Each clone is a byte copy of the item with the link pointers reset; pf_OnCloneItem
                 fires for every cloned record after the copy.
               | note: The cloned chain belongs to no list until it is attached with ::AttachItems().
      }}*/
      pc->Method( "CloneItems" , TLdList_CloneItems  ,2 );
      /*{{|method_: - METHOD DetachItems( [@nRecords] )
               | return: pFirstDetachedItem
               | desc_: Unlinks records from the list into a detached chain and returns the address of its
                 first item, or 0 when nothing was detached. nRecords == -1 detaches the whole list,
                 leaving it empty; a positive nRecords detaches up to nRecords records starting at the
                 current one, nothing at BOF or EOF. The list is repositioned on the record that took the
                 place of the first detached one, or on the new last record when the detached run reached
                 the end of the list. Passed by reference, nRecords receives the number of records
                 detached.
               | note: Detached items belong to no list: attach them with ::AttachItems() of a list with
                 the same item layout, or their memory stays allocated.
      }}*/
      pc->Method( "DetachItems", TLdList_DetachItems ,2 );
      /*{{|method_: - METHOD AttachItems( pFirstItem )
               | return: nRecords
               | desc_: Attaches a chain of detached item blocks, as returned by ::CloneItems() or
                 ::DetachItems(), and returns the number of records attached; 0 attaches nothing. At BOF
                 or on the first record the chain is inserted at the head of the list, at EOF it is
                 appended at the end, anywhere else it is spliced in after the current record.
               | note: The item blocks are expected to use the item layout of this list; the chain is
                 attached as it is, without checks.
      }}*/
      pc->Method( "AttachItems", TLdList_AttachItems ,1 );
      /*{{|method_: - METHOD StealItems( oSrcList , nRecords )
               | return: nRecords
               | desc_: Detaches records from oSrcList, as ::DetachItems() does starting at the source
                 current record, and attaches them to this list at the current position. nRecords == -1
                 steals the whole source list. Returns the number of records moved. oSrcList must be a
                 different, initialized TldList object or an ot4xb error is raised.
      }}*/
      pc->Method( "StealItems" , TLdList_StealItems  ,2 );
      /*{{|method_: - METHOD MergeClone( oSrcList )
               | return: nRecords
               | desc_: Clones every record of oSrcList, firing its pf_OnCloneItem for each one, and
                 attaches the clones to this list at the current position, leaving oSrcList untouched.
                 Returns the number of records added. oSrcList must be an initialized TldList object or an
                 ot4xb error is raised.
      }}*/
      pc->Method( "MergeClone" , TLdList_MergeClone  ,1 );
      /*{{|method_: - METHOD EatList( oSrcList )
               | return: nRecords
               | desc_: Steals every record of oSrcList and then destroys the source list by calling its
                 ::Destroy(). Returns the number of records moved. oSrcList must be a different,
                 initialized TldList object or an ot4xb error is raised.
      }}*/
      pc->Method( "EatList"    , TLdList_EatList     ,1 );
      /*{{|method_: - METHOD SwapRecords( nRecord1 , nRecord2 )
               | return: lOk
               | desc_: Exchanges the positions of two records and returns .T., or .F. when either record
                 number is out of the 1 to ::LastRec() range. The record pointer keeps its record number,
                 so when the current record is one of the swapped ones the other record becomes the
                 current one.
      }}*/
      pc->Method( "SwapRecords", TLdList_SwapRecords ,2 );
      // ---------------------------------------------------------------------------------
      /*{{|property_: - PROPERTY pf_OnDestroyItem
               | type: Numeric pointer
               | desc_: Address of a __stdcall callback invoked for every item that is about to be destroyed
                 by ::Delete() or ::Destroy(). It receives 3 parameters: the address of the dwpfCargo
                 slot, the item address and 0; its result is ignored.
      }}*/
      pc->Property( "pf_OnDestroyItem" , TLdList_pf_OnDestroyItem, 1 );
      /*{{|property_: - PROPERTY pf_OnCloneItem
               | type: Numeric pointer
               | desc_: Address of a __stdcall callback invoked for every cloned item after its byte copy,
                 by ::CloneItems() and by ::MergeClone() on the source list. It receives 3 parameters: the
                 address of the dwpfCargo slot, the source item address and the new item address; its
                 result is ignored.
      }}*/
      pc->Property( "pf_OnCloneItem"   , TLdList_pf_OnCloneItem, 1 );
      /*{{|property_: - PROPERTY pf_OnDestroy
               | type: Numeric pointer
               | desc_: Address of a __stdcall callback invoked once when the native list is destroyed by
                 ::Destroy(), after all the items have been destroyed. It receives 3 parameters: the
                 address of the dwpfCargo slot, 0 and 0; its result is ignored.
      }}*/
      pc->Property( "pf_OnDestroy"     , TLdList_pf_OnDestroy, 1 );
      /*{{|property_: - PROPERTY dwpfCargo
               | type: Numeric
               | desc_: User DWORD stored in the list controller and passed by address as the first
                 parameter of the pf_OnDestroyItem, pf_OnCloneItem and pf_OnDestroy callbacks.
      }}*/
      pc->Property( "dwpfCargo"        , TLdList_dwpfCargo, 1 );
      // ---------------------------------------------------------------------------------
      /*{{|method_: - METHOD _lock_()
               | return: pMem
               | desc_: GWST storage override: refreshes the instance memory pointer with the address of the
                 current item block, taken from the list controller, and returns that address. When there
                 is no current item the address is 0.
      }}*/
      pc->MethodCB( "_lock_"       , "{|s| s:_m__pt_ := PeekDWord(s:_m__ghpt_) }");
      /*{{|method_: - METHOD _unlock_()
               | return: 0
               | desc_: GWST storage override: resets the instance memory pointer.
      }}*/
      pc->MethodCB( "_unlock_"     , "{|s| s:_m__pt_ := 0}");
      /*{{|method_: - METHOD _alloc_()
               | return: NIL
               | desc_: Disabled GWST storage operation: the list controller owns the item memory, so the
                 method does nothing.
      }}*/
      pc->MethodCB( "_alloc_"      , "{|| NIL}");
      /*{{|method_: - METHOD _free_()
               | return: NIL
               | desc_: Disabled GWST storage operation: the list controller owns the item memory, so the
                 method does nothing.
      }}*/
      pc->MethodCB( "_free_"       , "{|| NIL}");
      /*{{|method_: - METHOD _link_()
               | return: NIL
               | desc_: Disabled GWST storage operation: the list controller owns the item memory, so the
                 method does nothing.
      }}*/
      pc->MethodCB( "_link_"       , "{|| NIL}");
      /*{{|method_: - METHOD _unlink_()
               | return: NIL
               | desc_: Disabled GWST storage operation: the list controller owns the item memory, so the
                 method does nothing.
      }}*/
      pc->MethodCB( "_unlink_"     , "{|| NIL}");
      /*{{|method_: - METHOD _zeromemory_()
               | return: NIL
               | desc_: Disabled GWST storage operation: the list controller owns the item memory, so the
                 method does nothing.
      }}*/
      pc->MethodCB( "_zeromemory_" , "{|| NIL}");
      /*{{|method_: - METHOD _read_()
               | return: NIL
               | desc_: Disabled GWST storage operation: the list controller owns the item memory, so the
                 method does nothing.
      }}*/
      pc->MethodCB( "_read_"       , "{|| NIL}");
      /*{{|method_: - METHOD _write_()
               | return: NIL
               | desc_: Disabled GWST storage operation: the list controller owns the item memory, so the
                 method does nothing.
      }}*/
      /*{{|:**END STRUCTURE** }}*/
      pc->MethodCB( "_write_"      , "{|| NIL}");
      // ---------------------------------------------------------------------------------



      conco = pc->Create();
      delete pc;
      if( conco == NULLCONTAINER ){_ret(pl); return;}
   }
   _conReturn(pl,conco);
   _conRelease(conco);
}
/*{{end-class}}*/
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
