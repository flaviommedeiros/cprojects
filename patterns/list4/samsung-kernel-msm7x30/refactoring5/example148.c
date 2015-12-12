#ifdef WLAN_SOFTAP_FEATURE
if(psessionEntry->limSystemRole == eLIM_AP_ROLE)
        {
            val = psessionEntry->privacy; 
        } 
        else 
#endif
        // Accept Authentication frame only if Privacy is implemented
        if (wlan_cfgGetInt(pMac, WNI_CFG_PRIVACY_ENABLED,
                      &val) != eSIR_SUCCESS)
        {
            /**
             * Could not get Privacy option
             * from CFG. Log error.
             */
            limLog(pMac, LOGP, FL("could not retrieve Privacy option\n"));
        }
