if((NULL != psessionEntry)
#ifdef WLAN_SOFTAP_FEATURE
        && (eLIM_AP_ROLE != psessionEntry->limSystemRole )
#endif     
    )      
            {
                peDeleteSession(pMac,psessionEntry);
                psessionEntry = NULL;
            }
