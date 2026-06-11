
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

/*******************************************************************************************************************
<xbdoc>
   <class-group>
      <name>OT4XB COM interface wrappers</name>
      <category>com/interfaces</category>
      <description>
         Low-level GWST-based wrappers over COM interface pointers. Instances are linked to existing COM interface
         pointers and dispatch methods through the interface vtable with IFpQCall().
      </description>
      <remarks>
         OT4XB_IUNKNOW keeps the historical exported spelling. It wraps IUnknown. These classes do not create COM
         objects by themselves; callers must link or provide a valid interface pointer and manage COM lifetime rules.
      </remarks>
      <class>
         <name>OT4XB_IUNKNOW</name>
         <parent>GWST</parent>
         <description>Wrapper over IUnknown.</description>
         <members>
            <member type="POINTER32" name="_m__vtbl_">Interface vtable pointer.</member>
         </members>
         <methods>
            <method name="QueryInterface" syntax="::QueryInterface( cIid, @pInterface ) -> nHRESULT" />
            <method name="AddRef" syntax="::AddRef() -> nRefCount" />
            <method name="Release" syntax="::Release() -> nRefCount" />
         </methods>
      </class>
      <class>
         <name>OT4XB_IDISPATCH</name>
         <parent>OT4XB_IUNKNOW</parent>
         <description>Wrapper over IDispatch.</description>
         <methods>
            <method name="GetTypeInfoCount" syntax="::GetTypeInfoCount( @nCount ) -> nHRESULT" />
            <method name="GetTypeInfo" syntax="::GetTypeInfo( nIndex, nLocale, @pTypeInfo ) -> nHRESULT" />
            <method name="GetIDsOfNames" syntax="::GetIDsOfNames( pRiid, pNames, nCount, nLocale, @pDispIds ) -> nHRESULT" />
            <method name="Invoke" syntax="::Invoke( nDispId, pRiid, nLocale, nFlags, @pDispParams, @pVarResult, @pExcepInfo, @nArgErr ) -> nHRESULT" />
         </methods>
      </class>
      <class>
         <name>OT4XB_ISEQUENTIALSTREAM</name>
         <parent>OT4XB_IUNKNOW</parent>
         <description>Wrapper over ISequentialStream.</description>
         <methods>
            <method name="Read" syntax="::Read( pBuffer, nBytes, @nRead ) -> nHRESULT" />
            <method name="Write" syntax="::Write( pBuffer, nBytes, @nWritten ) -> nHRESULT" />
         </methods>
      </class>
      <class>
         <name>OT4XB_ISTREAM</name>
         <parent>OT4XB_ISEQUENTIALSTREAM</parent>
         <description>Wrapper over IStream.</description>
         <methods>
            <method name="Seek" syntax="::Seek( nMove64, nOrigin, @nNewPos64 ) -> nHRESULT" />
            <method name="SetSize" syntax="::SetSize( nSize64 ) -> nHRESULT" />
            <method name="CopyTo" syntax="::CopyTo( pStream, nBytes64, @nRead64, @nWritten64 ) -> nHRESULT" />
            <method name="Commit" syntax="::Commit( nFlags ) -> nHRESULT" />
            <method name="Revert" syntax="::Revert() -> nHRESULT" />
            <method name="LockRegion" syntax="::LockRegion( nOffset64, nBytes64, nLockType ) -> nHRESULT" />
            <method name="UnlockRegion" syntax="::UnlockRegion( nOffset64, nBytes64, nLockType ) -> nHRESULT" />
            <method name="Stat" syntax="::Stat( @pStatStg, nFlags ) -> nHRESULT" />
            <method name="Clone" syntax="::Clone( @pStream ) -> nHRESULT" />
         </methods>
      </class>
   </class-group>
</xbdoc>
*******************************************************************************************************************/

