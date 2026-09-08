
//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
#include <stdio.h>
#include <shlwapi.h>
#include <comutil.h>
// -----------------------------------------------------------------------------------------------------------------------

/*{{begin-note-id}}*/
/*{{note-id: ot4xb-com-interface-wrappers
            | title_: OT4XB COM interface wrappers}}*/
/*{{|:
   Low-level GWST-based wrappers over COM interface pointers. Instances are linked to existing COM interface
   pointers and dispatch methods through the interface vtable with IFpQCall().

   These classes do not create COM objects by themselves; callers must link or provide a valid interface
   pointer and manage COM lifetime rules. }}*/
/*{{end-note-id}}*/

/*{{begin-class}}*/
/*{{class-name_: OT4XB_IUNKNOW
            | _slug_: ot4xb_iunknow
            | class-function: OT4XB_IUNKNOW
            | parent: {{ilink: <class gwst> gwst}}
            | category: interop/com
            | desc: GWST class wrapping the COM IUnknown interface. The instance is linked to an existing interface
              pointer (kept in the GWST ::_m__pt_ var) and each method calls its vtable slot with IFpQCall().
              Parent class of the other OT4XB COM interface wrappers.
            | note: The class keeps the historical exported spelling OT4XB_IUNKNOW, without the final n of IUnknown.
            | see-also: {{ilink: <slug ot4xb_idispatch> OT4XB_IDISPATCH}}, {{ilink: <slug ot4xb_isequentialstream> OT4XB_ISEQUENTIALSTREAM}}, {{ilink: <slug ot4xb_istream> OT4XB_ISTREAM}}, {{ilink: <function IFpQCall> IFpQCall}}
            | _kw_: OT4XB_IUNKNOW, Class
   }}*/
BEGIN_XBASE_CLASS( OT4XB_IUNKNOW )
{
   pc->GwstParent();
   /*{{|:**BEGIN STRUCTURE  OT4XB_IUNKNOW** }}*/
   /*{{|member_: - MEMBER POINTER32 _m__vtbl_
            | desc_: Interface vtable pointer (the first 4 bytes of the linked COM interface memory).
   }}*/
   pc->Member_Pointer32("_m__vtbl_");
   
   /*{{|method_: - `METHOD QueryInterface( cIid, @pInterface )`
            | return: nHRESULT
            | desc_: Calls IUnknown::QueryInterface (vtable slot 0). Asks the object for the interface identified by
              the IID at cIid; on success pInterface receives the new interface pointer.
   }}*/
   pc->MethodCB("QueryInterface","{|s,iid,p| IFpQCall(0,\"__sl__sl__pt_@sl\",s:_m__pt_,iid,@p)}");
   /*{{|method_: - `METHOD AddRef()`
            | return: nRefCount
            | desc_: Calls IUnknown::AddRef (vtable slot 1). Increments the reference count of the linked interface
              and returns the new count.
   }}*/
   pc->MethodCB("AddRef","{|s| IFpQCall(1,\"__sl__sl\",s:_m__pt_)}");
   /*{{|method_: - `METHOD Release()`
            | return: nRefCount
            | desc_: Calls IUnknown::Release (vtable slot 2). Decrements the reference count of the linked interface
              and returns the new count.
   }}*/
   pc->MethodCB("Release","{|s| IFpQCall(2,\"__sl__sl\",s:_m__pt_)}");
   /*{{|:**END STRUCTURE** }}*/
}
END_XBASE_CLASS
/*{{include-note-id: ot4xb-com-interface-wrappers}}*/
/*{{include-note-id: com-helpers}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: OT4XB_IDISPATCH
            | _slug_: ot4xb_idispatch
            | class-function: OT4XB_IDISPATCH
            | parent: {{ilink: <slug ot4xb_iunknow> OT4XB_IUNKNOW}}
            | category: interop/com
            | desc: Wrapper over the COM IDispatch interface: inherits the OT4XB_IUNKNOW methods and adds the four
              IDispatch vtable methods.
            | see-also: {{ilink: <slug ot4xb_iunknow> OT4XB_IUNKNOW}}, {{ilink: <function IFpQCall> IFpQCall}}
            | _kw_: OT4XB_IDISPATCH, Class
   }}*/
