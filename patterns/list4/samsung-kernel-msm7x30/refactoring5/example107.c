#ifdef WLAN_FEATURE_VOWIFI_11R
if ( (csrRoamIsHandoffInProgress(pMac)) && 
         (NewSubstate != eCSR_ROAM_SUBSTATE_DISASSOC_HANDOFF))
    {
        tpCsrNeighborRoamControlInfo pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
        palCopyMemory(pMac->hHdd, &bssId, pNeighborRoamInfo->csrNeighborRoamProfile.BSSIDs.bssid, sizeof(tSirMacAddr));
    } else 
#endif
    if(pSession->pConnectBssDesc)
    {
        palCopyMemory(pMac->hHdd, &bssId, pSession->pConnectBssDesc->bssId, sizeof(tCsrBssid));
    }
