#ifdef WLAN_SOFTAP_FEATURE
if(psessionEntry->limSystemRole == eLIM_AP_ROLE ){
            pInfo->uapsd = ( 0x1 & psessionEntry->apUapsdEnable );
        }
        else
#endif
            pInfo->uapsd = ( 0x1 & pMac->lim.gUapsdEnable );
