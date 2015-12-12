switch( pMsg->type )
   {
      case WNI_CFG_DNLD_REQ:
      {
         status = WDA_WniCfgDnld(pWDA);
         /* call WDA complete event if config download success */
         if( VOS_IS_STATUS_SUCCESS(status) )
         {
            vos_WDAComplete_cback(pVosContext);
         }
         else
         {
            VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_ERROR,
                                     "WDA Config Download failure" );
         }
         break ;
      }
      /* 
       * Init SCAN request from PE, convert it into DAL format 
       * and send it to DAL 
       */ 
      case WDA_INIT_SCAN_REQ:
      {
         WDA_ProcessInitScanReq(pWDA, (tInitScanParams *)pMsg->bodyptr) ;
         break ;    
      }
      /* start SCAN request from PE */
      case WDA_START_SCAN_REQ:
      {
         WDA_ProcessStartScanReq(pWDA, (tStartScanParams *)pMsg->bodyptr) ;
         break ;    
      }
      /* end SCAN request from PE */
      case WDA_END_SCAN_REQ:
      {
         WDA_ProcessEndScanReq(pWDA, (tEndScanParams *)pMsg->bodyptr) ;
         break ;
      }
      /* end SCAN request from PE */
      case WDA_FINISH_SCAN_REQ:
      {
         WDA_ProcessFinishScanReq(pWDA, (tFinishScanParams *)pMsg->bodyptr) ;
         break ;    
      }
      /* join request from PE */
      case WDA_CHNL_SWITCH_REQ:
      {
         if(WDA_PRE_ASSOC_STATE == pWDA->wdaState)
         {
            WDA_ProcessJoinReq(pWDA, (tSwitchChannelParams *)pMsg->bodyptr) ;
         }
         else
         {
            WDA_ProcessChannelSwitchReq(pWDA, 
                                 (tSwitchChannelParams*)pMsg->bodyptr) ;
         }
         break ;
      }
      /* ADD BSS request from PE */
      case WDA_ADD_BSS_REQ:
      {
         WDA_ProcessConfigBssReq(pWDA, (tAddBssParams*)pMsg->bodyptr) ;
         break ;
      }
      case WDA_ADD_STA_REQ:
      {
         WDA_ProcessAddStaReq(pWDA, (tAddStaParams *)pMsg->bodyptr) ;
         break ;
      }
      case WDA_DELETE_BSS_REQ:
      {
         WDA_ProcessDelBssReq(pWDA, (tDeleteBssParams *)pMsg->bodyptr) ;
         break ;
      }
      case WDA_DELETE_STA_REQ:
      {
         WDA_ProcessDelStaReq(pWDA, (tDeleteStaParams *)pMsg->bodyptr) ;
         break ;
      }
      case WDA_CONFIG_PARAM_UPDATE_REQ:
      {
         WDA_UpdateCfg(pWDA, (tSirMsgQ *)pMsg) ;
         break ;
      }
      case WDA_SET_BSSKEY_REQ:
      {
         WDA_ProcessSetBssKeyReq(pWDA, (tSetBssKeyParams *)pMsg->bodyptr);
         break ;
      }
      case WDA_SET_STAKEY_REQ:
      {
         WDA_ProcessSetStaKeyReq(pWDA, (tSetStaKeyParams *)pMsg->bodyptr);
         break ;
      }
      case WDA_SET_STA_BCASTKEY_REQ:
      {
         WDA_ProcessSetBcastStaKeyReq(pWDA, (tSetStaKeyParams *)pMsg->bodyptr);
         break ;
      }
      case WDA_REMOVE_BSSKEY_REQ:
      {
         WDA_ProcessRemoveBssKeyReq(pWDA, 
                                    (tRemoveBssKeyParams *)pMsg->bodyptr);
         break ;
      }
      case WDA_REMOVE_STAKEY_REQ:
      {
         WDA_ProcessRemoveStaKeyReq(pWDA, 
                                    (tRemoveStaKeyParams *)pMsg->bodyptr);
         break ;
      }
      case WDA_REMOVE_STA_BCASTKEY_REQ:
      {
         /* TODO: currently UMAC is not sending this request, Add the code for 
         handling this request when UMAC supports */
         break;
      }
