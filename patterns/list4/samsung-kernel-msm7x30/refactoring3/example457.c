switch (pActionHdr->category)
    {
        case SIR_MAC_ACTION_QOS_MGMT:
            if (psessionEntry->limQosEnabled)
            {
                switch (pActionHdr->actionID)
                {
                    case SIR_MAC_QOS_ADD_TS_REQ:
                        __limProcessAddTsReq(pMac, (tANI_U8 *) pRxPacketInfo,psessionEntry);
                        break;

                    case SIR_MAC_QOS_ADD_TS_RSP:
                        __limProcessAddTsRsp(pMac, (tANI_U8 *) pRxPacketInfo,psessionEntry);
                        break;

                    case SIR_MAC_QOS_DEL_TS_REQ:
                        __limProcessDelTsReq(pMac, (tANI_U8 *) pRxPacketInfo,psessionEntry);
                        break;

                    default:
                        PELOGE(limLog(pMac, LOGE, FL("Qos action %d not handled\n"), pActionHdr->actionID);)
                        break;
                }
                break ;
            }

           break;

        case SIR_MAC_ACTION_SPECTRUM_MGMT:
            switch (pActionHdr->actionID)
            {
#ifdef ANI_SUPPORT_11H
                case SIR_MAC_ACTION_MEASURE_REQUEST_ID:
                    if(psessionEntry->lim11hEnable)
                    {
                        __limProcessMeasurementRequestFrame(pMac, pRxPacketInfo);
                    }
                    break;

                case SIR_MAC_ACTION_TPC_REQUEST_ID:
                    if ((psessionEntry->limSystemRole == eLIM_STA_ROLE) ||
                        (pessionEntry->limSystemRole == eLIM_AP_ROLE))
                    {
                        if(psessionEntry->lim11hEnable)
                        {
                            __limProcessTpcRequestFrame(pMac, pRxPacketInfo);
                        }
                    }
                    break;

#endif
                case SIR_MAC_ACTION_CHANNEL_SWITCH_ID:
                    if (psessionEntry->limSystemRole == eLIM_STA_ROLE)
                    {
                        __limProcessChannelSwitchActionFrame(pMac, pRxPacketInfo,psessionEntry);
                    }
                    break;
                default:
                    PELOGE(limLog(pMac, LOGE, FL("Spectrum mgmt action id %d not handled\n"), pActionHdr->actionID);)
                    break;
            }
            break;

        case SIR_MAC_ACTION_WME:
            if (! psessionEntry->limWmeEnabled)
            {
                limLog(pMac, LOGW, FL("WME mode disabled - dropping action frame %d\n"),
                       pActionHdr->actionID);
                break;
            }
            switch(pActionHdr->actionID)
            {
                case SIR_MAC_QOS_ADD_TS_REQ:
                    __limProcessAddTsReq(pMac, (tANI_U8 *) pRxPacketInfo,psessionEntry);
                    break;

                case SIR_MAC_QOS_ADD_TS_RSP:
                    __limProcessAddTsRsp(pMac, (tANI_U8 *) pRxPacketInfo,psessionEntry);
                    break;

                case SIR_MAC_QOS_DEL_TS_REQ:
                    __limProcessDelTsReq(pMac, (tANI_U8 *) pRxPacketInfo,psessionEntry);
                    break;

                default:
                    PELOGE(limLog(pMac, LOGE, FL("WME action %d not handled\n"), pActionHdr->actionID);)
                    break;
            }
            break;

        case SIR_MAC_ACTION_BLKACK:
            // Determine the "type" of BA Action Frame
            switch(pActionHdr->actionID)
            {
              case SIR_MAC_BLKACK_ADD_REQ:
                __limProcessAddBAReq( pMac, (tANI_U8 *) pRxPacketInfo,psessionEntry);
                break;

              case SIR_MAC_BLKACK_ADD_RSP:
                __limProcessAddBARsp( pMac, (tANI_U8 *) pRxPacketInfo,psessionEntry);
                break;

              case SIR_MAC_BLKACK_DEL:
                __limProcessDelBAReq( pMac, (tANI_U8 *) pRxPacketInfo,psessionEntry);
                break;

              default:
                break;
            }

            break;
    case SIR_MAC_ACTION_HT:
        /** Type of HT Action to be performed*/
        switch(pActionHdr->actionID) {
        case SIR_MAC_SM_POWER_SAVE:
            __limProcessSMPowerSaveUpdate(pMac, (tANI_U8 *) pRxPacketInfo,psessionEntry);
            break;
        default:
            PELOGE(limLog(pMac, LOGE, FL("Action ID %d not handled in HT Action category\n"), pActionHdr->actionID);)
            break;
        }
        break;

#if defined WLAN_FEATURE_VOWIFI
    case SIR_MAC_ACTION_RRM:
        if( pMac->rrm.rrmPEContext.rrmEnable )
        {
            switch(pActionHdr->actionID) {
                case SIR_MAC_RRM_RADIO_MEASURE_REQ:
                    __limProcessRadioMeasureRequest( pMac, (tANI_U8 *) pRxPacketInfo, psessionEntry );
                    break;
                case SIR_MAC_RRM_LINK_MEASUREMENT_REQ:
                    __limProcessLinkMeasurementReq( pMac, (tANI_U8 *) pRxPacketInfo, psessionEntry );
                    break;
                case SIR_MAC_RRM_NEIGHBOR_RPT:   
                    __limProcessNeighborReport( pMac, (tANI_U8*) pRxPacketInfo, psessionEntry );
                    break;
                default:
                    PELOGE( limLog( pMac, LOGE, FL("Action ID %d not handled in RRM\n"), pActionHdr->actionID);)
                    break;

            }
        }
        else
        {
            // Else we will just ignore the RRM messages.
            PELOGE( limLog( pMac, LOGE, FL("RRM Action frame ignored as RRM is disabled in cfg\n"));)
        }
        break;
#endif
#if defined WLAN_FEATURE_P2P
    case SIR_MAC_ACTION_PUBLIC_USAGE:
        switch(pActionHdr->actionID) {
        case SIR_MAC_ACTION_VENDOR_SPECIFIC:
            {
              tpSirMacVendorSpecificPublicActionFrameHdr pPubAction = (tpSirMacVendorSpecificPublicActionFrameHdr) pActionHdr;
              tpSirMacMgmtHdr     pHdr;
              tANI_U32            frameLen;
              tANI_U8 P2POui[] = { 0x50, 0x6F, 0x9A, 0x09 };

              pHdr = WDA_GET_RX_MAC_HEADER(pRxPacketInfo);
              frameLen = WDA_GET_RX_PAYLOAD_LEN(pRxPacketInfo);

              //Check if it is a P2P public action frame.
              if( palEqualMemory( pMac->hHdd, pPubAction->Oui, P2POui, 4 ) )
              {
                 /* Forward to the SME to HDD to wpa_supplicant */
                 // type is ACTION
                 limSendSmeMgmtFrameInd(pMac, pHdr->fc.subType, 
                    (tANI_U8*)pHdr, frameLen + sizeof(tSirMacMgmtHdr), 0, 
                    WDA_GET_RX_CH( pRxPacketInfo ), psessionEntry);
              }
              else
              {
                 limLog( pMac, LOGE, FL("Unhandled public action frame (Vendor specific). OUI %x %x %x %x\n"),
                      pPubAction->Oui[0], pPubAction->Oui[1], pPubAction->Oui[2], pPubAction->Oui[3] );
              }
           }
            break;

        default:
            PELOGE(limLog(pMac, LOGE, FL("Unhandled public action frame -- %x \n"), pActionHdr->actionID);)
            break;
        }
        break;
#endif

#ifdef WLAN_FEATURE_11W
    case SIR_MAC_ACTION_SA_QUERY:
    {
        /**11w SA query request action frame received**/
        __limProcessSAQueryRequestActionFrame(pMac,(tANI_U8*) pRxPacketInfo, psessionEntry );
        break;
     }
#endif

    default:
       PELOGE(limLog(pMac, LOGE, FL("Action category %d not handled\n"), pActionHdr->category);)
       break;
    }