BEGIN_XBASE_CLASS( OT4XB_IUNKNOW )
{
   pc->GwstParent();
   pc->Member_Pointer32("_m__vtbl_");
   pc->MethodCB("QueryInterface","{|s,iid,p| IFpQCall(0,\"__sl__sl__pt_@sl\",s:_m__pt_,iid,@p)}");
   pc->MethodCB("AddRef","{|s| IFpQCall(1,\"__sl__sl\",s:_m__pt_)}");
   pc->MethodCB("Release","{|s| IFpQCall(2,\"__sl__sl\",s:_m__pt_)}");
}
END_XBASE_CLASS
// -----------------------------------------------------------------------------------------------------------------
BEGIN_XBASE_CLASS( OT4XB_IDISPATCH)     
{
   pc->Parent("OT4XB_IUNKNOW");
   pc->MethodCB("GetTypeInfoCount" ,"{|s,n| IFpQCall(3,\"__sl__sl_@sl\",s:_m__pt_,@n)}");
   pc->MethodCB("GetTypeInfo" ,"{|s,i,l,p| IFpQCall(4,\"__sl__sl__sl__sl_@sl\",s:_m__pt_,i,l,@p)}");
   pc->MethodCB("GetIDsOfNames","{|s,r,ppn,cb,l,ppi|"
                                "IFpQCall( 5,\"__sl__sl__pt__pt__sl__sl__pt\","
                                "s:_m__pt_,r,ppn,cb,l,@ppi)}");
   pc->MethodCB("Invoke","{|s,d,r,l,w,dp,vr,ei,pn|"
                         "IFpQCall( 6,\"__sl__sl__sl__pt__sl__us__pt__pt__pt_@sl\","
                          "s:_m__pt_,d,r,l,w,@dp,@vr,@ei,@pn)}");
}
END_XBASE_CLASS
// -----------------------------------------------------------------------------------------------------------------
BEGIN_XBASE_CLASS( OT4XB_ISEQUENTIALSTREAM )     
{
   pc->Parent("OT4XB_IUNKNOW");
   pc->MethodCB("Read" ,"{|s,pv,cb,pcb| IFpQCall(3,\"__sl__sl__pt__sl_@sl\",s:_m__pt_,pv,cb,@pcb)}");
   pc->MethodCB("Write","{|s,pv,cb,pcb| IFpQCall(4,\"__sl__sl__pt__sl_@sl\",s:_m__pt_,pv,cb,@pcb)}");
}
END_XBASE_CLASS
// -----------------------------------------------------------------------------------------------------------------
BEGIN_XBASE_CLASS( OT4XB_ISTREAM )
{
   pc->Parent("OT4XB_ISEQUENTIALSTREAM");
   pc->MethodCB("Seek","{|s,n,mt,pos| IFpQCall(4,\"__sl__sl__sq__sl_@sq\",s:_m__pt_,n,mt,@pos)}");
   pc->MethodCB("SetSize","{|s,cb| IFpQCall(5,\"__sl__sl__sq\",s:_m__pt_,cb)}");
   pc->MethodCB("CopyTo","{|s,os,cb,pcbr,pcbw| IFpQCall(6,\"__sl__sl__pt__sq_@sq_@sq\",s:_m__pt_,os,cb,@pcbr,@pcbw)}");
   pc->MethodCB("Commit","{|s,flags| IFpQCall(7,\"__sl__sl__sl\",s:_m__pt_,flags)}");
   pc->MethodCB("Revert","{|s| IFpQCall(8,\"__sl__sl\",s:_m__pt_)}");
   pc->MethodCB("LockRegion","{|s,offset,cb,dw| IFpQCall(9,\"__sl__sl__sq__sq__sl\",s:_m__pt_,offset,cb,dw)}");
   pc->MethodCB("UnlockRegion","{|s,offset,cb,dw| IFpQCall(10,\"__sl__sl__sq__sq__sl\",s:_m__pt_,offset,cb,dw)}");
   pc->MethodCB("Stat","{|s,ps,dw| IFpQCall(11,\"__sl__sl__pt__sl\",s:_m__pt_,@ps,dw)}");
   pc->MethodCB("Clone","{|s,p| IFpQCall(12,\"__sl__sl__pt\",s:_m__pt_,@p)}");
}
END_XBASE_CLASS
// -----------------------------------------------------------------------------------------------------------------
/*
BEGIN_XBASE_CLASS( OT4XB_IPICTURE )     
{
   pc->Parent("OT4XB_IUNKNOW");
   pc->MethodCB("get_Handle","{|s,h| IFpQCall(3,\"__sl__sl_@sl\",s:_m__pt_,@h)}");
   pc->MethodCB("get_hPal","{|s,h| IFpQCall(4,\"__sl__sl_@sl\",s:_m__pt_,@h)}");
   pc->MethodCB("get_Type","{|s,nnn| IFpQCall(5,\"__sl__sl_@ss\",s:_m__pt_,@nnn)}");
   pc->MethodCB("get_Width","{|s,nnn| IFpQCall(6,\"__sl__sl_@sl\",s:_m__pt_,@nnn)}");
   pc->MethodCB("get_Height","{|s,nnn| IFpQCall(7,\"__sl__sl_@sl\",s:_m__pt_,@nnn)}");
   pc->MethodCB("Render","{|s,hDC,x,y,cx,cy,xSrc,ySrc,cxSrc,cySrc,rc| "
                           "IFpQCall(8,\"__sl__sl__sl__sl__sl__sl__sl__sl__sl__sl__pt\"
                           ",s:_m__pt_,hDC,x,y,cx,cy,xSrc,ySrc,cxSrc,cySrc,rc)}");
                           
        virtual HRESULT STDMETHODCALLTYPE set_hPal( 
             OLE_HANDLE hPal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_CurDC( 
             __RPC__deref_out_opt HDC *phDC) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SelectPicture( 
             __RPC__in HDC hDCIn,
             __RPC__deref_out_opt HDC *phDCOut,
             __RPC__out OLE_HANDLE *phBmpOut) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_KeepOriginalFormat( 
             __RPC__out BOOL *pKeep) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_KeepOriginalFormat( 
             BOOL keep) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PictureChanged( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SaveAsFile( 
             __RPC__in_opt LPSTREAM pStream,
             BOOL fSaveMemCopy,
             __RPC__out LONG *pCbSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_Attributes( 
             __RPC__out DWORD *pDwAttr) = 0;
        
    };
*/