#ifdef FEATURE_WLAN_CCX
      case WDA_TSM_STATS_REQ:
      {
         WDA_ProcessTsmStatsReq(pWDA, (tTSMStats *)pMsg->bodyptr);
         break;
      }
#endif
      case WDA_UPDATE_EDCA_PROFILE_IND:
      {
         WDA_ProcessUpdateEDCAParamReq(pWDA, (tEdcaParams *)pMsg->bodyptr);
         break;
      }
      case WDA_ADD_TS_REQ:
      {
         WDA_ProcessAddTSReq(pWDA, (tAddTsParams *)pMsg->bodyptr);
         break;
      }
      case WDA_DEL_TS_REQ:
      {
         WDA_ProcessDelTSReq(pWDA, (tDelTsParams *)pMsg->bodyptr);
         break;
      }
      case WDA_ADDBA_REQ:
      {
         WDA_ProcessAddBASessionReq(pWDA, (tAddBAParams *)pMsg->bodyptr);
         break;
      }
      case WDA_DELBA_IND:
      {
         WDA_ProcessDelBAReq(pWDA, (tDelBAParams *)pMsg->bodyptr);
         break;
      }
      case WDA_SET_LINK_STATE:
      {
         WDA_ProcessSetLinkState(pWDA, (tLinkStateParams *)pMsg->bodyptr);
         break;
      }
      case WDA_GET_STATISTICS_REQ:
      {
         WDA_ProcessGetStatsReq(pWDA, (tAniGetPEStatsReq *)pMsg->bodyptr);
         break;
      }
      case WDA_PWR_SAVE_CFG:
      {
         if(pWDA->wdaState == WDA_READY_STATE)
         {
            WDA_ProcessSetPwrSaveCfgReq(pWDA, (tSirPowerSaveCfg *)pMsg->bodyptr);
         }
         else
         {
            if(NULL != pMsg->bodyptr)
            {
               vos_mem_free(pMsg->bodyptr);
            }
            VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_INFO,
                       "WDA_PWR_SAVE_CFG req in wrong state %d", pWDA->wdaState );
         }
         break;
      }
      case WDA_ENTER_IMPS_REQ:
      {
         if(pWDA->wdaState == WDA_READY_STATE)
         {
            WDA_ProcessEnterImpsReq(pWDA);
         }
         else
         {
            VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_INFO,
                       "WDA_ENTER_IMPS_REQ req in wrong state %d", pWDA->wdaState );
         }
         break;
      }
      case WDA_EXIT_IMPS_REQ:
      {
         if(pWDA->wdaState == WDA_READY_STATE)
         {
            WDA_ProcessExitImpsReq(pWDA);
         }
         else
         {
            VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_INFO,
                       "WDA_EXIT_IMPS_REQ req in wrong state %d", pWDA->wdaState );
         }
         break;
      }
      case WDA_ENTER_BMPS_REQ:
      {
         if(pWDA->wdaState == WDA_READY_STATE)
         {
            WDA_ProcessEnterBmpsReq(pWDA, (tEnterBmpsParams *)pMsg->bodyptr);
         }
         else
         {
            VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_INFO,
                       "WDA_ENTER_BMPS_REQ req in wrong state %d", pWDA->wdaState );
         }
         break;
      }
      case WDA_EXIT_BMPS_REQ:
      {
         if(pWDA->wdaState == WDA_READY_STATE)
         {
            WDA_ProcessExitBmpsReq(pWDA, (tExitBmpsParams *)pMsg->bodyptr);
         }
         else
         {
         VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_INFO,
                       "WDA_EXIT_BMPS_REQ req in wrong state %d", pWDA->wdaState );
         }
         break;
      }
      case WDA_ENTER_UAPSD_REQ:
      {
         if(pWDA->wdaState == WDA_READY_STATE)
         {
            WDA_ProcessEnterUapsdReq(pWDA, (tUapsdParams *)pMsg->bodyptr);
         }
         else
         {
            VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_INFO,
                       "WDA_ENTER_UAPSD_REQ req in wrong state %d", pWDA->wdaState );
         }
         break;
      }
      case WDA_EXIT_UAPSD_REQ:
      {
         if(pWDA->wdaState == WDA_READY_STATE)
         {
            WDA_ProcessExitUapsdReq(pWDA);
         }
         else
         {
            VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_INFO,
                       "WDA_EXIT_UAPSD_REQ req in wrong state %d", pWDA->wdaState );
         }
         break;
      }
      case WDA_UPDATE_UAPSD_IND:
      {
         if(pWDA->wdaState == WDA_READY_STATE)
         {
            WDA_UpdateUapsdParamsReq(pWDA, (tUpdateUapsdParams *)pMsg->bodyptr);
         }
         else
         {
            VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_INFO,
                       "WDA_UPDATE_UAPSD_IND req in wrong state %d", pWDA->wdaState );
         }
         break;
      }
      case WDA_REGISTER_PE_CALLBACK :
      {
         VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_INFO_HIGH,
                           "Handling msg type WDA_REGISTER_PE_CALLBACK " );
         /*TODO: store the PE callback */
         /* Do Nothing? MSG Body should be freed at here */
         if(NULL != pMsg->bodyptr)
         {
            vos_mem_free(pMsg->bodyptr);
         }
         break;
      }
      case WDA_SYS_READY_IND :
      {
         VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_INFO_HIGH,
                                  "Handling msg type WDA_SYS_READY_IND " );
         pWDA->wdaState = WDA_READY_STATE;
         if(NULL != pMsg->bodyptr)
         {
            vos_mem_free(pMsg->bodyptr);
         }
         break;
      }
      case WDA_BEACON_FILTER_IND  :
      {
         WDA_SetBeaconFilterReq(pWDA, (tBeaconFilterMsg *)pMsg->bodyptr);
         break;
      }
      case WDA_BTC_SET_CFG:
      {
         /*TODO: handle this while dealing with BTC */
         VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_INFO_HIGH,
                                  "Handling msg type WDA_BTC_SET_CFG  " );
         /* Do Nothing? MSG Body should be freed at here */
         if(NULL != pMsg->bodyptr)
         {
            vos_mem_free(pMsg->bodyptr);
         }
         break;
      }
      case WDA_SIGNAL_BT_EVENT:
      {
         /*TODO: handle this while dealing with BTC */
         VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_INFO_HIGH,
                                  "Handling msg type WDA_SIGNAL_BT_EVENT  " );
         /* Do Nothing? MSG Body should be freed at here */
         if(NULL != pMsg->bodyptr)
         {
            vos_mem_free(pMsg->bodyptr);
         }
         break;
      }
      case WDA_CFG_RXP_FILTER_REQ:
      {
         WDA_ProcessConfigureRxpFilterReq(pWDA, 
                             (tSirWlanSetRxpFilters *)pMsg->bodyptr);
         break;
      }
      case WDA_SET_HOST_OFFLOAD:
      {
         WDA_ProcessHostOffloadReq(pWDA, (tSirHostOffloadReq *)pMsg->bodyptr);
         break;
      }
      case WDA_SET_KEEP_ALIVE:
      {
         WDA_ProcessKeepAliveReq(pWDA, (tSirKeepAliveReq *)pMsg->bodyptr);
         break;
      }