BEGIN_XBASE_CLASS( OT4XB_IDISPATCH)     
{
   /*{{|:**BEGIN STRUCTURE  OT4XB_IDISPATCH  FROM OT4XB_IUNKNOW ** }}*/
   pc->Parent("OT4XB_IUNKNOW");
   /*{{|method_: - `METHOD GetTypeInfoCount( @nCount )`
            | return: nHRESULT
            | desc_: Calls IDispatch::GetTypeInfoCount (vtable slot 3). nCount receives 1 when the object provides
              type information, 0 when it does not.
   }}*/
   pc->MethodCB("GetTypeInfoCount" ,"{|s,n| IFpQCall(3,\"__sl__sl_@sl\",s:_m__pt_,@n)}");
   /*{{|method_: - `METHOD GetTypeInfo( nIndex, nLocale, @pTypeInfo )`
            | return: nHRESULT
            | desc_: Calls IDispatch::GetTypeInfo (vtable slot 4). Retrieves the type information of the object:
              pTypeInfo receives an ITypeInfo interface pointer for the type at nIndex in locale nLocale.
   }}*/
   pc->MethodCB("GetTypeInfo" ,"{|s,i,l,p| IFpQCall(4,\"__sl__sl__sl__sl_@sl\",s:_m__pt_,i,l,@p)}");
   /*{{|method_: - `METHOD GetIDsOfNames( pRiid, pNames, nCount, nLocale, @pDispIds )`
            | return: nHRESULT
            | desc_: Calls IDispatch::GetIDsOfNames (vtable slot 5). Maps member and argument names to dispatch
              identifiers: pNames addresses an array of nCount wide-string name pointers and pDispIds receives
              the corresponding DISPID values for locale nLocale. pRiid passes the reserved riid argument.
   }}*/
   pc->MethodCB("GetIDsOfNames","{|s,r,ppn,cb,l,ppi|"
                                "IFpQCall( 5,\"__sl__sl__pt__pt__sl__sl__pt\","
                                "s:_m__pt_,r,ppn,cb,l,@ppi)}");
   /*{{|method_: - `METHOD Invoke( nDispId, pRiid, nLocale, nFlags, @pDispParams, @pVarResult, @pExcepInfo, @nArgErr )`
            | return: nHRESULT
            | desc_: Calls IDispatch::Invoke (vtable slot 6). Invokes the dispatch member nDispId: nFlags selects
              the invoke kind, pDispParams addresses the DISPPARAMS block with the arguments, pVarResult and
              pExcepInfo address the result VARIANT and the exception information, and nArgErr receives the index
              of the first argument with an error. pRiid passes the reserved riid argument.
   }}*/
   pc->MethodCB("Invoke","{|s,d,r,l,w,dp,vr,ei,pn|"
                         "IFpQCall( 6,\"__sl__sl__sl__pt__sl__us__pt__pt__pt_@sl\","
                          "s:_m__pt_,d,r,l,w,@dp,@vr,@ei,@pn)}");
   /*{{|:**END STRUCTURE** }}*/
}
END_XBASE_CLASS
/*{{include-note-id: ot4xb-com-interface-wrappers}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: OT4XB_ISEQUENTIALSTREAM
            | _slug_: ot4xb_isequentialstream
            | class-function: OT4XB_ISEQUENTIALSTREAM
            | parent: {{ilink: <slug ot4xb_iunknow> OT4XB_IUNKNOW}}
            | category: interop/com
            | desc: Wrapper over the COM ISequentialStream interface: inherits the OT4XB_IUNKNOW methods and adds
              the Read and Write stream methods.
            | see-also: {{ilink: <slug ot4xb_iunknow> OT4XB_IUNKNOW}}, {{ilink: <slug ot4xb_istream> OT4XB_ISTREAM}}, {{ilink: <function IFpQCall> IFpQCall}}
            | _kw_: OT4XB_ISEQUENTIALSTREAM, Class
   }}*/
BEGIN_XBASE_CLASS( OT4XB_ISEQUENTIALSTREAM )     
{
   /*{{|:**BEGIN STRUCTURE  OT4XB_ISEQUENTIALSTREAM  FROM OT4XB_IUNKNOW ** }}*/
   pc->Parent("OT4XB_IUNKNOW");
   /*{{|method_: - `METHOD Read( pBuffer, nBytes, @nRead )`
            | return: nHRESULT
            | desc_: Calls ISequentialStream::Read (vtable slot 3). Reads up to nBytes bytes from the stream into
              the memory at pBuffer; nRead receives the number of bytes actually read.
   }}*/
   pc->MethodCB("Read" ,"{|s,pv,cb,pcb| IFpQCall(3,\"__sl__sl__pt__sl_@sl\",s:_m__pt_,pv,cb,@pcb)}");
   /*{{|method_: - `METHOD Write( pBuffer, nBytes, @nWritten )`
            | return: nHRESULT
            | desc_: Calls ISequentialStream::Write (vtable slot 4). Writes nBytes bytes from the memory at pBuffer
              into the stream; nWritten receives the number of bytes actually written.
   }}*/
   pc->MethodCB("Write","{|s,pv,cb,pcb| IFpQCall(4,\"__sl__sl__pt__sl_@sl\",s:_m__pt_,pv,cb,@pcb)}");
   /*{{|:**END STRUCTURE** }}*/
}
END_XBASE_CLASS
/*{{include-note-id: ot4xb-com-interface-wrappers}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: OT4XB_ISTREAM
            | _slug_: ot4xb_istream
            | class-function: OT4XB_ISTREAM
            | parent: {{ilink: <slug ot4xb_isequentialstream> OT4XB_ISEQUENTIALSTREAM}}
            | category: interop/com
            | desc: Wrapper over the COM IStream interface: inherits Read and Write from OT4XB_ISEQUENTIALSTREAM
              and adds the remaining IStream vtable methods (seek, size, copy, commit, revert, locking, stat and
              clone).
            | see-also: {{ilink: <slug ot4xb_isequentialstream> OT4XB_ISEQUENTIALSTREAM}}, {{ilink: <slug ot4xb_iunknow> OT4XB_IUNKNOW}}, {{ilink: <function IFpQCall> IFpQCall}}
            | _kw_: OT4XB_ISTREAM, Class
   }}*/
