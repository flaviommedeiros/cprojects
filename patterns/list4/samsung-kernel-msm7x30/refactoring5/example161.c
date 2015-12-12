#ifdef WLAN_SOFTAP_FEATURE
if(eLIM_AP_ROLE == psessionEntry->limSystemRole)
        {
            if(overlap)
            {
                psessionEntry->gLimOlbcParams.protectionEnabled = true;
                PELOGE(limLog(pMac, LOGE, FL("protection from olbc is enabled\n"));)
                if(true == psessionEntry->htCapability)
                {
                    if((eSIR_HT_OP_MODE_OVERLAP_LEGACY != psessionEntry->htOperMode) &&
                            (eSIR_HT_OP_MODE_MIXED != psessionEntry->htOperMode))
                    {
                        psessionEntry->htOperMode = eSIR_HT_OP_MODE_OVERLAP_LEGACY;
                    }
                    //CR-263021: OBSS bit is not switching back to 0 after disabling the overlapping legacy BSS
                    // This fixes issue of OBSS bit not set after 11b, 11g station leaves
                    limEnableHtRifsProtection(pMac, true, overlap, pBeaconParams,psessionEntry);
                    //Not processing OBSS bit from other APs, as we are already taking care
                    //of Protection from overlapping BSS based on erp IE or useProtection bit
                    limEnableHtOBSSProtection(pMac,  true, overlap, pBeaconParams, psessionEntry);
                }
            }
            else
            {
                psessionEntry->gLim11bParams.protectionEnabled = true;
                PELOGE(limLog(pMac, LOGE, FL("protection from 11b is enabled\n"));)
                if(true == psessionEntry->htCapability)
                {
                    if(eSIR_HT_OP_MODE_MIXED != psessionEntry->htOperMode)
                    {
                        psessionEntry->htOperMode = eSIR_HT_OP_MODE_MIXED;
                        limEnableHtRifsProtection(pMac, true, overlap, pBeaconParams,psessionEntry);
                        limEnableHtOBSSProtection(pMac,  true, overlap, pBeaconParams,psessionEntry);     
                    }
                }
            }
        }else if ((eLIM_BT_AMP_AP_ROLE == psessionEntry->limSystemRole) &&
                (true == psessionEntry->htCapability))
#else
            if(((eLIM_AP_ROLE == psessionEntry->limSystemRole)|| (eLIM_BT_AMP_AP_ROLE == psessionEntry->limSystemRole)) &&
                    (true == psessionEntry->htCapability))
#endif
            {
                if(overlap)
                {
                    psessionEntry->gLimOlbcParams.protectionEnabled = true;
                    if((eSIR_HT_OP_MODE_OVERLAP_LEGACY != pMac->lim.gHTOperMode) &&
                            (eSIR_HT_OP_MODE_MIXED != pMac->lim.gHTOperMode))
                    {
                        pMac->lim.gHTOperMode = eSIR_HT_OP_MODE_OVERLAP_LEGACY;
                    }
                    //CR-263021: OBSS bit is not switching back to 0 after disabling the overlapping legacy BSS
                    // This fixes issue of OBSS bit not set after 11b, 11g station leaves
                    limEnableHtRifsProtection(pMac, true, overlap, pBeaconParams,psessionEntry);
                    //Not processing OBSS bit from other APs, as we are already taking care
                    //of Protection from overlapping BSS based on erp IE or useProtection bit
                    limEnableHtOBSSProtection(pMac,  true, overlap, pBeaconParams, psessionEntry);
                }
                else
                {
                    psessionEntry->gLim11bParams.protectionEnabled = true;
                    if(eSIR_HT_OP_MODE_MIXED != pMac->lim.gHTOperMode)
                    { 
                        pMac->lim.gHTOperMode = eSIR_HT_OP_MODE_MIXED;
                        limEnableHtRifsProtection(pMac, true, overlap, pBeaconParams,psessionEntry);
                        limEnableHtOBSSProtection(pMac,  true, overlap, pBeaconParams,psessionEntry);     
                    }
                }
            }
