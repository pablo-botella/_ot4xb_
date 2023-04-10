// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
#ifndef _XB_RESTARTMANAGER_PROTOTYPES_
#define _XB_RESTARTMANAGER_PROTOTYPES_
// -----------------------------------------------------------------------------------------------------------------
#xcommand DECLARE RESTARTMANAGER STRUCTURE CLASSES [<*more*>]   => ;
[<more>] function RM_UNIQUE_PROCESS();
;local ooo;
;local oClass := ClassObject("RM_UNIQUE_PROCESS");
;if oClass != NIL;
;return oClass;
;end;
;ooo := TXbClass():New( "RM_UNIQUE_PROCESS");
;ooo:_GwstParent(  );
;    ooo:_Member_DWord( "dwProcessId" );
;    ooo:_Child( "ProcessStartTime" , FILETIME64() );
;oClass := ooo:Create();
;ooo:Destroy();
;return oClass;
;[<more>] function RM_PROCESS_INFO();
;local ooo;
;local oClass := ClassObject("RM_PROCESS_INFO");
;if oClass != NIL;
;return oClass;
;end;
;ooo := TXbClass():New( "RM_PROCESS_INFO");
;ooo:_GwstParent(  );
;    ooo:_Child( "Process" , RM_UNIQUE_PROCESS() );
;    ooo:_Member_SZWSTR( "strAppName" , (255+1));
;    ooo:_Member_SZWSTR( "strServiceShortName" , (63+1));
;    ooo:_Member_Long( "ApplicationType" );
;    ooo:_Member_ULong( "AppStatus" );
;    ooo:_Member_DWord( "TSSessionId" );
;    ooo:_Member_Bool( "bRestartable" );
;oClass := ooo:Create();
;ooo:Destroy();
;return oClass;
;[<more>] function RM_FILTER_INFO();
;local ooo;
;local oClass := ClassObject("RM_FILTER_INFO");
;if oClass != NIL;
;return oClass;
;end;
;ooo := TXbClass():New( "RM_FILTER_INFO");
;ooo:_GwstParent(  );
;    ooo:_Member_Long( "FilterAction" );
;    ooo:_Member_Long( "FilterTrigger" );
;    ooo:_Member_DWord( "cbNextOffset" );
;    ooo:_GwstBeginUnion();
;        ooo:_Member_Pointer32( "strFilename" );
;        ooo:_Child( "Process" , RM_UNIQUE_PROCESS() );
;        ooo:_Member_Pointer32( "strServiceShortName" );
;    ooo:_GwstEndUnion();
;oClass := ooo:Create();
;ooo:Destroy();
;return oClass
//----------------------------------------------------------------------------------------------------------------------
// typedef void (*RM_WRITE_STATUS_CALLBACK)( __in UINT nPercentComplete );
//----------------------------------------------------------------------------------------------------------------------
#xtranslate Rm.StartSession(<pSessionHandle>,<dwSessionFlags>,<strSessionKey>) =>; 
            fpqcall({"rstrtmgr","RmStartSession"},"__sl_@sl__slc@sw",<pSessionHandle>,<dwSessionFlags>,<strSessionKey>)
//----------------------------------------------------------------------------------------------------------------------
#xtranslate Rm.JoinSession( <pSessionHandle> , <strSessionKey> ) =>;
           fpqcall({"rstrtmgr","RmJoinSession"}, "__sl_@slc_sw" , <pSessionHandle> , <strSessionKey> )
//----------------------------------------------------------------------------------------------------------------------
#xtranslate Rm.EndSession( <dwSessionHandle> ) =>;
           fpqcall({"rstrtmgr","RmEndSession"}, "__sl__sl" , <dwSessionHandle>)
//----------------------------------------------------------------------------------------------------------------------
#xtranslate Rm.RegisterResources(<dwSessionHandle>,<nFiles>,<rgsFileNames>,<nApplications>,<rgApplications>,<nServices>,<rgsServiceNames>) =>; 
            fpqcall({"rstrtmgr","RmRegisterResources"},"__sl__sl__sl__pt__sl__pt__sl__pt" ,;
            <dwSessionHandle>,<nFiles>,<rgsFileNames>,<nApplications>,<rgApplications>,<nServices>,<rgsServiceNames> )
//----------------------------------------------------------------------------------------------------------------------
#xtranslate Rm.GetList(<dwSessionHandle>,<pnProcInfoNeeded>,<pnProcInfo>,<rgAffectedApps>,<lpdwRebootReasons>) =>;
            fpqcall({"rstrtmgr","RmGetList"},"__sl__sl_@sl_@sl__pt_@sl" ,;
            <dwSessionHandle>,<pnProcInfoNeeded>,<pnProcInfo>,<rgAffectedApps>,<lpdwRebootReasons>)
//----------------------------------------------------------------------------------------------------------------------
#xtranslate Rm.Shutdown(<dwSessionHandle>,<lActionFlags>,<fnStatus>) =>; 
            fpqcall({"rstrtmgr","RmShutdown"},"__sl__sl__sl__pt" ,;
            <dwSessionHandle>,<lActionFlags>,<fnStatus>)
//----------------------------------------------------------------------------------------------------------------------
#xtranslate Rm.Restart(<dwSessionHandle>,<dwRestartFlags>,<fnStatus>) =>; 
            fpqcall({"rstrtmgr","RmRestart"},"__sl__sl__sl__pt" ,;
            <dwSessionHandle>,<dwRestartFlags>,<fnStatus>)
//----------------------------------------------------------------------------------------------------------------------
#xtranslate Rm.CancelCurrentTask(<dwSessionHandle>) => fpqcall({"rstrtmgr","RmCancelCurrentTask"},"__sl__sl",<dwSessionHandle>)
//----------------------------------------------------------------------------------------------------------------------
#xtranslate Rm.AddFilter(<dwSessionHandle>,<strModuleName>,<pProcess>,<strServiceShortName>,<FilterAction>) =>; 
            fpqcall({"rstrtmgr","RmAddFilter"},"__sl__slc_sw__ptc_sw__sl" ,;
            <dwSessionHandle>,<strModuleName>,<pProcess>,<strServiceShortName>,<FilterAction> )
//----------------------------------------------------------------------------------------------------------------------
#xtranslate Rm.RemoveFilter(<dwSessionHandle>,<strModuleName>,<pProcess>,<strServiceShortName>) =>; 
            fpqcall({"rstrtmgr","RmRemoveFilter"},"__sl__slc_sw__ptc_sw" ,;
            <dwSessionHandle>,<strModuleName>,<pProcess>,<strServiceShortName> )
//----------------------------------------------------------------------------------------------------------------------
#xtranslate Rm.GetFilterList(<dwSessionHandle>,<strModuleName>,<pbFilterBuf>,<cbFilterBuf>,<cbFilterBufNeeded>) =>; 
            fpqcall({"rstrtmgr","RmGetFilterList"},"__sl__sl__pt__sl_@sl" ,;
             <dwSessionHandle>,<strModuleName>,<pbFilterBuf>,<cbFilterBuf>,<cbFilterBufNeeded>)
// -----------------------------------------------------------------------------------------------------------------
#endif // _XB_RESTARTMANAGER_PROTOTYPES_
// -----------------------------------------------------------------------------------------------------------------
// EOF
// -----------------------------------------------------------------------------------------------------------------
