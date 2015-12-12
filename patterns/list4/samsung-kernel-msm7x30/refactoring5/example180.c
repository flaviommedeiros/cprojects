#ifdef WLAN_SOFTAP_FEATURE
if(psessionEntry->limSystemRole == eLIM_AP_ROLE)
        {
            privacyOptImp = psessionEntry->privacy;
        }
        else
#endif

        if (wlan_cfgGetInt(pMac, WNI_CFG_PRIVACY_ENABLED,
                      &privacyOptImp) != eSIR_SUCCESS)
        {
            /**
             * Could not get PrivacyOptionImplemented value
             * from CFG. Log error.
             */
            limLog(pMac, LOGE,
               FL("could not retrieve PrivacyOptImplemented value\n"));

            return false;
        }