#ifdef WLAN_NS_OFFLOAD
      case WDA_SET_NS_OFFLOAD:
      {
         WDA_ProcessHostOffloadReq(pWDA, (tSirHostOffloadReq *)pMsg->bodyptr);
         break;
      }
#endif //WLAN_NS_OFFLOAD
      case WDA_ADD_STA_SELF_REQ:
      {
         WDA_ProcessAddStaSelfReq(pWDA, (tAddStaSelfParams *)pMsg->bodyptr);
         break;
      }
      case WDA_DEL_STA_SELF_REQ:
      {
         WDA_ProcessDelSTASelfReq(pWDA, (tDelStaSelfParams *)pMsg->bodyptr);
         break;
      }
      case WDA_WOWL_ADD_BCAST_PTRN:
      {
         WDA_ProcessWowlAddBcPtrnReq(pWDA, (tSirWowlAddBcastPtrn *)pMsg->bodyptr);
         break;
      }
      case WDA_WOWL_DEL_BCAST_PTRN:
      {
         WDA_ProcessWowlDelBcPtrnReq(pWDA, (tSirWowlDelBcastPtrn *)pMsg->bodyptr);
         break;
      }
      case WDA_WOWL_ENTER_REQ:
      {
         WDA_ProcessWowlEnterReq(pWDA, (tSirHalWowlEnterParams *)pMsg->bodyptr);
         break;
      }
      case WDA_WOWL_EXIT_REQ:
      {
         WDA_ProcessWowlExitReq(pWDA);
         break;
      }
      case WDA_TL_FLUSH_AC_REQ:
      {
         WDA_ProcessFlushAcReq(pWDA, (tFlushACReq *)pMsg->bodyptr);
         break;
      }
      case WDA_SIGNAL_BTAMP_EVENT:
      {
         WDA_ProcessBtAmpEventReq(pWDA, (tSmeBtAmpEvent *)pMsg->bodyptr);
         break;
      }
