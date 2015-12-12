#ifdef FEATURE_WLAN_CCX
if ((RSNAuthType == eCSR_AUTH_TYPE_CCKM_WPA) && 
                ((pWextState->authKeyMgmt & IW_AUTH_KEY_MGMT_802_1X) 
                 == IW_AUTH_KEY_MGMT_802_1X)) { 
                hddLog( LOG1, "%s: set authType to CCKM WPA. AKM also 802.1X.\n", __FUNCTION__);
                pRoamProfile->AuthType.authType[0] = eCSR_AUTH_TYPE_CCKM_WPA;   
            } else 
            if ((RSNAuthType == eCSR_AUTH_TYPE_CCKM_WPA)) { 
                hddLog( LOG1, "%s: Last chance to set authType to CCKM WPA.\n", __FUNCTION__);
                pRoamProfile->AuthType.authType[0] = eCSR_AUTH_TYPE_CCKM_WPA;   
            } else
#endif
            if((pWextState->authKeyMgmt & IW_AUTH_KEY_MGMT_802_1X)
                    == IW_AUTH_KEY_MGMT_802_1X) {
               pRoamProfile->AuthType.authType[0] = eCSR_AUTH_TYPE_WPA;   
            } else 
            if ((pWextState->authKeyMgmt & IW_AUTH_KEY_MGMT_PSK)
                    == IW_AUTH_KEY_MGMT_PSK) {
               pRoamProfile->AuthType.authType[0] = eCSR_AUTH_TYPE_WPA_PSK;
            } else {     
               pRoamProfile->AuthType.authType[0] = eCSR_AUTH_TYPE_WPA_NONE;
            }
