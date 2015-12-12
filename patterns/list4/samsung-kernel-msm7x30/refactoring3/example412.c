switch (pMsg->type)
    {
        case eWNI_PMC_PWR_SAVE_CFG:
        {
            tpSirPowerSaveCfg pPSCfg;
            tSirMbMsg *pMbMsg = (tSirMbMsg *)pMsg->bodyptr;

            if (palAllocateMemory(pMac->hHdd, (void **)&pPSCfg, sizeof(tSirPowerSaveCfg)) != eHAL_STATUS_SUCCESS)
            {
                pmmLog(pMac, LOGP, "PMM: Not able to allocate memory for PMC Config\n");
            }
            (void) palCopyMemory(pMac->hHdd, pPSCfg, pMbMsg->data, sizeof(tSirPowerSaveCfg));
            (void) pmmSendPowerSaveCfg(pMac, pPSCfg);

            // sending beacon filtering information down to HAL
            if (limSendBeaconFilterInfo(pMac) != eSIR_SUCCESS)
                pmmLog(pMac, LOGE, FL("Fail to send Beacon Filter Info \n"));
        }
            break;

        case eWNI_PMC_ENTER_BMPS_REQ:
            pmmInitBmpsPwrSave(pMac);
            break;

        case WDA_ENTER_BMPS_RSP:
            pmmInitBmpsResponseHandler(pMac, (eHalStatus)pMsg->bodyval);
            break;

        case eWNI_PMC_EXIT_BMPS_REQ:
        {
            tpExitBmpsInfo  pExitBmpsInfo;
            tSirMbMsg      *pMbMsg = (tSirMbMsg *)pMsg->bodyptr;

            if (palAllocateMemory(pMac->hHdd, (void **)&pExitBmpsInfo, sizeof(tExitBmpsInfo)) != eHAL_STATUS_SUCCESS)
            {
                pmmLog(pMac, LOGP, "PMM: Failed to allocate memory for Exit BMPS Info \n");
            }
            (void) palCopyMemory(pMac->hHdd, pExitBmpsInfo, pMbMsg->data, sizeof(tExitBmpsInfo));
            (void) pmmExitBmpsRequestHandler(pMac, pExitBmpsInfo);
        }
            break;

        case WDA_EXIT_BMPS_RSP:
            pmmExitBmpsResponseHandler(pMac, pMsg);
            break;

        case WDA_EXIT_BMPS_IND:
            pmmExitBmpsIndicationHandler(pMac, SIR_PM_ACTIVE_MODE, (eHalStatus)pMsg->bodyval);
            break;

        case eWNI_PMC_ENTER_IMPS_REQ:
            pmmEnterImpsRequestHandler(pMac);
            break;

        case WDA_ENTER_IMPS_RSP:
            pmmEnterImpsResponseHandler(pMac, (eHalStatus)pMsg->bodyval);
            break;

        case eWNI_PMC_EXIT_IMPS_REQ:
            pmmExitImpsRequestHandler(pMac);
            break;

        case WDA_EXIT_IMPS_RSP:
            pmmExitImpsResponseHandler(pMac, (eHalStatus)pMsg->bodyval);
            break;

        case eWNI_PMC_ENTER_UAPSD_REQ:
            pmmEnterUapsdRequestHandler(pMac);
            break;

        case WDA_ENTER_UAPSD_RSP:
            pmmEnterUapsdResponseHandler(pMac, pMsg);
            break;

        case eWNI_PMC_EXIT_UAPSD_REQ:
            pmmExitUapsdRequestHandler(pMac);
            break;

        case WDA_EXIT_UAPSD_RSP:
            pmmExitUapsdResponseHandler(pMac, (eHalStatus)pMsg->bodyval);
            break;

        case eWNI_PMC_WOWL_ADD_BCAST_PTRN:
            pmmSendWowlAddBcastPtrn(pMac, pMsg);
            break;

        case eWNI_PMC_WOWL_DEL_BCAST_PTRN:
            pmmSendWowlDelBcastPtrn(pMac, pMsg);
            break;

        case eWNI_PMC_ENTER_WOWL_REQ:
            pmmEnterWowlRequestHandler(pMac, pMsg);
            break;

        case WDA_WOWL_ENTER_RSP:
            pmmEnterWowlanResponseHandler(pMac, pMsg);
            break;

        case eWNI_PMC_EXIT_WOWL_REQ:
            pmmExitWowlanRequestHandler(pMac);
            break;

        case WDA_WOWL_EXIT_RSP:
            pmmExitWowlanResponseHandler(pMac, (eHalStatus)pMsg->bodyval);
            break;
#ifdef WLAN_FEATURE_PACKET_FILTERING
        case WDA_PACKET_COALESCING_FILTER_MATCH_COUNT_RSP:
            pmmFilterMatchCountResponseHandler(pMac, pMsg);
            break;
#endif // WLAN_FEATURE_PACKET_FILTERING


#ifdef WLAN_FEATURE_GTK_OFFLOAD
        case WDA_GTK_OFFLOAD_GETINFO_RSP:
            pmmGTKOffloadGetInfoResponseHandler(pMac, pMsg);
            break;
#endif // WLAN_FEATURE_GTK_OFFLOAD

        default:
            PELOGW(pmmLog(pMac, LOGW, 
                FL("PMM: Unknown message in pmmMsgQ type %d, potential memory leak!!\n"),
                pMsg->type);)
    }
