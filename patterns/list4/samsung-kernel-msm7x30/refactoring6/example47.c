if ((pSession->pCurRoamProfile != NULL)  && (
#ifdef WLAN_SOFTAP_FEATURE
             (CSR_IS_INFRA_AP(pSession->pCurRoamProfile)) || 
#endif
             (CSR_IS_WDS_AP(pSession->pCurRoamProfile)))){ 
            // Set the BSSID before sending the message to LIM
            status = palCopyMemory( pMac->hHdd, (tSirMacAddr *)pBuf, pSession->selfMacAddr, sizeof( pMsg->peerMacAddr ) );
            pBuf =  pBuf + sizeof(tSirMacAddr);
        }
        else
        {
            // Set the BSSID before sending the message to LIM
            status = palCopyMemory( pMac->hHdd, (tSirMacAddr *)pBuf, bssId, sizeof( pMsg->peerMacAddr ) );
            pBuf =  pBuf + sizeof(tSirMacAddr);
        }
