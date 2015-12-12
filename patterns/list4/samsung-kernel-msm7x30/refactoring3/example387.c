switch(roamStatus)
    {
        case eCSR_ROAM_SESSION_OPENED:
        {
            /* tHalHandle */
            tHalHandle hHal = VOS_GET_HAL_CB(sapContext->pvosGCtx);

            if (NULL == hHal)
            {
               VOS_TRACE( VOS_MODULE_ID_SAP, VOS_TRACE_LEVEL_ERROR,
                          "In %s invalid hHal", __FUNCTION__);
               halStatus = eHAL_STATUS_FAILED_ALLOC;
            }
            else
            {
               VOS_TRACE( VOS_MODULE_ID_SAP, VOS_TRACE_LEVEL_INFO_HIGH,
                          "In %s calling sme_RoamConnect with eCSR_BSS_TYPE_INFRA_AP", __FUNCTION__);
               sapContext->isSapSessionOpen = eSAP_TRUE;
               halStatus = sme_RoamConnect(hHal, sapContext->sessionId,
                                           &sapContext->csrRoamProfile,
                                           &sapContext->csrRoamId);
            }
            break;
        }

        case eCSR_ROAM_INFRA_IND:
            VOS_TRACE( VOS_MODULE_ID_SAP, VOS_TRACE_LEVEL_INFO_HIGH, "In %s, CSR roamStatus = %s (%d)\n",
                      __FUNCTION__, "eCSR_ROAM_INFRA_IND", roamStatus);
            if(roamResult == eCSR_ROAM_RESULT_INFRA_START_FAILED)
            {
                /* Fill in the event structure */ 
                sapEvent.event = eSAP_MAC_START_FAILS; 
                sapEvent.params = pCsrRoamInfo;
                sapEvent.u1 = roamStatus;
                sapEvent.u2 = roamResult; 
                
                /* Handle event */ 
                vosStatus = sapFsm(sapContext, &sapEvent);
                if(!VOS_IS_STATUS_SUCCESS(vosStatus))
                {
                    halStatus = eHAL_STATUS_FAILURE;
                }
            }
            break;

        case eCSR_ROAM_LOSTLINK:
            VOS_TRACE( VOS_MODULE_ID_SAP, VOS_TRACE_LEVEL_INFO_HIGH, "In %s, CSR roamStatus = %s (%d)\n",
                       __FUNCTION__, "eCSR_ROAM_LOSTLINK", roamStatus);
            break;

        case eCSR_ROAM_MIC_ERROR_IND:
            VOS_TRACE( VOS_MODULE_ID_SAP, VOS_TRACE_LEVEL_INFO_HIGH, "In %s, CSR roamStatus = %s (%d)\n",
                __FUNCTION__, "eCSR_ROAM_MIC_ERROR_IND", roamStatus);
            break;

        case eCSR_ROAM_SET_KEY_COMPLETE:
            VOS_TRACE( VOS_MODULE_ID_SAP, VOS_TRACE_LEVEL_INFO_HIGH, "In %s, CSR roamStatus = %s (%d)\n",
                __FUNCTION__, "eCSR_ROAM_SET_KEY_COMPLETE", roamStatus);
            if (roamResult == eCSR_ROAM_RESULT_FAILURE )
            {
                /* Format the SET KEY complete information pass to HDD... */
                sapSignalHDDevent(sapContext, pCsrRoamInfo, eSAP_STA_SET_KEY_EVENT,(v_PVOID_t) eSAP_STATUS_FAILURE);
            }
            break;

        case eCSR_ROAM_REMOVE_KEY_COMPLETE:
            VOS_TRACE( VOS_MODULE_ID_SAP, VOS_TRACE_LEVEL_INFO_HIGH, "In %s, CSR roamStatus = %s (%d)\n",
                        __FUNCTION__, "eCSR_ROAM_REMOVE_KEY_COMPLETE", roamStatus);
            if (roamResult == eCSR_ROAM_RESULT_FAILURE )
            {
                /* Format the SET KEY complete information pass to HDD... */
                sapSignalHDDevent(sapContext, pCsrRoamInfo, eSAP_STA_DEL_KEY_EVENT, (v_PVOID_t)eSAP_STATUS_FAILURE);
            }
            break;

        case eCSR_ROAM_ASSOCIATION_COMPLETION:
            VOS_TRACE( VOS_MODULE_ID_SAP, VOS_TRACE_LEVEL_INFO_HIGH, "In %s, CSR roamStatus = %s (%d)\n",
                       __FUNCTION__, "eCSR_ROAM_ASSOCIATION_COMPLETION", roamStatus);
            if (roamResult == eCSR_ROAM_RESULT_FAILURE )
            {
                /* Format the SET KEY complete information pass to HDD... */
                sapSignalHDDevent(sapContext, pCsrRoamInfo, eSAP_STA_REASSOC_EVENT, (v_PVOID_t)eSAP_STATUS_FAILURE);
            }
            break;

        case eCSR_ROAM_DISASSOCIATED:
            VOS_TRACE( VOS_MODULE_ID_SAP, VOS_TRACE_LEVEL_INFO_HIGH, "In %s, CSR roamStatus = %s (%d)\n",
                       __FUNCTION__, "eCSR_ROAM_DISASSOCIATED", roamStatus);
            if (roamResult == eCSR_ROAM_RESULT_MIC_FAILURE)
            {
                /* Format the MIC failure event to return... */
                sapSignalHDDevent(sapContext, pCsrRoamInfo, eSAP_STA_MIC_FAILURE_EVENT,(v_PVOID_t) eSAP_STATUS_FAILURE);
            }
            break;
                        
        case eCSR_ROAM_WPS_PBC_PROBE_REQ_IND:
            VOS_TRACE( VOS_MODULE_ID_SAP, VOS_TRACE_LEVEL_INFO_HIGH, "In %s, CSR roamStatus = %s (%d)\n",
                       __FUNCTION__, "eCSR_ROAM_WPS_PBC_PROBE_REQ_IND", roamStatus);
            break;        

#ifdef WLAN_FEATURE_P2P
        case eCSR_ROAM_INDICATE_MGMT_FRAME:
            sapSignalHDDevent(sapContext, pCsrRoamInfo, 
                              eSAP_INDICATE_MGMT_FRAME, 
                              (v_PVOID_t) eSAP_STATUS_SUCCESS);
            break;
        case eCSR_ROAM_REMAIN_CHAN_READY:
            sapSignalHDDevent(sapContext, pCsrRoamInfo, 
                              eSAP_REMAIN_CHAN_READY, 
                              (v_PVOID_t) eSAP_STATUS_SUCCESS);
            break;
        case eCSR_ROAM_SEND_ACTION_CNF:
            sapSignalHDDevent(sapContext, pCsrRoamInfo, 
                            eSAP_SEND_ACTION_CNF, 
                            (v_PVOID_t)(( roamResult == eCSR_ROAM_RESULT_NONE) ?
                            eSAP_STATUS_SUCCESS : eSAP_STATUS_FAILURE));
            break;
#endif

        default:
            VOS_TRACE( VOS_MODULE_ID_SAP, VOS_TRACE_LEVEL_ERROR, "In %s, CSR roamStatus not handled roamStatus = %s (%d)\n",
                       __FUNCTION__, get_eRoamCmdStatus_str(roamStatus), roamStatus);
            break;

    }
