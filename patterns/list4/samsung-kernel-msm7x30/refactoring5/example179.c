#ifdef WLAN_SOFTAP_FEATURE
if(psessionEntry->limSystemRole == eLIM_AP_ROLE)
        {
            if((psessionEntry->authType == eSIR_SHARED_KEY) || (psessionEntry->authType == eSIR_AUTO_SWITCH))
                algoEnable = true;
            else
                algoEnable = false;
            
        }
        else
#endif

        if (wlan_cfgGetInt(pMac, WNI_CFG_SHARED_KEY_AUTH_ENABLE,
                      &algoEnable) != eSIR_SUCCESS)
        {
            /**
             * Could not get AuthAlgo2 Enable value
             * from CFG. Log error.
             */
            limLog(pMac, LOGE,
                   FL("could not retrieve AuthAlgo2 Enable value\n"));

            return false;
        }
