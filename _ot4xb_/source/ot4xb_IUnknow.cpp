
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