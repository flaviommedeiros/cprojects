if((fc.subType != SIR_MAC_MGMT_PROBE_RSP )&&
            (fc.subType != SIR_MAC_MGMT_BEACON)&&
            (fc.subType != SIR_MAC_MGMT_PROBE_REQ)
#if defined WLAN_FEATURE_P2P
            && (fc.subType != SIR_MAC_MGMT_ACTION ) //Public action frame can be received from non-associated stations.
#endif
          )
        {

            if((psessionEntry = peFindSessionByPeerSta(pMac,pHdr->sa,&sessionId))== NULL) 
            {
               limLog(pMac, LOG1, FL("session does not exist for given bssId\n"));
               limPktFree(pMac, HAL_TXRX_FRM_802_11_MGMT, pRxPacketInfo, limMsg->bodyptr);
               return;
            }
        }
