switch (pMsg->type)
    {
        case eWNI_SME_START_REQ:
            __limProcessSmeStartReq(pMac, pMsgBuf);
            break;

        case eWNI_SME_SYS_READY_IND:
            bufConsumed = __limProcessSmeSysReadyInd(pMac, pMsgBuf);
            break;


        case eWNI_SME_START_BSS_REQ:
            bufConsumed = __limProcessSmeStartBssReq(pMac, pMsg);
            break;

        case eWNI_SME_SCAN_REQ:
            __limProcessSmeScanReq(pMac, pMsgBuf);

            break;

#ifdef FEATURE_OEM_DATA_SUPPORT
        case eWNI_SME_OEM_DATA_REQ:
            __limProcessSmeOemDataReq(pMac, pMsgBuf);

            break;
#endif
#ifdef WLAN_FEATURE_P2P
        case eWNI_SME_REMAIN_ON_CHANNEL_REQ:
            bufConsumed = limProcessRemainOnChnlReq(pMac, pMsgBuf);
            break;

        case eWNI_SME_UPDATE_NOA:
            __limProcessSmeNoAUpdate(pMac, pMsgBuf);
            break;
#endif
        case eWNI_SME_JOIN_REQ:
            __limProcessSmeJoinReq(pMac, pMsgBuf);

            break;

        case eWNI_SME_AUTH_REQ:
           // __limProcessSmeAuthReq(pMac, pMsgBuf);

            break;

        case eWNI_SME_REASSOC_REQ:
            __limProcessSmeReassocReq(pMac, pMsgBuf);

            break;

        case eWNI_SME_PROMISCUOUS_MODE_REQ:
            //__limProcessSmePromiscuousReq(pMac, pMsgBuf);

            break;

        case eWNI_SME_DISASSOC_REQ:
            __limProcessSmeDisassocReq(pMac, pMsgBuf);

            break;

        case eWNI_SME_DISASSOC_CNF:
        case eWNI_SME_DEAUTH_CNF:
            __limProcessSmeDisassocCnf(pMac, pMsgBuf);

            break;

        case eWNI_SME_DEAUTH_REQ:
            __limProcessSmeDeauthReq(pMac, pMsgBuf);

            break;

#if (WNI_POLARIS_FW_PACKAGE == ADVANCED) && defined(ANI_PRODUCT_TYPE_AP)
        case eWNI_SME_SWITCH_CHL_REQ:
        case eWNI_SME_SWITCH_CHL_CB_PRIMARY_REQ:
        case eWNI_SME_SWITCH_CHL_CB_SECONDARY_REQ:
            bufConsumed = __limProcessSmeSwitchChlReq(pMac, pMsg);
            break;
#endif


        case eWNI_SME_SETCONTEXT_REQ:
            __limProcessSmeSetContextReq(pMac, pMsgBuf);

            break;

        case eWNI_SME_REMOVEKEY_REQ:
            __limProcessSmeRemoveKeyReq(pMac, pMsgBuf);

            break;

        case eWNI_SME_STOP_BSS_REQ:
            bufConsumed = __limProcessSmeStopBssReq(pMac, pMsg);
            break;

        case eWNI_SME_ASSOC_CNF:
        case eWNI_SME_REASSOC_CNF:
            if (pMsg->type == eWNI_SME_ASSOC_CNF)
                PELOG1(limLog(pMac, LOG1, FL("Received ASSOC_CNF message\n"));)
            else
                PELOG1(limLog(pMac, LOG1, FL("Received REASSOC_CNF message\n"));)
#ifdef ANI_PRODUCT_TYPE_AP
            __limProcessSmeAssocCnf(pMac, pMsg->type, pMsgBuf);
#endif
            __limProcessSmeAssocCnfNew(pMac, pMsg->type, pMsgBuf);
            break;

        case eWNI_SME_ADDTS_REQ:
            PELOG1(limLog(pMac, LOG1, FL("Received ADDTS_REQ message\n"));)
            __limProcessSmeAddtsReq(pMac, pMsgBuf);
            break;

        case eWNI_SME_DELTS_REQ:
            PELOG1(limLog(pMac, LOG1, FL("Received DELTS_REQ message\n"));)
            __limProcessSmeDeltsReq(pMac, pMsgBuf);
            break;

        case SIR_LIM_ADDTS_RSP_TIMEOUT:
            PELOG1(limLog(pMac, LOG1, FL("Received SIR_LIM_ADDTS_RSP_TIMEOUT message \n"));)
            limProcessSmeAddtsRspTimeout(pMac, pMsg->bodyval);
            break;

        case eWNI_SME_STA_STAT_REQ:
        case eWNI_SME_AGGR_STAT_REQ:
        case eWNI_SME_GLOBAL_STAT_REQ:
        case eWNI_SME_STAT_SUMM_REQ:
            __limProcessSmeStatsRequest( pMac, pMsgBuf);
            //HAL consumes pMsgBuf. It will be freed there. Set bufConsumed to false.
            bufConsumed = FALSE;
            break;
        case eWNI_SME_GET_STATISTICS_REQ:
            __limProcessSmeGetStatisticsRequest( pMac, pMsgBuf);
            //HAL consumes pMsgBuf. It will be freed there. Set bufConsumed to false.
            bufConsumed = FALSE;
            break;              
        case eWNI_SME_DEL_BA_PEER_IND:
            limProcessSmeDelBaPeerInd(pMac, pMsgBuf);
            break;
        case eWNI_SME_GET_SCANNED_CHANNEL_REQ:
            limProcessSmeGetScanChannelInfo(pMac, pMsgBuf);
            break;
#ifdef WLAN_SOFTAP_FEATURE
        case eWNI_SME_GET_ASSOC_STAS_REQ:
            limProcessSmeGetAssocSTAsInfo(pMac, pMsgBuf);
            break;
        case eWNI_SME_TKIP_CNTR_MEAS_REQ:
            limProcessTkipCounterMeasures(pMac, pMsgBuf);
            break;

       case eWNI_SME_HIDE_SSID_REQ: 
            __limProcessSmeHideSSID(pMac, pMsgBuf);
            break;
       case eWNI_SME_UPDATE_APWPSIE_REQ: 
            __limProcessSmeUpdateAPWPSIEs(pMac, pMsgBuf);
            break;
        case eWNI_SME_GET_WPSPBC_SESSION_REQ:
             limProcessSmeGetWPSPBCSessions(pMac, pMsgBuf); 
             break;
         
        case eWNI_SME_SET_APWPARSNIEs_REQ:
              __limProcessSmeSetWPARSNIEs(pMac, pMsgBuf);        
              break;
#endif            
            
#if defined WLAN_FEATURE_VOWIFI 
        case eWNI_SME_NEIGHBOR_REPORT_REQ_IND:
        case eWNI_SME_BEACON_REPORT_RESP_XMIT_IND:
            __limProcessReportMessage(pMac, pMsg);
            break;
#endif

#if defined WLAN_FEATURE_VOWIFI_11R
       case eWNI_SME_FT_PRE_AUTH_REQ:
            bufConsumed = (tANI_BOOLEAN)limProcessFTPreAuthReq(pMac, pMsg);
            break;
       case eWNI_SME_FT_UPDATE_KEY:
            limProcessFTUpdateKey(pMac, pMsgBuf);
            break;

       case eWNI_SME_FT_AGGR_QOS_REQ:
            limProcessFTAggrQosReq(pMac, pMsgBuf);
            break;
#endif

#if defined FEATURE_WLAN_CCX
       case eWNI_SME_CCX_ADJACENT_AP_REPORT:
            limProcessAdjacentAPRepMsg ( pMac, pMsgBuf );
            break;
#endif
       case eWNI_SME_ADD_STA_SELF_REQ:
            __limProcessSmeAddStaSelfReq( pMac, pMsgBuf );
            break;
        case eWNI_SME_DEL_STA_SELF_REQ:
            __limProcessSmeDelStaSelfReq( pMac, pMsgBuf );
            break;

#ifdef WLAN_FEATURE_P2P
        case eWNI_SME_REGISTER_MGMT_FRAME_REQ:
            __limProcessSmeRegisterMgmtFrameReq( pMac, pMsgBuf );
            break;
#endif        
            

        default:
            vos_mem_free((v_VOID_t*)pMsg->bodyptr);
            pMsg->bodyptr = NULL;
            break;
    }