#ifdef WDA_UT
      case WDA_WDI_EVENT_MSG:
      {
         WDI_processEvent(pMsg->bodyptr,(void *)pMsg->bodyval);
         break ;
      }
#endif
      case WDA_UPDATE_BEACON_IND:
      {
          WDA_ProcessUpdateBeaconParams(pWDA, 
                                    (tUpdateBeaconParams *)pMsg->bodyptr);
          break;
      }
      case WDA_SEND_BEACON_REQ:
      {
          WDA_ProcessSendBeacon(pWDA, (tSendbeaconParams *)pMsg->bodyptr);
          break;
      }
      case WDA_UPDATE_PROBE_RSP_TEMPLATE_IND:
      {
          WDA_ProcessUpdateProbeRspTemplate(pWDA, 
                                      (tSendProbeRespParams *)pMsg->bodyptr);
          break;
      }
#if defined(WLAN_FEATURE_VOWIFI) || defined(FEATURE_WLAN_CCX)
      case WDA_SET_MAX_TX_POWER_REQ:
      {
         WDA_ProcessSetMaxTxPowerReq(pWDA,
                                       (tMaxTxPowerParams *)pMsg->bodyptr);
         break;
      }
#endif
#ifdef WLAN_FEATURE_P2P
      case WDA_SET_P2P_GO_NOA_REQ:
      {
         WDA_ProcessSetP2PGONOAReq(pWDA,
                                    (tP2pPsParams *)pMsg->bodyptr);
         break;
      }
#endif
      /* timer related messages */
      case WDA_TIMER_BA_ACTIVITY_REQ:
      {
         WDA_BaCheckActivity(pWDA) ;
         break ;
      }
#ifdef WLAN_FEATURE_VOWIFI_11R
      case WDA_AGGR_QOS_REQ:
      {
         WDA_ProcessAggrAddTSReq(pWDA, (tAggrAddTsParams *)pMsg->bodyptr);
         break;
      }
#endif /* WLAN_FEATURE_VOWIFI_11R */
#ifdef ANI_MANF_DIAG
      case WDA_FTM_CMD_REQ:
      {
         WDA_ProcessFTMCommand(pWDA, (tPttMsgbuffer *)pMsg->bodyptr) ;
         break ;
      }
#endif /* ANI_MANF_DIAG */
#ifdef FEATURE_OEM_DATA_SUPPORT
      case WDA_START_OEM_DATA_REQ:
      {
         WDA_ProcessStartOemDataReq(pWDA, (tStartOemDataReq *)pMsg->bodyptr) ;
         break;
      }
#endif /* FEATURE_OEM_DATA_SUPPORT */
      /* Tx Complete Time out Indication */
      case WDA_TX_COMPLETE_TIMEOUT_IND:
      {
         WDA_ProcessTxCompleteTimeOutInd(pWDA); 
         break;
      }         
      case WDA_WLAN_SUSPEND_IND:
      {
         WDA_ProcessWlanSuspendInd(pWDA, 
                        (tSirWlanSuspendParam *)pMsg->bodyptr) ;
         break;
      }
      case WDA_WLAN_RESUME_REQ:
      {
         WDA_ProcessWlanResumeReq(pWDA, 
                        (tSirWlanResumeParam *)pMsg->bodyptr) ;
         break;
      }
      
      case WDA_UPDATE_CF_IND:
      {
         vos_mem_free((v_VOID_t*)pMsg->bodyptr);
         pMsg->bodyptr = NULL;
         break;
      }
