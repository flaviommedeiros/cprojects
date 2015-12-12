switch ( pEvent->wdiRequest )
  {
  case WDI_START_REQ:
    *ppfnReqCB   =  ((WDI_StartReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_StartReqParamsType*)pEvent->pEventData)->pUserData;
    break;
  case WDI_STOP_REQ:
    *ppfnReqCB   =  ((WDI_StopReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_StopReqParamsType*)pEvent->pEventData)->pUserData;
    break;
  case WDI_INIT_SCAN_REQ:
    *ppfnReqCB   =  ((WDI_InitScanReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_InitScanReqParamsType*)pEvent->pEventData)->pUserData;
    break;
  case WDI_START_SCAN_REQ:
    *ppfnReqCB   =  ((WDI_StartScanReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_StartScanReqParamsType*)pEvent->pEventData)->pUserData;
    break;
  case WDI_END_SCAN_REQ:
    *ppfnReqCB   =  ((WDI_EndScanReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_EndScanReqParamsType*)pEvent->pEventData)->pUserData;
    break;
  case WDI_FINISH_SCAN_REQ:
    *ppfnReqCB   =  ((WDI_FinishScanReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_FinishScanReqParamsType*)pEvent->pEventData)->pUserData;
    break;
  case WDI_JOIN_REQ:
    *ppfnReqCB   =  ((WDI_JoinReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_JoinReqParamsType*)pEvent->pEventData)->pUserData;
    break;
  case WDI_CONFIG_BSS_REQ:
    *ppfnReqCB   =  ((WDI_ConfigBSSReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_ConfigBSSReqParamsType*)pEvent->pEventData)->pUserData;
    break;
  case WDI_DEL_BSS_REQ:
    *ppfnReqCB   =  ((WDI_DelBSSReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_DelBSSReqParamsType*)pEvent->pEventData)->pUserData;
    break;
  case WDI_POST_ASSOC_REQ:
    *ppfnReqCB   =  ((WDI_PostAssocReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_PostAssocReqParamsType*)pEvent->pEventData)->pUserData;
    break;
  case WDI_DEL_STA_REQ:
    *ppfnReqCB   =  ((WDI_DelSTAReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_DelSTAReqParamsType*)pEvent->pEventData)->pUserData;
    break;
  case WDI_DEL_STA_SELF_REQ:
    *ppfnReqCB   =  ((WDI_DelSTASelfReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_DelSTASelfReqParamsType*)pEvent->pEventData)->pUserData;
    break;

  case WDI_SET_BSS_KEY_REQ:
    *ppfnReqCB   =  ((WDI_SetBSSKeyReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_SetBSSKeyReqParamsType*)pEvent->pEventData)->pUserData;
    break;
  case WDI_RMV_BSS_KEY_REQ:
    *ppfnReqCB   =  ((WDI_RemoveBSSKeyReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_RemoveBSSKeyReqParamsType*)pEvent->pEventData)->pUserData;
    break;
  case WDI_SET_STA_KEY_REQ:
    *ppfnReqCB   =  ((WDI_SetSTAKeyReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_SetSTAKeyReqParamsType*)pEvent->pEventData)->pUserData;
    break;
  case WDI_RMV_STA_KEY_REQ:
    *ppfnReqCB   =  ((WDI_RemoveSTAKeyReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_RemoveSTAKeyReqParamsType*)pEvent->pEventData)->pUserData;
    break;
  case WDI_ADD_TS_REQ:
    *ppfnReqCB   =  ((WDI_AddTSReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_AddTSReqParamsType*)pEvent->pEventData)->pUserData;
    break;
  case WDI_DEL_TS_REQ:
    *ppfnReqCB   =  ((WDI_DelTSReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_DelTSReqParamsType*)pEvent->pEventData)->pUserData;
    break;
  case WDI_UPD_EDCA_PRMS_REQ:
    *ppfnReqCB   =  ((WDI_UpdateEDCAParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_UpdateEDCAParamsType*)pEvent->pEventData)->pUserData;
    break;
  case WDI_ADD_BA_SESSION_REQ:
    *ppfnReqCB   =  ((WDI_AddBASessionReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_AddBASessionReqParamsType*)pEvent->pEventData)->pUserData;
    break;
  case WDI_DEL_BA_REQ:
    *ppfnReqCB   =  ((WDI_DelBAReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_DelBAReqParamsType*)pEvent->pEventData)->pUserData;
    break;
#ifdef FEATURE_WLAN_CCX
   case WDI_TSM_STATS_REQ:
    *ppfnReqCB   =  ((WDI_TSMStatsReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_TSMStatsReqParamsType*)pEvent->pEventData)->pUserData;
     break;
#endif
  case WDI_CH_SWITCH_REQ:
    *ppfnReqCB   =  ((WDI_SwitchChReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_SwitchChReqParamsType*)pEvent->pEventData)->pUserData;
    break;
  case WDI_CONFIG_STA_REQ:
    *ppfnReqCB   =  ((WDI_ConfigSTAReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_ConfigSTAReqParamsType*)pEvent->pEventData)->pUserData;
    break;
  case WDI_SET_LINK_ST_REQ:
    *ppfnReqCB   =  ((WDI_SetLinkReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_SetLinkReqParamsType*)pEvent->pEventData)->pUserData;
    break;
  case WDI_GET_STATS_REQ:
    *ppfnReqCB   =  ((WDI_GetStatsReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_GetStatsReqParamsType*)pEvent->pEventData)->pUserData;
    break;
  case WDI_UPDATE_CFG_REQ:
    *ppfnReqCB   =  ((WDI_UpdateCfgReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_UpdateCfgReqParamsType*)pEvent->pEventData)->pUserData;
    break;
  case WDI_ADD_BA_REQ:
    *ppfnReqCB   =  ((WDI_AddBAReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_AddBAReqParamsType*)pEvent->pEventData)->pUserData;
    break;
  case WDI_TRIGGER_BA_REQ:
    *ppfnReqCB   =  ((WDI_TriggerBAReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_TriggerBAReqParamsType*)pEvent->pEventData)->pUserData;
    break;
  case  WDI_UPD_BCON_PRMS_REQ:
    *ppfnReqCB   =  ((WDI_UpdateBeaconParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_UpdateBeaconParamsType*)pEvent->pEventData)->pUserData;
     break;
  case  WDI_SND_BCON_REQ:
    *ppfnReqCB   =  ((WDI_SendBeaconParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_SendBeaconParamsType*)pEvent->pEventData)->pUserData;
     break;
  case  WDI_ENTER_BMPS_REQ:
    *ppfnReqCB   =  ((WDI_EnterBmpsReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_EnterBmpsReqParamsType*)pEvent->pEventData)->pUserData;
     break;
  case  WDI_EXIT_BMPS_REQ:
    *ppfnReqCB   =  ((WDI_ExitBmpsReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_ExitBmpsReqParamsType*)pEvent->pEventData)->pUserData;
     break;
  case  WDI_ENTER_UAPSD_REQ:
    *ppfnReqCB   =  ((WDI_EnterUapsdReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_EnterUapsdReqParamsType*)pEvent->pEventData)->pUserData;
     break;
  case  WDI_UPDATE_UAPSD_PARAM_REQ:
    *ppfnReqCB   =  ((WDI_UpdateUapsdReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_UpdateUapsdReqParamsType*)pEvent->pEventData)->pUserData;
     break;
  case  WDI_CONFIGURE_RXP_FILTER_REQ:
    *ppfnReqCB   =  ((WDI_ConfigureRxpFilterReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_ConfigureRxpFilterReqParamsType*)pEvent->pEventData)->pUserData;
     break;
  case  WDI_SET_BEACON_FILTER_REQ:
    *ppfnReqCB   =  ((WDI_BeaconFilterReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_BeaconFilterReqParamsType*)pEvent->pEventData)->pUserData;
     break;
  case  WDI_REM_BEACON_FILTER_REQ:
    *ppfnReqCB   =  ((WDI_RemBeaconFilterReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_RemBeaconFilterReqParamsType*)pEvent->pEventData)->pUserData;
     break;
  case  WDI_SET_RSSI_THRESHOLDS_REQ:
    *ppfnReqCB   =  ((WDI_SetRSSIThresholdsReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_SetRSSIThresholdsReqParamsType*)pEvent->pEventData)->pUserData;
     break;
  case  WDI_HOST_OFFLOAD_REQ:
    *ppfnReqCB   =  ((WDI_HostOffloadReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_HostOffloadReqParamsType*)pEvent->pEventData)->pUserData;
     break;
  case  WDI_WOWL_ADD_BC_PTRN_REQ:
    *ppfnReqCB   =  ((WDI_WowlAddBcPtrnReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_WowlAddBcPtrnReqParamsType*)pEvent->pEventData)->pUserData;
     break;
  case  WDI_WOWL_DEL_BC_PTRN_REQ:
    *ppfnReqCB   =  ((WDI_WowlDelBcPtrnReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_WowlDelBcPtrnReqParamsType*)pEvent->pEventData)->pUserData;
     break;
  case  WDI_WOWL_ENTER_REQ:
    *ppfnReqCB   =  ((WDI_WowlEnterReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_WowlEnterReqParamsType*)pEvent->pEventData)->pUserData;
     break;
  case  WDI_CONFIGURE_APPS_CPU_WAKEUP_STATE_REQ:
    *ppfnReqCB   =  ((WDI_ConfigureAppsCpuWakeupStateReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_ConfigureAppsCpuWakeupStateReqParamsType*)pEvent->pEventData)->pUserData;
     break;
  case WDI_FLUSH_AC_REQ:
    *ppfnReqCB   =  ((WDI_FlushAcReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_FlushAcReqParamsType*)pEvent->pEventData)->pUserData;
    break;
  case WDI_BTAMP_EVENT_REQ:
    *ppfnReqCB   =  ((WDI_BtAmpEventParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_BtAmpEventParamsType*)pEvent->pEventData)->pUserData;
    break;
  case WDI_KEEP_ALIVE_REQ:
    *ppfnReqCB   =  ((WDI_KeepAliveReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_KeepAliveReqParamsType*)pEvent->pEventData)->pUserData;
    break;
  case WDI_SET_TX_PER_TRACKING_REQ:
    *ppfnReqCB   =  ((WDI_SetTxPerTrackingReqParamsType*)pEvent->pEventData)->wdiReqStatusCB;
    *ppUserData  =  ((WDI_SetTxPerTrackingReqParamsType*)pEvent->pEventData)->pUserData;
  default:
    *ppfnReqCB   =  NULL;
    *ppUserData  =  NULL;
      break;
  }
