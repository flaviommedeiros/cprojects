#ifdef WLAN_SOFTAP_FEATURE
if(eLIM_AP_ROLE == psessionEntry->limSystemRole)
        {
            if(overlap)
            {
                psessionEntry->gLimOverlap11gParams.protectionEnabled = true;
                //11g exists in overlap BSS.
                //need not to change the operating mode to overlap_legacy
                //if higher or same protection operating mode is enabled right now.
                if((eSIR_HT_OP_MODE_OVERLAP_LEGACY != psessionEntry->htOperMode) &&
                    (eSIR_HT_OP_MODE_MIXED != psessionEntry->htOperMode))
                {
                    psessionEntry->htOperMode = eSIR_HT_OP_MODE_OVERLAP_LEGACY;
                }
                limEnableHtRifsProtection(pMac, true, overlap, pBeaconParams,psessionEntry);
                limEnableHtOBSSProtection(pMac,  true , overlap, pBeaconParams, psessionEntry);
            }
            else
            {
                //11g is associated to an AP operating in 11n mode.
                //Change the HT operating mode to 'mixed mode'.
                psessionEntry->gLim11gParams.protectionEnabled = true;
                if(eSIR_HT_OP_MODE_MIXED != psessionEntry->htOperMode)
                {
                    psessionEntry->htOperMode = eSIR_HT_OP_MODE_MIXED;
                    limEnableHtRifsProtection(pMac, true, overlap, pBeaconParams,psessionEntry);
                    limEnableHtOBSSProtection(pMac,  true , overlap, pBeaconParams,psessionEntry);        
                }
            }
        }else if(eLIM_BT_AMP_AP_ROLE == psessionEntry->limSystemRole)
#else
        if((eLIM_AP_ROLE == psessionEntry->limSystemRole)||(eLIM_BT_AMP_AP_ROLE == psessionEntry->limSystemRole))
#endif
        {
            if(overlap)
            {
                pMac->lim.gLimOverlap11gParams.protectionEnabled = true;
                //11g exists in overlap BSS.
                //need not to change the operating mode to overlap_legacy
                //if higher or same protection operating mode is enabled right now.
                if((eSIR_HT_OP_MODE_OVERLAP_LEGACY != pMac->lim.gHTOperMode) &&
                    (eSIR_HT_OP_MODE_MIXED != pMac->lim.gHTOperMode))
                {
                    pMac->lim.gHTOperMode = eSIR_HT_OP_MODE_OVERLAP_LEGACY;
                    limEnableHtRifsProtection(pMac, true, overlap, pBeaconParams,psessionEntry);
                }
            }
            else
            {
                //11g is associated to an AP operating in 11n mode.
                //Change the HT operating mode to 'mixed mode'.
                psessionEntry->gLim11gParams.protectionEnabled = true;
                if(eSIR_HT_OP_MODE_MIXED != pMac->lim.gHTOperMode)
                {
                    pMac->lim.gHTOperMode = eSIR_HT_OP_MODE_MIXED;
                    limEnableHtRifsProtection(pMac, true, overlap, pBeaconParams,psessionEntry);
                    limEnableHtOBSSProtection(pMac,  true , overlap, pBeaconParams,psessionEntry);        
                }
            }
        }
