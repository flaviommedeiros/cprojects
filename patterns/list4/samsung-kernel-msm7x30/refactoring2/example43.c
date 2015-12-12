#ifdef WLAN_SOFTAP_FEATURE
if(!CSR_IS_INFRA_AP(&pSession->connectedProfile))
#endif
    {
        csrRoamCallCallback(pMac, sessionId, NULL, 0, eCSR_ROAM_LOSTLINK_DETECTED, result);
    }
