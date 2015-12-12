#ifdef WLAN_SOFTAP_FEATURE
if(eLIM_AP_ROLE == psessionEntry->limSystemRole){
            if(overlap)
            {
                psessionEntry->gLimOverlapHt20Params.protectionEnabled = true;
                if((eSIR_HT_OP_MODE_OVERLAP_LEGACY != psessionEntry->htOperMode) &&
                    (eSIR_HT_OP_MODE_MIXED != psessionEntry->htOperMode))
                {
                    psessionEntry->htOperMode = eSIR_HT_OP_MODE_OVERLAP_LEGACY;
                    limEnableHtRifsProtection(pMac, true, overlap, pBeaconParams,psessionEntry);
                }
            }
            else
            {
               psessionEntry->gLimHt20Params.protectionEnabled = true;
                if(eSIR_HT_OP_MODE_PURE == psessionEntry->htOperMode)
                {
                    //Commenting because of CR 258588 WFA cert
                    //psessionEntry->htOperMode = eSIR_HT_OP_MODE_NO_LEGACY_20MHZ_HT;
                    psessionEntry->htOperMode = eSIR_HT_OP_MODE_PURE;
                    limEnableHtRifsProtection(pMac, false, overlap, pBeaconParams,psessionEntry);
                    limEnableHtOBSSProtection(pMac,  false, overlap, pBeaconParams,psessionEntry);
                }
            }
        }else if(eLIM_BT_AMP_AP_ROLE == psessionEntry->limSystemRole)
#else
        if((eLIM_AP_ROLE == psessionEntry->limSystemRole)||(eLIM_BT_AMP_AP_ROLE == psessionEntry->limSystemRole))
#endif
        {
            if(overlap)
            {
                pMac->lim.gLimOverlapHt20Params.protectionEnabled = true;
                if((eSIR_HT_OP_MODE_OVERLAP_LEGACY != pMac->lim.gHTOperMode) &&
                    (eSIR_HT_OP_MODE_MIXED != pMac->lim.gHTOperMode))
                {
                    pMac->lim.gHTOperMode = eSIR_HT_OP_MODE_OVERLAP_LEGACY;
                    limEnableHtRifsProtection(pMac, true, overlap, pBeaconParams,psessionEntry);
                }
            }
            else
            {
                psessionEntry->gLimHt20Params.protectionEnabled = true;
                if(eSIR_HT_OP_MODE_PURE == pMac->lim.gHTOperMode)
                {
                    pMac->lim.gHTOperMode = eSIR_HT_OP_MODE_NO_LEGACY_20MHZ_HT;
                    limEnableHtRifsProtection(pMac, false, overlap, pBeaconParams,psessionEntry);
                    limEnableHtOBSSProtection(pMac,  false, overlap, pBeaconParams,psessionEntry);
                }
            }
        }
