switch (pSchMsg->type)
    {
#ifdef FIXME_GEN6
        case SIR_BB_XPORT_MGMT_MSG:
            pMac->sch.gSchBBXportRcvCnt++;


#if defined (ANI_OS_TYPE_LINUX) || defined (ANI_OS_TYPE_OSX)
            {
                palGetPacketDataPtr( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, pSchMsg->bodyptr, (void **) &(pBD) );
            }
#else
            pBD = (tANI_U32 *) pSchMsg->bodyptr;
#endif


            mh = SIR_MAC_BD_TO_MPDUHEADER( pBD );

            if (mh->fc.type == SIR_MAC_MGMT_FRAME &&
                mh->fc.subType == SIR_MAC_MGMT_BEACON)
                schBeaconProcess(pMac, pBD);
            else
            {
                schLog(pMac, LOGE, FL("Unexpected message (%d,%d) rcvd\n"),
                       mh->fc.type, mh->fc.subType);
                pMac->sch.gSchUnknownRcvCnt++;
            }
#if defined (ANI_OS_TYPE_LINUX) || defined (ANI_OS_TYPE_OSX)
        // Free up allocated SK BUF
        //for Windows, this is freed up by palHandleRxFrames
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, pBD, (void *) pSchMsg->bodyptr) ;
#endif
            break;
#endif

        case SIR_SCH_CHANNEL_SWITCH_REQUEST:
            schLog(pMac, LOGE,
                   FL("Channel switch request not handled\n"));
            break;

        case SIR_SCH_START_SCAN_REQ:
            SIR_SCHED_LOCK();
            pMac->sch.gSchScanReqRcvd = true;
            if (pMac->sch.gSchHcfEnabled)
            {
                // In HCF mode, wait for TFP to stop before sending a response
                if (pMac->sch.schObject.gSchCFBInitiated ||
                    pMac->sch.schObject.gSchCFPInitiated)
                {
                   PELOG1(schLog(pMac, LOG1,
                           FL("Waiting for TFP to halt before sending "
                              "start scan response\n"));)
                }
                else
                    schSendStartScanRsp(pMac);
            }
            else
            {
                // In eDCF mode, send the response right away
                schSendStartScanRsp(pMac);
            }
            SIR_SCHED_UNLOCK();
            break;

        case SIR_SCH_END_SCAN_NTF:
           PELOG3(schLog(pMac, LOG3,
                   FL("Received STOP_SCAN_NTF from LIM\n"));)
            pMac->sch.gSchScanReqRcvd = false;
#ifdef WMM_SA
#if (WNI_POLARIS_FW_PRODUCT == AP)
            if (psessionEntry->limSystemRole == eLIM_AP_ROLE && pMac->sch.gSchHcfEnabled)
                startCFB();
#endif
#endif
            break;

        case SIR_CFG_PARAM_UPDATE_IND:

            if (wlan_cfgGetInt(pMac, (tANI_U16) pSchMsg->bodyval, &val) != eSIR_SUCCESS)
                schLog(pMac, LOGP, FL("failed to cfg get id %d\n"), pSchMsg->bodyval);

            switch (pSchMsg->bodyval)
            {
                case WNI_CFG_BEACON_INTERVAL:
                    // What to do for IBSS ?? - TBD
                    if (psessionEntry->limSystemRole == eLIM_AP_ROLE)
                        schSetBeaconInterval(pMac,psessionEntry);
                    break;


                case WNI_CFG_DTIM_PERIOD:
                    pMac->sch.schObject.gSchDTIMCount = 0;
                    break;

                case WNI_CFG_CFP_PERIOD:
                    pMac->sch.schObject.gSchCFPCount = 0;
                    break;

                case WNI_CFG_EDCA_PROFILE:
                    schEdcaProfileUpdate(pMac, psessionEntry);
                    break;

                case WNI_CFG_EDCA_ANI_ACBK_LOCAL:
                case WNI_CFG_EDCA_ANI_ACBE_LOCAL:
                case WNI_CFG_EDCA_ANI_ACVI_LOCAL:
                case WNI_CFG_EDCA_ANI_ACVO_LOCAL:
                case WNI_CFG_EDCA_WME_ACBK_LOCAL:
                case WNI_CFG_EDCA_WME_ACBE_LOCAL:
                case WNI_CFG_EDCA_WME_ACVI_LOCAL:
                case WNI_CFG_EDCA_WME_ACVO_LOCAL:
                    if (psessionEntry->limSystemRole == eLIM_AP_ROLE)
                        schQosUpdateLocal(pMac, psessionEntry);
                    break;

                case WNI_CFG_EDCA_ANI_ACBK:
                case WNI_CFG_EDCA_ANI_ACBE:
                case WNI_CFG_EDCA_ANI_ACVI:
                case WNI_CFG_EDCA_ANI_ACVO:
                case WNI_CFG_EDCA_WME_ACBK:
                case WNI_CFG_EDCA_WME_ACBE:
                case WNI_CFG_EDCA_WME_ACVI:
                case WNI_CFG_EDCA_WME_ACVO:
                    if (psessionEntry->limSystemRole == eLIM_AP_ROLE)
                    {
                        psessionEntry->gLimEdcaParamSetCount++;
                        schQosUpdateBroadcast(pMac, psessionEntry);
                    }
                    break;

                default:
                    schLog(pMac, LOGE, FL("Cfg param %d indication not handled\n"),
                           pSchMsg->bodyval);
            }
            break;

        default:
            schLog(pMac, LOGE, FL("Unknown message in schMsgQ type %d\n"),
                   pSchMsg->type);
    }
