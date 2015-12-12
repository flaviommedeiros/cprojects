if((pMac->lim.gpSession[sessionId].bssType == eSIR_INFRASTRUCTURE_MODE) &&
           (((pMac->lim.gpSession[sessionId].is11Rconnection) 
#ifdef FEATURE_WLAN_CCX
           || (pMac->lim.gpSession[sessionId].isCCXconnection)
#endif
#ifdef FEATURE_WLAN_LFR
           || (pMac->lim.gpSession[sessionId].isFastRoamIniFeatureEnabled)
#endif
           )&& 
            pMac->lim.gpSession[sessionId].isFastTransitionEnabled))
        {
            // Make sure we have 11r/CCX and FT enabled only then we need
            // the values to be altered from cfg for FW RSSI Period alteration.
            return TRUE;
        }
