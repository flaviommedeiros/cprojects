if((psessionEntry->limSystemRole == eLIM_BT_AMP_AP_ROLE)
#ifdef WLAN_SOFTAP_FEATURE
       || (psessionEntry->limSystemRole == eLIM_AP_ROLE)
#endif
    )
    {
        sirCopyMacAddr(pDisAssocReq->peerMacAddr,pStaDs->staAddr);
        sirCopyMacAddr(pDisAssocReq->bssId,psessionEntry->bssId);
    }
