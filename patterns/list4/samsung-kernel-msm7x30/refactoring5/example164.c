#ifdef WLAN_SOFTAP_FEATURE
if(eLIM_AP_ROLE == psessionEntry->limSystemRole)
        {
            if(overlap)
            {
                //Overlap Legacy protection disabled.
                if (psessionEntry->gLim11gParams.numSta == 0)
                psessionEntry->gLimOverlap11gParams.protectionEnabled = false;

                // no HT op mode change if any of the overlap protection enabled.
                if(!(psessionEntry->gLimOlbcParams.protectionEnabled ||
                    psessionEntry->gLimOverlapHt20Params.protectionEnabled ||
                    psessionEntry->gLimOverlapNonGfParams.protectionEnabled))
                {
                    //Check if there is a need to change HT OP mode.
                    if(eSIR_HT_OP_MODE_OVERLAP_LEGACY == psessionEntry->htOperMode)
                    {
                        limEnableHtRifsProtection(pMac, false, overlap, pBeaconParams,psessionEntry);
                        limEnableHtOBSSProtection(pMac,  false, overlap, pBeaconParams,psessionEntry);            

                        if(psessionEntry->gLimHt20Params.protectionEnabled){
                            //Commenting because of CR 258588 WFA cert
                            //psessionEntry->htOperMode = eSIR_HT_OP_MODE_NO_LEGACY_20MHZ_HT;
                            psessionEntry->htOperMode = eSIR_HT_OP_MODE_PURE;
                        }
                        else
                            psessionEntry->htOperMode = eSIR_HT_OP_MODE_PURE;
                    }
                }
            }
            else
            {
                //Disable protection from 11G stations.
                psessionEntry->gLim11gParams.protectionEnabled = false;
                //Check if any other non-HT protection enabled.
                if(!psessionEntry->gLim11bParams.protectionEnabled)
                {

                    //Right now we are in HT OP Mixed mode.
                    //Change HT op mode appropriately.
                    limEnableHtOBSSProtection(pMac,  false, overlap, pBeaconParams,psessionEntry);            

                    //Change HT OP mode to 01 if any overlap protection enabled
                    if(psessionEntry->gLimOlbcParams.protectionEnabled ||
                        psessionEntry->gLimOverlap11gParams.protectionEnabled ||
                        psessionEntry->gLimOverlapHt20Params.protectionEnabled ||
                        psessionEntry->gLimOverlapNonGfParams.protectionEnabled)

                    {
                        psessionEntry->htOperMode = eSIR_HT_OP_MODE_OVERLAP_LEGACY;
                        limEnableHtRifsProtection(pMac, true, overlap, pBeaconParams,psessionEntry);
                    }
                    else if(psessionEntry->gLimHt20Params.protectionEnabled)
                    {
                        //Commenting because of CR 258588 WFA cert
                        //psessionEntry->htOperMode = eSIR_HT_OP_MODE_NO_LEGACY_20MHZ_HT;
                        psessionEntry->htOperMode = eSIR_HT_OP_MODE_PURE;
                        limEnableHtRifsProtection(pMac, false, overlap, pBeaconParams,psessionEntry);
                    }
                    else
                    {
                        psessionEntry->htOperMode = eSIR_HT_OP_MODE_PURE;
                        limEnableHtRifsProtection(pMac, false, overlap, pBeaconParams,psessionEntry);
                    }
                }
            }
            if(!psessionEntry->gLimOverlap11gParams.protectionEnabled &&
                  !psessionEntry->gLim11gParams.protectionEnabled)
            {
                PELOG1(limLog(pMac, LOG1, FL("===> Protection from 11G Disabled\n"));)
                pBeaconParams->llgCoexist = psessionEntry->beaconParams.llgCoexist = false;
                pBeaconParams->paramChangeBitmap |= PARAM_llGCOEXIST_CHANGED;
            }
        }else if(eLIM_BT_AMP_AP_ROLE == psessionEntry->limSystemRole)
