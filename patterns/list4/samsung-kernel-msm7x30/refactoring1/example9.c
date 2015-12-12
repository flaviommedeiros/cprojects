if(false == psessionEntry->beaconParams.llgCoexist)
        {
            pBeaconParams->llgCoexist = psessionEntry->beaconParams.llgCoexist = true;
            pBeaconParams->paramChangeBitmap |= PARAM_llGCOEXIST_CHANGED;
        }
#ifdef WLAN_SOFTAP_FEATURE
        else if (true == psessionEntry->gLimOverlap11gParams.protectionEnabled)
        {
            // As operating mode changed after G station assoc some way to update beacon
            // This addresses the issue of mode not changing to - 11 in beacon when OBSS overlap is enabled
            //pMac->sch.schObject.fBeaconChanged = 1;
            pBeaconParams->paramChangeBitmap |= PARAM_llGCOEXIST_CHANGED;
        }
#endif