BEGIN_XBASE_CLASS( OT4XB_ISTREAM )
{
   /*{{|:**BEGIN STRUCTURE  OT4XB_ISTREAM  FROM OT4XB_ISEQUENTIALSTREAM ** }}*/
   pc->Parent("OT4XB_ISEQUENTIALSTREAM");
   /*{{|method_: - `METHOD Seek( nMove64, nOrigin, @nNewPos64 )`
            | return: nHRESULT
            | desc_: Calls IStream::Seek (vtable slot 5). Moves the seek pointer nMove64 bytes relative to nOrigin
              (0 = begin, 1 = current position, 2 = end); nNewPos64 receives the new absolute position.
   }}*/
   pc->MethodCB("Seek","{|s,n,mt,pos| IFpQCall(5,\"__sl__sl__sq__sl_@sq\",s:_m__pt_,n,mt,@pos)}");
   /*{{|method_: - `METHOD SetSize( nSize64 )`
            | return: nHRESULT
            | desc_: Calls IStream::SetSize (vtable slot 6). Changes the size of the stream to nSize64 bytes.
   }}*/
   pc->MethodCB("SetSize","{|s,cb| IFpQCall(6,\"__sl__sl__sq\",s:_m__pt_,cb)}");
   /*{{|method_: - `METHOD CopyTo( pStream, nBytes64, @nRead64, @nWritten64 )`
            | return: nHRESULT
            | desc_: Calls IStream::CopyTo (vtable slot 7). Copies nBytes64 bytes from the current seek pointer to
              the stream interface at pStream; nRead64 and nWritten64 receive the number of bytes read and written.
   }}*/
   pc->MethodCB("CopyTo","{|s,os,cb,pcbr,pcbw| IFpQCall(7,\"__sl__sl__pt__sq_@sq_@sq\",s:_m__pt_,os,cb,@pcbr,@pcbw)}");
   /*{{|method_: - `METHOD Commit( nFlags )`
            | return: nHRESULT
            | desc_: Calls IStream::Commit (vtable slot 8). Persists changes made to the stream according to the
              nFlags commit flags.
   }}*/
   pc->MethodCB("Commit","{|s,flags| IFpQCall(8,\"__sl__sl__sl\",s:_m__pt_,flags)}");
   /*{{|method_: - `METHOD Revert()`
            | return: nHRESULT
            | desc_: Calls IStream::Revert (vtable slot 9). Discards the changes made to the stream since the last
              Commit.
   }}*/
   pc->MethodCB("Revert","{|s| IFpQCall(9,\"__sl__sl\",s:_m__pt_)}");
   /*{{|method_: - `METHOD LockRegion( nOffset64, nBytes64, nLockType )`
            | return: nHRESULT
            | desc_: Calls IStream::LockRegion (vtable slot 10). Locks nBytes64 bytes starting at nOffset64 with
              lock mode nLockType.
   }}*/
   pc->MethodCB("LockRegion","{|s,offset,cb,dw| IFpQCall(10,\"__sl__sl__sq__sq__sl\",s:_m__pt_,offset,cb,dw)}");
   /*{{|method_: - `METHOD UnlockRegion( nOffset64, nBytes64, nLockType )`
            | return: nHRESULT
            | desc_: Calls IStream::UnlockRegion (vtable slot 11). Removes a lock set by LockRegion; the parameters
              must match the ones used to lock.
   }}*/
   pc->MethodCB("UnlockRegion","{|s,offset,cb,dw| IFpQCall(11,\"__sl__sl__sq__sq__sl\",s:_m__pt_,offset,cb,dw)}");
   /*{{|method_: - `METHOD Stat( @pStatStg, nFlags )`
            | return: nHRESULT
            | desc_: Calls IStream::Stat (vtable slot 12). Fills the STATSTG structure at pStatStg with information
              about the stream; nFlags selects how the name field is returned.
   }}*/
   pc->MethodCB("Stat","{|s,ps,dw| IFpQCall(12,\"__sl__sl__pt__sl\",s:_m__pt_,@ps,dw)}");
   /*{{|method_: - `METHOD Clone( @pStream )`
            | return: nHRESULT
            | desc_: Calls IStream::Clone (vtable slot 13). Creates a new stream object over the same bytes with an
              independent seek pointer; pStream receives the new interface pointer.
   }}*/
   pc->MethodCB("Clone","{|s,p| IFpQCall(13,\"__sl__sl__pt\",s:_m__pt_,@p)}");
   /*{{|:**END STRUCTURE** }}*/
}
END_XBASE_CLASS
/*{{include-note-id: ot4xb-com-interface-wrappers}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------

