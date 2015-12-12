switch (fc.type)
    {
        case SIR_MAC_MGMT_FRAME:
        {
                #if 0   //TBD-RAJESH fix this
                if (limIsReassocInProgress( pMac,psessionEntry) && (fc.subType != SIR_MAC_MGMT_DISASSOC) &&
                                                (fc.subType != SIR_MAC_MGMT_DEAUTH) && (fc.subType != SIR_MAC_MGMT_REASSOC_RSP))
                {
                    limLog(pMac, LOGE, FL("Frame with Type - %d, Subtype - %d received in ReAssoc Wait state, dropping...\n"),
                                                                fc.type, fc.subType);
                    return;
            }
                #endif   //HACK to continue scanning 
            // Received Management frame
            switch (fc.subType)
            {
                case SIR_MAC_MGMT_ASSOC_REQ:
                    // Make sure the role supports Association
                    if ((psessionEntry->limSystemRole == eLIM_BT_AMP_AP_ROLE)
#ifdef WLAN_SOFTAP_FEATURE
                    || (psessionEntry->limSystemRole == eLIM_AP_ROLE)
#endif
                    )
                        limProcessAssocReqFrame(pMac, pRxPacketInfo, LIM_ASSOC, psessionEntry);

                    else
                    {
                        // Unwanted messages - Log error
                        limLog(pMac, LOGE, FL("unexpected message received %X\n"),limMsg->type);
                        limPrintMsgName(pMac, LOGE, limMsg->type);
                    }
                    break;

                case SIR_MAC_MGMT_ASSOC_RSP:
                    limProcessAssocRspFrame(pMac, pRxPacketInfo, LIM_ASSOC,psessionEntry);
                    break;

                case SIR_MAC_MGMT_REASSOC_REQ:
                    // Make sure the role supports Reassociation
                    if ((psessionEntry->limSystemRole == eLIM_BT_AMP_AP_ROLE)
#ifdef WLAN_SOFTAP_FEATURE
                      || (psessionEntry->limSystemRole == eLIM_AP_ROLE)
#endif                   
                    ){
                        limProcessAssocReqFrame(pMac, pRxPacketInfo, LIM_REASSOC, psessionEntry);
                    }
                    else
                    {
                        // Unwanted messages - Log error
                        limLog(pMac, LOGE, FL("unexpected message received %X\n"),limMsg->type);
                        limPrintMsgName(pMac, LOGE, limMsg->type);
                    }
                    break;

                case SIR_MAC_MGMT_REASSOC_RSP:
                    limProcessAssocRspFrame(pMac, pRxPacketInfo, LIM_REASSOC,psessionEntry);
                    break;

                case SIR_MAC_MGMT_PROBE_REQ:
                    limProcessProbeReqFrame_multiple_BSS(pMac, pRxPacketInfo,psessionEntry);
                    break;

                case SIR_MAC_MGMT_PROBE_RSP:
                    if(psessionEntry == NULL)
                        limProcessProbeRspFrameNoSession(pMac, pRxPacketInfo);
                    else
                        limProcessProbeRspFrame(pMac, pRxPacketInfo, psessionEntry);
                    break;

                case SIR_MAC_MGMT_BEACON:
                    __limHandleBeacon(pMac, limMsg,psessionEntry);
                    break;

                case SIR_MAC_MGMT_DISASSOC:
                    limProcessDisassocFrame(pMac, pRxPacketInfo,psessionEntry);
                    break;

                case SIR_MAC_MGMT_AUTH:
                    limProcessAuthFrame(pMac, pRxPacketInfo,psessionEntry);
                    break;

                case SIR_MAC_MGMT_DEAUTH:
                    limProcessDeauthFrame(pMac, pRxPacketInfo,psessionEntry);
                    break;

                case SIR_MAC_MGMT_ACTION:
#if defined WLAN_FEATURE_P2P
                   if(psessionEntry == NULL)
                      limProcessActionFrameNoSession(pMac, pRxPacketInfo);
                   else
                   {
#endif
                      if (WDA_GET_RX_UNKNOWN_UCAST(pRxPacketInfo))
                         limHandleUnknownA2IndexFrames(pMac, pRxPacketInfo,psessionEntry);
                     else
                         limProcessActionFrame(pMac, pRxPacketInfo,psessionEntry);
#if defined WLAN_FEATURE_P2P
                   }
#endif
                   break;
                default:
                    // Received Management frame of 'reserved' subtype
                    break;
            } // switch (fc.subType)

        }
        break;
#ifdef FEATURE_WLAN_CCX
        case SIR_MAC_DATA_FRAME:
        {
             /* We accept data frame (IAPP frame) only if Session is
              * present and ccx connection is established on that
              * session
              */
             if (psessionEntry && psessionEntry->isCCXconnection) {
                 limProcessIappFrame(pMac, pRxPacketInfo, psessionEntry);
             }
        }
        break;
#endif
        default:
            // Received frame of type 'reserved'
            break;

    }
