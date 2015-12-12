if ((pRSNie->rsnIEdata[0] != DOT11F_EID_RSN) &&
            (pRSNie->rsnIEdata[0] != DOT11F_EID_WPA)
#ifdef FEATURE_WLAN_WAPI
            && (pRSNie->rsnIEdata[0] != DOT11F_EID_WAPI)
#endif
            )
        {
            limLog(pMac, LOGE, FL("RSN/WPA/WAPI EID %d not [%d || %d]\n"), 
                   pRSNie->rsnIEdata[0], DOT11F_EID_RSN, 
                   DOT11F_EID_WPA);
            return false;
        }
