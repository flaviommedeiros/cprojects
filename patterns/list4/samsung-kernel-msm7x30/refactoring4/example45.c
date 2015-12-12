#ifdef WLAN_SOFTAP_FEATURE
if (pAPSession->gLimProtectionControl != WNI_CFG_FORCE_POLICY_PROTECTION_DISABLE)
#else
        if (pMac->lim.gLimProtectionControl != WNI_CFG_FORCE_POLICY_PROTECTION_DISABLE)
#endif
            ap_beacon_process(pMac,  pRxPacketInfo, &beaconStruct, &beaconParams, pAPSession);