#else
        if((eLIM_AP_ROLE == psessionEntry->limSystemRole)||(eLIM_BT_AMP_AP_ROLE == psessionEntry->limSystemRole))
#endif
        {
            if(overlap)
            {
                //Overlap Legacy protection disabled.
                pMac->lim.gLimOverlap11gParams.protectionEnabled = false;

                // no HT op mode change if any of the overlap protection enabled.
                if(!(psessionEntry->gLimOlbcParams.protectionEnabled ||
                    psessionEntry->gLimOverlapHt20Params.protectionEnabled ||
                    psessionEntry->gLimOverlapNonGfParams.protectionEnabled))
                {
                    //Check if there is a need to change HT OP mode.
                    if(eSIR_HT_OP_MODE_OVERLAP_LEGACY == pMac->lim.gHTOperMode)
                    {
                        limEnableHtRifsProtection(pMac, false, overlap, pBeaconParams,psessionEntry);
                        limEnableHtOBSSProtection(pMac,  false, overlap, pBeaconParams,psessionEntry);            

                        if(psessionEntry->gLimHt20Params.protectionEnabled)
                            pMac->lim.gHTOperMode = eSIR_HT_OP_MODE_NO_LEGACY_20MHZ_HT;
                        else
                            pMac->lim.gHTOperMode = eSIR_HT_OP_MODE_PURE;
                    }
                }
            }
            else
            {
                //Disable protection from 11G stations.
                psessionEntry->gLim11gParams.protectionEnabled = false;
                //Check if any other non-HT protection enabled.
                if(!psessionEntry->gLim11bParams.protectionEnabled)
                {

                    //Right now we are in HT OP Mixed mode.
                    //Change HT op mode appropriately.
                    limEnableHtOBSSProtection(pMac,  false, overlap, pBeaconParams,psessionEntry);            

                    //Change HT OP mode to 01 if any overlap protection enabled
                    if(psessionEntry->gLimOlbcParams.protectionEnabled ||
                        pMac->lim.gLimOverlap11gParams.protectionEnabled ||
                        pMac->lim.gLimOverlapHt20Params.protectionEnabled ||
                        pMac->lim.gLimOverlapNonGfParams.protectionEnabled)

                    {
                        pMac->lim.gHTOperMode = eSIR_HT_OP_MODE_OVERLAP_LEGACY;
                        limEnableHtRifsProtection(pMac, true, overlap, pBeaconParams,psessionEntry);
                    }
                    else if(psessionEntry->gLimHt20Params.protectionEnabled)
                    {
                        pMac->lim.gHTOperMode = eSIR_HT_OP_MODE_NO_LEGACY_20MHZ_HT;
                        limEnableHtRifsProtection(pMac, false, overlap, pBeaconParams,psessionEntry);
                    }
                    else
                    {
                        pMac->lim.gHTOperMode = eSIR_HT_OP_MODE_PURE;
                        limEnableHtRifsProtection(pMac, false, overlap, pBeaconParams,psessionEntry);
                    }
                }
            }
            if(!pMac->lim.gLimOverlap11gParams.protectionEnabled &&
                  !psessionEntry->gLim11gParams.protectionEnabled)
            {
                PELOG1(limLog(pMac, LOG1, FL("===> Protection from 11G Disabled\n"));)
                pBeaconParams->llgCoexist = psessionEntry->beaconParams.llgCoexist = false;
                pBeaconParams->paramChangeBitmap |= PARAM_llGCOEXIST_CHANGED;
            }
        }
        //for station role
        else
        {
            PELOG1(limLog(pMac, LOG1, FL("===> Protection from 11G Disabled\n"));)
            pBeaconParams->llgCoexist = psessionEntry->beaconParams.llgCoexist = false;
            pBeaconParams->paramChangeBitmap |= PARAM_llGCOEXIST_CHANGED;
        }
