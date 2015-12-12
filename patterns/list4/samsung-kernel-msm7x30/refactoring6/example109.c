if (((psessionEntry->limSystemRole == eLIM_BT_AMP_AP_ROLE)  ||
         (psessionEntry->limSystemRole == eLIM_BT_AMP_STA_ROLE)
#ifdef WLAN_SOFTAP_FEATURE
         || (psessionEntry->limSystemRole == eLIM_AP_ROLE)
#endif
         ) &&
        (psessionEntry->statypeForBss == STA_ENTRY_SELF))
    {
        limProcessBtAmpApMlmDelBssRsp(pMac, limMsgQ,psessionEntry);
        return;
    }
