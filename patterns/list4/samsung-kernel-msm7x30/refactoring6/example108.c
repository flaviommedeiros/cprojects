if ((psessionEntry->limSystemRole == eLIM_BT_AMP_AP_ROLE)
#ifdef WLAN_SOFTAP_FEATURE
    || (psessionEntry->limSystemRole == eLIM_AP_ROLE)
#endif
    )
    {
        limProcessBtAmpApMlmAddStaRsp(pMac, limMsgQ,psessionEntry);
        return;
    }
