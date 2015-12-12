if ( CSR_IS_ROAM_SUBSTATE_DISASSOC_HO(pMac, sessionId)
#ifdef WLAN_FEATURE_VOWIFI_11R
                && csrRoamIs11rAssoc(pMac)
#endif
           )            
        {
            *pBuf = CSR_DONT_SEND_DISASSOC_OVER_THE_AIR;  /* Set DoNotSendOverTheAir flag to 1 only for handoff case */
        }
