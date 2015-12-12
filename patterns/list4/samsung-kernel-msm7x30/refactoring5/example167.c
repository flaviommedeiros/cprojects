#ifdef WLAN_SOFTAP_FEATURE
if(eLIM_AP_ROLE == psessionEntry->limSystemRole){
            if(overlap)
            {
                //Overlap Legacy protection disabled.
                psessionEntry->gLimOverlapHt20Params.protectionEnabled = false;

                // no HT op mode change if any of the overlap protection enabled.
                if(!(psessionEntry->gLimOlbcParams.protectionEnabled ||
                    psessionEntry->gLimOverlap11gParams.protectionEnabled ||
                    psessionEntry->gLimOverlapHt20Params.protectionEnabled ||
                    psessionEntry->gLimOverlapNonGfParams.protectionEnabled))
                {

                    //Check if there is a need to change HT OP mode.
                    if(eSIR_HT_OP_MODE_OVERLAP_LEGACY == psessionEntry->htOperMode)
                    {
                        if(psessionEntry->gLimHt20Params.protectionEnabled)
                        {
                            //Commented beacuse of CR 258588 for WFA Cert
                            //psessionEntry->htOperMode = eSIR_HT_OP_MODE_NO_LEGACY_20MHZ_HT;
                            psessionEntry->htOperMode = eSIR_HT_OP_MODE_PURE;
                            limEnableHtRifsProtection(pMac, false, overlap, pBeaconParams,psessionEntry);
                            limEnableHtOBSSProtection(pMac,  false, overlap, pBeaconParams,psessionEntry);            
                        }
                        else
                        {
                            psessionEntry->htOperMode = eSIR_HT_OP_MODE_PURE;
                        }
                    }
                }
            }
            else
            {
                //Disable protection from 11G stations.
                psessionEntry->gLimHt20Params.protectionEnabled = false;

                //Change HT op mode appropriately.
                if(eSIR_HT_OP_MODE_NO_LEGACY_20MHZ_HT == psessionEntry->htOperMode)
                {
                    psessionEntry->htOperMode = eSIR_HT_OP_MODE_PURE;
                    limEnableHtRifsProtection(pMac, false, overlap, pBeaconParams,psessionEntry);
                    limEnableHtOBSSProtection(pMac,  false, overlap, pBeaconParams,psessionEntry);        
                }
            }
            PELOG1(limLog(pMac, LOG1, FL("===> Protection from HT 20 Disabled\n"));)
            pBeaconParams->ht20MhzCoexist = psessionEntry->beaconParams.ht20Coexist = false;
            pBeaconParams->paramChangeBitmap |= PARAM_HT20MHZCOEXIST_CHANGED;
        }else if(eLIM_BT_AMP_AP_ROLE == psessionEntry->limSystemRole)
#else
        if((eLIM_AP_ROLE == psessionEntry->limSystemRole)||(eLIM_BT_AMP_AP_ROLE == psessionEntry->limSystemRole))
#endif
        {
            if(overlap)
            {
                //Overlap Legacy protection disabled.
                pMac->lim.gLimOverlapHt20Params.protectionEnabled = false;

                // no HT op mode change if any of the overlap protection enabled.
                if(!(psessionEntry->gLimOlbcParams.protectionEnabled ||
                    pMac->lim.gLimOverlap11gParams.protectionEnabled ||
                    pMac->lim.gLimOverlapHt20Params.protectionEnabled ||
                    pMac->lim.gLimOverlapNonGfParams.protectionEnabled))
                {

                    //Check if there is a need to change HT OP mode.
                    if(eSIR_HT_OP_MODE_OVERLAP_LEGACY == pMac->lim.gHTOperMode)
                    {
                        if(psessionEntry->gLimHt20Params.protectionEnabled)
                        {
                            pMac->lim.gHTOperMode = eSIR_HT_OP_MODE_NO_LEGACY_20MHZ_HT;
                            limEnableHtRifsProtection(pMac, false, overlap, pBeaconParams,psessionEntry);
                            limEnableHtOBSSProtection(pMac,  false, overlap, pBeaconParams,psessionEntry);            
                        }
                        else
                        {
                            pMac->lim.gHTOperMode = eSIR_HT_OP_MODE_PURE;
                        }
                    }
                }
            }
            else
            {
                //Disable protection from 11G stations.
                psessionEntry->gLimHt20Params.protectionEnabled = false;

                //Change HT op mode appropriately.
                if(eSIR_HT_OP_MODE_NO_LEGACY_20MHZ_HT == pMac->lim.gHTOperMode)
                {
                    pMac->lim.gHTOperMode = eSIR_HT_OP_MODE_PURE;
                    limEnableHtRifsProtection(pMac, false, overlap, pBeaconParams,psessionEntry);
                    limEnableHtOBSSProtection(pMac,  false, overlap, pBeaconParams,psessionEntry);        
                }
            }
            PELOG1(limLog(pMac, LOG1, FL("===> Protection from HT 20 Disabled\n"));)
            pBeaconParams->ht20MhzCoexist = psessionEntry->beaconParams.ht20Coexist = false;
            pBeaconParams->paramChangeBitmap |= PARAM_HT20MHZCOEXIST_CHANGED;
        }
        //for station role
        else
        {
            PELOG1(limLog(pMac, LOG1, FL("===> Protection from HT20 Disabled\n"));)
            pBeaconParams->ht20MhzCoexist = psessionEntry->beaconParams.ht20Coexist = false;
            pBeaconParams->paramChangeBitmap |= PARAM_HT20MHZCOEXIST_CHANGED;
        }