#ifdef FEATURE_WLAN_SCAN_PNO
      case WDA_SET_PNO_REQ:
      {
         WDA_ProcessSetPrefNetworkReq(pWDA, (tSirPNOScanReq *)pMsg->bodyptr);
         break;
      }
      case WDA_UPDATE_SCAN_PARAMS_REQ:
      {
         WDA_ProcessUpdateScanParams(pWDA, (tSirUpdateScanParams *)pMsg->bodyptr);
         break;
      }
      case WDA_SET_RSSI_FILTER_REQ:
      {
         WDA_ProcessSetRssiFilterReq(pWDA, (tSirSetRSSIFilterReq *)pMsg->bodyptr);
         break;
      }
#endif // FEATURE_WLAN_SCAN_PNO
      case WDA_SET_TX_PER_TRACKING_REQ:
      {
         WDA_ProcessSetTxPerTrackingReq(pWDA, (tSirTxPerTrackingParam *)pMsg->bodyptr);
         break;
      }
      
#ifdef WLAN_FEATURE_PACKET_FILTERING
      case WDA_8023_MULTICAST_LIST_REQ:
      {
         WDA_Process8023MulticastListReq(pWDA, (tSirRcvFltMcAddrList *)pMsg->bodyptr);
         break;
      }
      case WDA_RECEIVE_FILTER_SET_FILTER_REQ:
      {
         WDA_ProcessReceiveFilterSetFilterReq(pWDA, (tSirRcvPktFilterCfgType *)pMsg->bodyptr);
         break;
      }
      case WDA_PACKET_COALESCING_FILTER_MATCH_COUNT_REQ:
      {
         WDA_ProcessPacketFilterMatchCountReq(pWDA, (tpSirRcvFltPktMatchRsp)pMsg->bodyptr);
         break;
      }
      case WDA_RECEIVE_FILTER_CLEAR_FILTER_REQ:
      {
         WDA_ProcessReceiveFilterClearFilterReq(pWDA, (tSirRcvFltPktClearParam *)pMsg->bodyptr);
         break;
      }
#endif // WLAN_FEATURE_PACKET_FILTERING
  
  
      case WDA_TRANSMISSION_CONTROL_IND:
      {
         WDA_ProcessTxControlInd(pWDA, (tpTxControlParams)pMsg->bodyptr);
         break;
      }
      case WDA_SET_POWER_PARAMS_REQ:
      {
         WDA_ProcessSetPowerParamsReq(pWDA, (tSirSetPowerParamsReq *)pMsg->bodyptr);
         break;
      }
#ifdef WLAN_FEATURE_GTK_OFFLOAD
      case WDA_GTK_OFFLOAD_REQ:
      {
         WDA_ProcessGTKOffloadReq(pWDA, (tpSirGtkOffloadParams)pMsg->bodyptr);
         break;
      }

      case WDA_GTK_OFFLOAD_GETINFO_REQ:
      {
         WDA_ProcessGTKOffloadGetInfoReq(pWDA, (tpSirGtkOffloadGetInfoRspParams)pMsg->bodyptr);
         break;
      }
#endif //WLAN_FEATURE_GTK_OFFLOAD

      case WDA_SET_TM_LEVEL_REQ:
      {
         WDA_ProcessSetTmLevelReq(pWDA, (tAniSetTmLevelReq *)pMsg->bodyptr);
         break;
      }

      default:
      {
         VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_ERROR,
                                  "No Handling for msg type %x in WDA " 
                                  ,pMsg->type);
         /* Do Nothing? MSG Body should be freed at here */
         if(NULL != pMsg->bodyptr)
         {
            vos_mem_free(pMsg->bodyptr);
         }
         //WDA_VOS_ASSERT(0) ;
      }
   }
