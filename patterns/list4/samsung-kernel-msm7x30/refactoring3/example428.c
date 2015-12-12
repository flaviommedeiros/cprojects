switch (limMsg->type)
    {

        case SIR_LIM_UPDATE_BEACON:
            limUpdateBeacon(pMac);
            break;

        case SIR_CFG_PARAM_UPDATE_IND:
            /// CFG parameter updated
            if (limIsSystemInScanState(pMac))
            {
                // System is in DFS (Learn) mode
                // Defer processsing this message
                if (limDeferMsg(pMac, limMsg) != TX_SUCCESS)
                {
                    PELOGE(limLog(pMac, LOGE, FL("Unable to Defer message(0x%X) limSmeState %d (prev sme state %d) sysRole %d mlm state %d (prev mlm state %d)\n"),
                        limMsg->type, pMac->lim.gLimSmeState,  pMac->lim.gLimPrevSmeState,
                        pMac->lim.gLimSystemRole,  pMac->lim.gLimMlmState,  pMac->lim.gLimPrevMlmState);)
                    limLogSessionStates(pMac);
                    limPrintMsgName(pMac, LOGE, limMsg->type);
                }
            }
            else
            {
                limHandleCFGparamUpdate(pMac, limMsg->bodyval);
            }

            break;

        case WDA_INIT_SCAN_RSP:
            limProcessInitScanRsp(pMac, limMsg->bodyptr);
            break;

        case WDA_START_SCAN_RSP:
            limProcessStartScanRsp(pMac, limMsg->bodyptr);
            break;

        case WDA_END_SCAN_RSP:
            limProcessEndScanRsp(pMac, limMsg->bodyptr);
            break;

        case WDA_FINISH_SCAN_RSP:
            limProcessFinishScanRsp(pMac, limMsg->bodyptr);
            break;
#ifdef FEATURE_OEM_DATA_SUPPORT
        case WDA_START_OEM_DATA_RSP:
            limProcessOemDataRsp(pMac, limMsg->bodyptr);
            break;
#endif

        case WDA_SWITCH_CHANNEL_RSP:
            limProcessSwitchChannelRsp(pMac, limMsg->bodyptr);
            break;
            
#ifdef ANI_SIR_IBSS_PEER_CACHING
        case WDA_IBSS_STA_ADD:
            limIbssStaAdd(pMac, limMsg->bodyptr);
            break;
#endif
        case SIR_BB_XPORT_MGMT_MSG:
            // These messages are from Peer MAC entity.
#ifdef WLAN_DEBUG                
            pMac->lim.numBbt++;
#endif

#ifdef VOSS_ENABLED
            {
                v_U16_t     pktLen = 0;
                vos_pkt_t  *pVosPkt;
                VOS_STATUS  vosStatus;
                tSirMsgQ    limMsgNew;

                /* The original limMsg which we were deferring have the 
                 * bodyPointer point to 'BD' instead of 'Vos pkt'. If we don't make a copy
                 * of limMsg, then vos_pkt_peek_data will overwrite the limMsg->bodyPointer. 
                 * and next time when we try to process the msg, we will try to use 'BD' as 
                 * 'Vos Pkt' which will cause a crash
                 */
                palCopyMemory(pMac, (tANI_U8*)&limMsgNew, (tANI_U8*)limMsg, sizeof(tSirMsgQ));
                pVosPkt = (vos_pkt_t *)limMsgNew.bodyptr;
                vos_pkt_get_packet_length(pVosPkt, &pktLen);

                vosStatus = WDA_DS_PeekRxPacketInfo( pVosPkt, (v_PVOID_t *)&limMsgNew.bodyptr, VOS_FALSE );

                if( !VOS_IS_STATUS_SUCCESS(vosStatus) )
                {
                    vos_pkt_return_packet(pVosPkt);
                    break;

                }
                limHandle80211Frames(pMac, &limMsgNew, &deferMsg);

                if ( deferMsg == true )
                {
                    PELOG1(limLog(pMac, LOG1, FL("Defer message type=%X \n"), limMsg->type);)
                        if (limDeferMsg(pMac, limMsg) != TX_SUCCESS)
                        {
                            PELOGE(limLog(pMac, LOGE, FL("Unable to Defer message(0x%X) limSmeState %d (prev sme state %d) sysRole %d mlm state %d (prev mlm state %d)\n"),
                                limMsg->type, pMac->lim.gLimSmeState,  pMac->lim.gLimPrevSmeState,
                                pMac->lim.gLimSystemRole,  pMac->lim.gLimMlmState,  pMac->lim.gLimPrevMlmState);)
                            limLogSessionStates(pMac);
                            limPrintMsgName(pMac, LOGE, limMsg->type);
                            vos_pkt_return_packet(pVosPkt);
                        }
                }
                else
                {
                    /* PE is not deferring this 802.11 frame so we need to call vos_pkt_return. 
                     * Asumption here is when Rx mgmt frame processing is done,
                     * voss packet could be freed here.
                     */
                    vos_pkt_return_packet(pVosPkt);
                }
            }
#else
            limHandle80211Frames(pMac, limMsg);
#endif
            break;

        case eWNI_SME_SCAN_REQ:
#ifdef WLAN_FEATURE_P2P
        case eWNI_SME_REMAIN_ON_CHANNEL_REQ:
#endif
        case eWNI_SME_DISASSOC_REQ:
        case eWNI_SME_DEAUTH_REQ:
        case eWNI_SME_STA_STAT_REQ:
        case eWNI_SME_AGGR_STAT_REQ:
        case eWNI_SME_GLOBAL_STAT_REQ:
        case eWNI_SME_STAT_SUMM_REQ:
        case eWNI_SME_GET_SCANNED_CHANNEL_REQ:
        case eWNI_SME_GET_STATISTICS_REQ:
#ifdef FEATURE_OEM_DATA_SUPPORT
        case eWNI_SME_OEM_DATA_REQ:
#endif
            // These messages are from HDD
            limProcessNormalHddMsg(pMac, limMsg, true);  //need to response to hdd
            break;

        case eWNI_SME_SCAN_ABORT_IND:
            vos_mem_free((v_VOID_t *)limMsg->bodyptr);
            limMsg->bodyptr = NULL;
            limProcessAbortScanInd(pMac);
            break;

        case eWNI_SME_START_REQ:
        case eWNI_SME_SYS_READY_IND:
#ifndef WNI_ASKEY_NON_SUPPORT_FEATURE
        case eWNI_SME_JOIN_REQ:
#endif
        case eWNI_SME_AUTH_REQ:
        case eWNI_SME_REASSOC_REQ:
        case eWNI_SME_START_BSS_REQ:
        case eWNI_SME_STOP_BSS_REQ:
        case eWNI_SME_SWITCH_CHL_REQ:
        case eWNI_SME_SWITCH_CHL_CB_PRIMARY_REQ:
        case eWNI_SME_SWITCH_CHL_CB_SECONDARY_REQ:
        case eWNI_SME_SETCONTEXT_REQ:
        case eWNI_SME_REMOVEKEY_REQ:
#ifndef WNI_ASKEY_NON_SUPPORT_FEATURE
        case eWNI_SME_PROMISCUOUS_MODE_REQ:
#endif
        case eWNI_SME_DISASSOC_CNF:
        case eWNI_SME_DEAUTH_CNF:
        case eWNI_SME_ASSOC_CNF:
        case eWNI_SME_REASSOC_CNF:
        case eWNI_SME_ADDTS_REQ:
        case eWNI_SME_DELTS_REQ:
        case eWNI_SME_DEL_BA_PEER_IND:
        case eWNI_SME_SET_TX_POWER_REQ:
        case eWNI_SME_GET_TX_POWER_REQ:
        case eWNI_SME_GET_NOISE_REQ:
#ifdef WLAN_SOFTAP_FEATURE        
        case eWNI_SME_GET_ASSOC_STAS_REQ:
        case eWNI_SME_TKIP_CNTR_MEAS_REQ:
        case eWNI_SME_UPDATE_APWPSIE_REQ:
        case eWNI_SME_HIDE_SSID_REQ:
        case eWNI_SME_GET_WPSPBC_SESSION_REQ:
        case eWNI_SME_SET_APWPARSNIEs_REQ:
#endif
#if defined WLAN_FEATURE_VOWIFI
        case eWNI_SME_NEIGHBOR_REPORT_REQ_IND:
        case eWNI_SME_BEACON_REPORT_RESP_XMIT_IND:
#endif
#if defined FEATURE_WLAN_CCX
        case eWNI_SME_CCX_ADJACENT_AP_REPORT:
#endif
#ifdef WLAN_FEATURE_VOWIFI_11R
        case eWNI_SME_FT_UPDATE_KEY:
        case eWNI_SME_FT_PRE_AUTH_REQ:
        case eWNI_SME_FT_AGGR_QOS_REQ:
#endif
        case eWNI_SME_ADD_STA_SELF_REQ:
        case eWNI_SME_DEL_STA_SELF_REQ:
#ifdef WLAN_FEATURE_P2P
        case eWNI_SME_REGISTER_MGMT_FRAME_REQ:
        case eWNI_SME_UPDATE_NOA:
#endif
            // These messages are from HDD
            limProcessNormalHddMsg(pMac, limMsg, false);   //no need to response to hdd
            break;

        //Power Save Messages From HDD
        case eWNI_PMC_PWR_SAVE_CFG:
        case eWNI_PMC_ENTER_BMPS_REQ:
        case eWNI_PMC_EXIT_BMPS_REQ:
        case eWNI_PMC_ENTER_IMPS_REQ:
        case eWNI_PMC_EXIT_IMPS_REQ:
        case eWNI_PMC_ENTER_UAPSD_REQ:
        case eWNI_PMC_EXIT_UAPSD_REQ:
        case eWNI_PMC_ENTER_WOWL_REQ:
        case eWNI_PMC_EXIT_WOWL_REQ:
        case eWNI_PMC_WOWL_ADD_BCAST_PTRN:
        case eWNI_PMC_WOWL_DEL_BCAST_PTRN:
            pmmProcessMessage(pMac, limMsg);
            break;

        case eWNI_PMC_SMPS_STATE_IND :
        {
            if(limMsg->bodyptr){
            palFreeMemory(pMac->hHdd, (tANI_U8 *)limMsg->bodyptr);
            limMsg->bodyptr = NULL;
            }
        }
            break;
#if defined WLAN_FEATURE_P2P
        case eWNI_SME_SEND_ACTION_FRAME_IND:
            limSendP2PActionFrame(pMac, limMsg);
            palFreeMemory(pMac->hHdd, (tANI_U8 *)limMsg->bodyptr);
            limMsg->bodyptr = NULL;
            break;
        case eWNI_SME_ABORT_REMAIN_ON_CHAN_IND:
            limAbortRemainOnChan(pMac);
            palFreeMemory(pMac->hHdd, (tANI_U8 *)limMsg->bodyptr);
            limMsg->bodyptr = NULL;
            break;

        case SIR_HAL_P2P_NOA_ATTR_IND:
            {
                tpPESession psessionEntry = &pMac->lim.gpSession[0];  
                tANI_U8  i;
                
                
                limLog(pMac, LOGW, FL("Received message Noa_ATTR %x\n"), limMsg->type);
                for(i=0; i < pMac->lim.maxBssId; i++)
                {
                    if   ( (psessionEntry != NULL) && (pMac->lim.gpSession[i].valid) && 
                        (psessionEntry->pePersona == VOS_P2P_GO_MODE))
                    { //Save P2P attributes for P2P Go persona
                    
                        palCopyMemory(pMac->hHdd,&psessionEntry->p2pGoPsUpdate, limMsg->bodyptr,sizeof(tSirP2PNoaAttr));
                        
                        
                        limLog(pMac, LOGE, FL(" &psessionEntry->bssId%02x:%02x:%02x:%02x:%02x:%02x ctWin=%d oppPsFlag=%d\n"),
                                     psessionEntry->bssId[0],
                                     psessionEntry->bssId[1],
                                     psessionEntry->bssId[2],
                                     psessionEntry->bssId[3],
                                     psessionEntry->bssId[4],
                                     psessionEntry->bssId[5],                                     
                                     psessionEntry->p2pGoPsUpdate.ctWin,
                                     psessionEntry->p2pGoPsUpdate.oppPsFlag);

                        limLog(pMac, LOGE, FL(" uNoa1IntervalCnt=%d uNoa1Duration=%d uNoa1Interval=%d uNoa1StartTime=%d\n"),
                                     psessionEntry->p2pGoPsUpdate.uNoa1IntervalCnt,
                                     psessionEntry->p2pGoPsUpdate.uNoa1Duration,
                                     psessionEntry->p2pGoPsUpdate.uNoa1Interval,
                                     psessionEntry->p2pGoPsUpdate.uNoa1StartTime);

                        
                        break;
                    }
                }
                
            }
            palFreeMemory(pMac->hHdd, (tANI_U8 *)limMsg->bodyptr);
            limMsg->bodyptr = NULL;
            
            break;

            
#endif
        /* eWNI_SME_PRE_CHANNEL_SWITCH_FULL_POWER Message comes after the
         * device comes out of full power for the full power request sent 
         * because of channel switch with switch count as 0, so call the same 
         * function used in timeout case(i.e SIR_LIM_CHANNEL_SWITCH_TIMEOUT) 
         * for switching the channel*/
        case eWNI_SME_PRE_CHANNEL_SWITCH_FULL_POWER:
            if ( !tx_timer_running(&pMac->lim.limTimers.gLimChannelSwitchTimer) )
            {  
                limProcessChannelSwitchTimeout(pMac);
            }
            palFreeMemory(pMac->hHdd, (tANI_U8 *)limMsg->bodyptr);
            limMsg->bodyptr = NULL;
            break;

        //Power Save Related Messages From HAL
        case WDA_ENTER_BMPS_RSP:
        case WDA_EXIT_BMPS_RSP:
        case WDA_EXIT_BMPS_IND:
        case WDA_ENTER_IMPS_RSP:
        case WDA_EXIT_IMPS_RSP:
        case WDA_ENTER_UAPSD_RSP:
        case WDA_EXIT_UAPSD_RSP:
        case WDA_WOWL_ENTER_RSP:
        case WDA_WOWL_EXIT_RSP:
            pmmProcessMessage(pMac, limMsg);
            break;

        case WDA_LOW_RSSI_IND:
            //limHandleLowRssiInd(pMac);
            break;

        case WDA_BMPS_STATUS_IND:
            limHandleBmpsStatusInd(pMac);
            break;

        case WDA_MISSED_BEACON_IND:
            limHandleMissedBeaconInd(pMac);
            break;
        case WDA_MIC_FAILURE_IND:
           limMicFailureInd(pMac, limMsg);
           palFreeMemory(pMac->hHdd, (tANI_U8 *)limMsg->bodyptr);
           limMsg->bodyptr = NULL;
           break;
    

#if (WNI_POLARIS_FW_PACKAGE == ADVANCED) && defined(ANI_PRODUCT_TYPE_AP)
        case eWNI_SME_MEASUREMENT_REQ:
        case eWNI_SME_SET_WDS_INFO_REQ:
            // Message to support ANI feature set
            // These are handled by LMM sub module
            if (limIsSystemInScanState(pMac))
            {
                // System is in DFS (Learn) mode
                // Defer processsing this message
                if (limDeferMsg(pMac, limMsg) != TX_SUCCESS)
                {
                    pMac->lim.numSme++;
                    PELOGE(limLog(pMac, LOGE, FL("Unable to Defer message(0x%X) limSmeState %d (prev sme state %d) sysRole %d mlm state %d (prev mlm state %d)\n"),
                        limMsg->type, pMac->lim.gLimSmeState,  pMac->lim.gLimPrevSmeState,
                        pMac->lim.gLimSystemRole,  pMac->lim.gLimMlmState,  pMac->lim.gLimPrevMlmState);)
                    limLogSessionStates(pMac);
                    limPrintMsgName(pMac, LOGE, limMsg->type);
                    // Release body
                    palFreeMemory( pMac->hHdd, (tANI_U8 *) limMsg->bodyptr);
                    break;
                }

                if (limMsg->type == eWNI_SME_MEASUREMENT_REQ)
                {
                    if (GET_LIM_PROCESS_DEFD_MESGS(pMac))
                    {
                        //Set the resume channel to Any valid channel (invalid). 
                        //This will instruct HAL to set it to any previous valid channel.
                        peSetResumeChannel(pMac, 0, 0);
                        limSendHalFinishScanReq(pMac, eLIM_HAL_FINISH_LEARN_WAIT_STATE);
                    }
                }
            }
            else
            {
                pMac->lim.numSme++;
                limProcessLmmMessages(pMac,
                                      limMsg->type,
                                      (tANI_U32 *) limMsg->bodyptr);

                // Release body
                palFreeMemory( pMac->hHdd, (tANI_U8 *) limMsg->bodyptr);
            }
            break;

        case SIR_LIM_LEARN_INTERVAL_TIMEOUT:
            if ((pMac->lim.gLimSystemRole == eLIM_STA_ROLE) &&
                ((pMac->lim.gLimMlmState == eLIM_MLM_WT_DEL_STA_RSP_STATE) ||
                 (pMac->lim.gLimMlmState == eLIM_MLM_WT_DEL_BSS_RSP_STATE)))
            {
                // BP is in the process of cleaning up
                // its state with previously assocaited AP.
                // Discard processsing this message.
                PELOG1(limLog(pMac, LOG1,
                       FL("Discarding LEARN_INTERVAL_TO message\n"));)
            }
            else
                limProcessLmmMessages(pMac,
                                      limMsg->type,
                                      (tANI_U32 *) limMsg->bodyptr);
            break;

        case SIR_LIM_MEASUREMENT_IND_TIMEOUT:
        case SIR_LIM_LEARN_DURATION_TIMEOUT:
            // These measurement related timeouts are
            // handled by LMM sub module.
            limProcessLmmMessages(pMac,
                                  limMsg->type,
                                  (tANI_U32 *) limMsg->bodyptr);

            break;

        case SIR_LIM_RADAR_DETECT_IND:
            limDetectRadar(pMac, (tANI_U32*)limMsg->bodyptr);
            palFreeMemory( pMac->hHdd, (tANI_U32*)limMsg->bodyptr);
            break;

#endif

        case SIR_LIM_ADDTS_RSP_TIMEOUT:
            limProcessSmeReqMessages(pMac,limMsg);
            break;
#ifdef FEATURE_WLAN_CCX
        case SIR_LIM_CCX_TSM_TIMEOUT:
            limProcessTsmTimeoutHandler(pMac,limMsg);
            break;
        case WDA_TSM_STATS_RSP:
            limProcessHalCcxTsmRsp(pMac, limMsg);
            break;
#endif
        case WDA_ADD_TS_RSP:
            limProcessHalAddTsRsp(pMac, limMsg);
            break;

        case SIR_LIM_DEL_TS_IND:
          limProcessDelTsInd(pMac, limMsg);
        case SIR_LIM_ADD_BA_IND:
            limProcessAddBaInd(pMac, limMsg);
            break;
        case SIR_LIM_DEL_BA_ALL_IND:
            limDelAllBASessions(pMac);  // refer notes and change
            break;
        case SIR_LIM_DEL_BA_IND:
            limProcessMlmHalBADeleteInd( pMac, limMsg );
            break;

         case SIR_LIM_BEACON_GEN_IND: {
#ifdef ANI_PRODUCT_TYPE_AP
                    if (pMac->lim.gLimSystemRole == eLIM_AP_ROLE)
                        pmmUpdateTIM(pMac, (tpBeaconGenParams)limMsg->bodyptr);
#endif

#ifdef WLAN_SOFTAP_FEATURE
                if( pMac->lim.gLimSystemRole != eLIM_AP_ROLE )
#endif                  
                    schProcessPreBeaconInd(pMac, limMsg);    

                }
                break;

        case SIR_LIM_DELETE_STA_CONTEXT_IND:
            limDeleteStaContext(pMac, limMsg);
            break;

        case SIR_LIM_MIN_CHANNEL_TIMEOUT:
        case SIR_LIM_MAX_CHANNEL_TIMEOUT:
        case SIR_LIM_PERIODIC_PROBE_REQ_TIMEOUT:
        case SIR_LIM_JOIN_FAIL_TIMEOUT:
        case SIR_LIM_AUTH_FAIL_TIMEOUT:
        case SIR_LIM_AUTH_RSP_TIMEOUT:
        case SIR_LIM_ASSOC_FAIL_TIMEOUT:
        case SIR_LIM_REASSOC_FAIL_TIMEOUT:
#ifdef WLAN_FEATURE_VOWIFI_11R
        case SIR_LIM_FT_PREAUTH_RSP_TIMEOUT:
#endif
#ifdef WLAN_FEATURE_P2P
        case SIR_LIM_REMAIN_CHN_TIMEOUT:
#endif
            // These timeout messages are handled by MLM sub module

            limProcessMlmReqMessages(pMac,
                                     limMsg);

            break;

        case SIR_LIM_HEART_BEAT_TIMEOUT:
            /** check if heart beat failed, even if one Beacon
                    * is rcvd within the Heart Beat interval continue
                  * normal processing
                    */

            #if 0 
            PELOG1(limLog(pMac, LOG1, FL("Heartbeat timeout, SME %d, MLME %d, #bcn %d\n"),
                   pMac->lim.gLimSmeState, pMac->lim.gLimMlmState,
                   pMac->lim.gLimRxedBeaconCntDuringHB);)

            if(pMac->lim.gLimSystemRole == eLIM_STA_IN_IBSS_ROLE)
                limIbssHeartBeatHandle(pMac); //HeartBeat for peers.
            else
                /**
                        * Heartbeat failure occurred on STA
                      * This is handled by LMM sub module.
                        */
                limHandleHeartBeatFailure(pMac);

            break;
            #endif //TO SUPPORT BT-AMP

            limHandleHeartBeatTimeout(pMac);
            break;
           
        case SIR_LIM_PROBE_HB_FAILURE_TIMEOUT:
            limHandleHeartBeatFailureTimeout(pMac);            
            break;

        case SIR_LIM_CHANNEL_SCAN_TIMEOUT:
#if defined(ANI_PRODUCT_TYPE_CLIENT) || defined(ANI_AP_CLIENT_SDK)
            /**
             * Background scan timeout occurred on STA.
             * This is handled by LMM sub module.
             */
             limDeactivateAndChangeTimer(pMac, eLIM_BACKGROUND_SCAN_TIMER);

            //We will do background scan even in bcnps mode
            //if (pMac->sys.gSysEnableScanMode)
            pMac->lim.gLimReportBackgroundScanResults = FALSE;
            limTriggerBackgroundScan(pMac);
#endif
            break;

#ifdef ANI_PRODUCT_TYPE_AP
        case SIR_LIM_PREAUTH_CLNUP_TIMEOUT:
            if (limIsSystemInScanState(pMac))
            {
                // System is in DFS (Learn) mode
                // Defer processsing this message
                if (limDeferMsg(pMac, limMsg) != TX_SUCCESS)
                {
                    PELOGE(limLog(pMac, LOGE, FL("Unable to Defer message(0x%X) limSmeState %d (prev sme state %d) sysRole %d mlm state %d (prev mlm state %d)\n"),
                        limMsg->type, pMac->lim.gLimSmeState,  pMac->lim.gLimPrevSmeState,
                        pMac->lim.gLimSystemRole,  pMac->lim.gLimMlmState,  pMac->lim.gLimPrevMlmState);)
                    limLogSessionStates(pMac);
                }
            }
            else
            {
                // Pre-authentication context cleanup timeout message
                limPreAuthClnupHandler(pMac);
            }

            break;
#endif

        case SIR_LIM_HASH_MISS_THRES_TIMEOUT:

            /*
            ** clear the credit to the send disassociate frame bucket
            **/

            pMac->lim.gLimDisassocFrameCredit = 0;
            break;

        case SIR_LIM_CNF_WAIT_TIMEOUT:

            /*
            ** Does not receive CNF or dummy packet
            **/
            limHandleCnfWaitTimeout(pMac, (tANI_U16) limMsg->bodyval);

            break;

        case SIR_LIM_KEEPALIVE_TIMEOUT:
            limSendKeepAliveToPeer(pMac);

            break;

        case SIR_LIM_RETRY_INTERRUPT_MSG:
            // Message from ISR upon TFP's max retry limit interrupt

            break;

        case SIR_LIM_INV_KEY_INTERRUPT_MSG:
            // Message from ISR upon SP's Invalid session key interrupt

            break;

        case SIR_LIM_KEY_ID_INTERRUPT_MSG:
            // Message from ISR upon SP's Invalid key ID interrupt

            break;

        case SIR_LIM_REPLAY_THRES_INTERRUPT_MSG:
            // Message from ISR upon SP's Replay threshold interrupt

            break;

        case SIR_LIM_CHANNEL_SWITCH_TIMEOUT:
            limProcessChannelSwitchTimeout(pMac);
            break;

        case SIR_LIM_QUIET_TIMEOUT:
            limProcessQuietTimeout(pMac);
            break;

        case SIR_LIM_QUIET_BSS_TIMEOUT:
            limProcessQuietBssTimeout(pMac);
            break;

#ifdef WLAN_SOFTAP_FEATURE
        case SIR_LIM_UPDATE_OLBC_CACHEL_TIMEOUT:
            limHandleUpdateOlbcCache(pMac);
            break;
#if 0
        case SIR_LIM_WPS_OVERLAP_TIMEOUT:
            limProcessWPSOverlapTimeout(pMac);
            break;
#endif

#endif

        case WDA_ADD_BSS_RSP:
            limProcessMlmAddBssRsp( pMac, limMsg );
            break;

        case WDA_ADD_STA_RSP:

            //call a wrapper by paasing bodyptr, their get sessionID and and call proper function from there.
            limProcessAddStaRsp(pMac,limMsg);
            break;

        case WDA_DELETE_STA_RSP:
            limProcessMlmDelStaRsp(pMac, limMsg);
            break;

        case WDA_ADD_STA_SELF_RSP:
            limProcessAddStaSelfRsp(pMac, limMsg);
            break; 
        case WDA_DEL_STA_SELF_RSP:
            limProcessDelStaSelfRsp(pMac, limMsg);
            break;

        case WDA_DELETE_BSS_RSP:
            limHandleDeleteBssRsp(pMac,limMsg); //wrapper routine to handle delete bss response 
            break;

        case WDA_SET_BSSKEY_RSP:
        case WDA_SET_STA_BCASTKEY_RSP:
            limProcessMlmSetBssKeyRsp( pMac, limMsg );
            break;
        case WDA_SET_STAKEY_RSP:
            limProcessMlmSetStaKeyRsp( pMac, limMsg );
            break;
        case WDA_REMOVE_BSSKEY_RSP:
        case WDA_REMOVE_STAKEY_RSP:
            limProcessMlmRemoveKeyRsp( pMac, limMsg );
            break;
        case WDA_ADDBA_RSP:
            limProcessMlmHalAddBARsp( pMac, limMsg );
            break;

        case WDA_STA_STAT_RSP:
        case WDA_AGGR_STAT_RSP:
        case WDA_GLOBAL_STAT_RSP:
        case WDA_STAT_SUMM_RSP:
            limSendSmeStatsRsp ( pMac, limMsg->type, (void *)limMsg->bodyptr);
            break;

        case WDA_GET_STATISTICS_RSP:
            limSendSmePEStatisticsRsp ( pMac, limMsg->type, (void *)limMsg->bodyptr);
            break;

        case WDA_SET_MIMOPS_RSP:            //limProcessSetMimoRsp(pMac, limMsg);
        case WDA_SET_TX_POWER_RSP:          //limProcessSetTxPowerRsp(pMac, limMsg);
        case WDA_GET_TX_POWER_RSP:          //limProcessGetTxPowerRsp(pMac, limMsg);
        case WDA_GET_NOISE_RSP:
            vos_mem_free((v_VOID_t*)limMsg->bodyptr);
            limMsg->bodyptr = NULL;
            //limProcessGetNoiseRsp(pMac, limMsg);
            break;

        case WDA_SET_MAX_TX_POWER_RSP:
#if defined WLAN_FEATURE_VOWIFI
            rrmSetMaxTxPowerRsp( pMac, limMsg );
#endif
            if(limMsg->bodyptr != NULL)
            {
               vos_mem_free((v_VOID_t*)limMsg->bodyptr);
               limMsg->bodyptr = NULL;
            }
            break;

#ifdef ANI_CHIPSET_VOLANS
       case SIR_LIM_ADDR2_MISS_IND:
       {
           limLog(pMac, LOGE,
                   FL("Addr2 mismatch interrupt received %X\n"),
                   limMsg->type);
           /*a message from HAL indicating addr2 mismatch interrupt occurred
             limMsg->bodyptr contains only pointer to 48-bit addr2 field*/
           //Dinesh fix this. the third parameter should be sessionentry.
           //limHandleUnknownA2IndexFrames(pMac, (void *)limMsg->bodyptr); 

           /*Free message body pointer*/ 
           vos_mem_free((v_VOID_t *)(limMsg->bodyptr));
           break;
       }
#endif

#ifdef WLAN_FEATURE_VOWIFI_11R
    case WDA_AGGR_QOS_RSP:
       limProcessFTAggrQoSRsp( pMac, limMsg );
       break;
#endif

    case WDA_SET_LINK_STATE_RSP:
       linkStateParams = (tLinkStateParams *)limMsg->bodyptr;
#if defined WLAN_FEATURE_VOWIFI_11R
       pSession = linkStateParams->session;
       if(linkStateParams->ft)
       {
          limSendReassocReqWithFTIEsMgmtFrame(pMac, 
                                              pSession->pLimMlmReassocReq,
                                              pSession); 
       }
#endif
       if( linkStateParams->callback )
       {
          linkStateParams->callback( pMac, linkStateParams->callbackArg );
       }
       vos_mem_free((v_VOID_t *)(limMsg->bodyptr));
       break;

#ifdef WLAN_FEATURE_PACKET_FILTERING
    case WDA_PACKET_COALESCING_FILTER_MATCH_COUNT_RSP:
        pmmProcessMessage(pMac, limMsg);
        break;
#endif // WLAN_FEATURE_PACKET_FILTERING

#ifdef WLAN_FEATURE_GTK_OFFLOAD
    case WDA_GTK_OFFLOAD_GETINFO_RSP:
        pmmProcessMessage(pMac, limMsg);
        break;
#endif // WLAN_FEATURE_GTK_OFFLOAD

    default:
        vos_mem_free((v_VOID_t*)limMsg->bodyptr);
        limMsg->bodyptr = NULL;
        // Unwanted messages
        // Log error
        limLog(pMac, LOGE,
                FL("Discarding unexpected message received %X\n"),
                limMsg->type);
        limPrintMsgName(pMac, LOGE, limMsg->type);
        break;

    }
