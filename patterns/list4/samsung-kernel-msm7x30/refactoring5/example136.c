#ifdef FEATURE_WLAN_CCX
if ((RSNAuthType == eCSR_AUTH_TYPE_CCKM_RSN) && 
                ((pWextState->authKeyMgmt & IW_AUTH_KEY_MGMT_802_1X) 
                 == IW_AUTH_KEY_MGMT_802_1X)) { 
                hddLog( LOG1, "%s: set authType to CCKM RSN. AKM also 802.1X.\n", __FUNCTION__);
                pRoamProfile->AuthType.authType[0] = eCSR_AUTH_TYPE_CCKM_RSN;   
            } else
            if ((RSNAuthType == eCSR_AUTH_TYPE_CCKM_RSN)) { 
                hddLog( LOG1, "%s: Last chance to set authType to CCKM RSN.\n", __FUNCTION__);
                pRoamProfile->AuthType.authType[0] = eCSR_AUTH_TYPE_CCKM_RSN;   
            } else
#endif

#ifdef WLAN_FEATURE_VOWIFI_11R
            if ((RSNAuthType == eCSR_AUTH_TYPE_FT_RSN) && 
                ((pWextState->authKeyMgmt & IW_AUTH_KEY_MGMT_802_1X) 
                 == IW_AUTH_KEY_MGMT_802_1X)) {
               pRoamProfile->AuthType.authType[0] = eCSR_AUTH_TYPE_FT_RSN;   
            }else
            if ((RSNAuthType == eCSR_AUTH_TYPE_FT_RSN_PSK) && 
                ((pWextState->authKeyMgmt & IW_AUTH_KEY_MGMT_PSK)
                 == IW_AUTH_KEY_MGMT_PSK)) {
               pRoamProfile->AuthType.authType[0] = eCSR_AUTH_TYPE_FT_RSN_PSK;   
            } else
#endif

            if( (pWextState->authKeyMgmt & IW_AUTH_KEY_MGMT_802_1X) 
                    == IW_AUTH_KEY_MGMT_802_1X) {
               pRoamProfile->AuthType.authType[0] = eCSR_AUTH_TYPE_RSN;   
            } else 
            if ( (pWextState->authKeyMgmt & IW_AUTH_KEY_MGMT_PSK)
                    == IW_AUTH_KEY_MGMT_PSK) {
               pRoamProfile->AuthType.authType[0] = eCSR_AUTH_TYPE_RSN_PSK;
            } else {             
               pRoamProfile->AuthType.authType[0] = eCSR_AUTH_TYPE_UNKNOWN;
            }
