if ((eLIM_AP_ROLE == psessionEntry->limSystemRole)
#ifdef WLAN_FEATURE_P2P_INTERNAL
         || (psessionEntry->limSystemRole == eLIM_P2P_DEVICE_ROLE)
#endif
          )
        {
            limIndicateProbeReqToHDD(pMac, pBd, psessionEntry);
        }
