// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
#ifndef _XB_RESTARTMANAGER_CONSTANTS_
#define _XB_RESTARTMANAGER_CONSTANTS_
// -----------------------------------------------------------------------------------------------------------------
#define RM_SESSION_KEY_LEN  16 
#define CCH_RM_SESSION_KEY  RM_SESSION_KEY_LEN*2
#define CCH_RM_MAX_APP_NAME 255
#define CCH_RM_MAX_SVC_NAME 63
#define RM_INVALID_TS_SESSION -1
#define RM_INVALID_PROCESS -1

#xtranslate RmAppType.UnknownApp  => ( 0    )
#xtranslate RmAppType.MainWindow  => ( 1    )
#xtranslate RmAppType.OtherWindow => ( 2    )
#xtranslate RmAppType.Service     => ( 3    )
#xtranslate RmAppType.Explorer    => ( 4    )
#xtranslate RmAppType.Console     => ( 5    )
#xtranslate RmAppType.Critical    => ( 1000 )  
#xtranslate RmShutdownType.Force          => (0x01)
#xtranslate RmShutdownType.OnlyRegistered => (0x10)

#xtranslate RmAppStatus.Unknown        => (0x00)
#xtranslate RmAppStatus.Running        => (0x01)
#xtranslate RmAppStatus.Stopped        => (0x02)
#xtranslate RmAppStatus.StoppedOther   => (0x04)
#xtranslate RmAppStatus.Restarted      => (0x08)
#xtranslate RmAppStatus.ErrorOnStop    => (0x10)
#xtranslate RmAppStatus.ErrorOnRestart => (0x20)
#xtranslate RmAppStatus.ShutdownMasked => (0x40)
#xtranslate RmAppStatus.RestartMasked  => (0x80)

#xtranslate RmRebootReason.None             => (0x00)
#xtranslate RmRebootReason.PermissionDenied => (0x01)
#xtranslate RmRebootReason.SessionMismatch  => (0x02)
#xtranslate RmRebootReason.CriticalProcess  => (0x04)
#xtranslate RmRebootReason.CriticalService  => (0x08)
#xtranslate RmRebootReason.DetectedSelf     => (0x10)

#xtranslate RmFilterTrigger.Invalid => ( 0 )
#xtranslate RmFilterTrigger.File    => ( 1 )
#xtranslate RmFilterTrigger.Process => ( 2 )
#xtranslate RmFilterTrigger.Service => ( 3 )

#xtranslate RmFilterAction.Invalid    => ( 0 )
#xtranslate RmFilterAction.NoRestart  => ( 1 )
#xtranslate RmFilterAction.NoShutdown => ( 2 )
                                  
// -----------------------------------------------------------------------------------------------------------------
#endif // _XB_RESTARTMANAGER_CONSTANTS_
// -----------------------------------------------------------------------------------------------------------------
// EOF
// -----------------------------------------------------------------------------------------------------------------
