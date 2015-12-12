#ifdef WLAN_SOFTAP_FEATURE
if(psessionEntry->limSystemRole == eLIM_AP_ROLE){
        if ((enable) && (false == psessionEntry->beaconParams.llnNonGFCoexist))
        {
            PELOG1(limLog(pMac, LOG1, FL(" => Prtection from non GF Enabled\n"));)
            pBeaconParams->llnNonGFCoexist = psessionEntry->beaconParams.llnNonGFCoexist = true;
            pBeaconParams->paramChangeBitmap |= PARAM_NON_GF_DEVICES_PRESENT_CHANGED;
        }
        else if (!enable && (true == psessionEntry->beaconParams.llnNonGFCoexist))
        {
            PELOG1(limLog(pMac, LOG1, FL("===> Protection from Non GF Disabled\n"));)
            pBeaconParams->llnNonGFCoexist = psessionEntry->beaconParams.llnNonGFCoexist = false;
            pBeaconParams->paramChangeBitmap |= PARAM_NON_GF_DEVICES_PRESENT_CHANGED;
        }
    }else
#endif
    {
        if ((enable) && (false == psessionEntry->beaconParams.llnNonGFCoexist))
        {
            PELOG1(limLog(pMac, LOG1, FL(" => Prtection from non GF Enabled\n"));)
            pBeaconParams->llnNonGFCoexist = psessionEntry->beaconParams.llnNonGFCoexist = true;
            pBeaconParams->paramChangeBitmap |= PARAM_NON_GF_DEVICES_PRESENT_CHANGED;
        }
        else if (!enable && (true == psessionEntry->beaconParams.llnNonGFCoexist))
        {
            PELOG1(limLog(pMac, LOG1, FL("===> Protection from Non GF Disabled\n"));)
            pBeaconParams->llnNonGFCoexist = psessionEntry->beaconParams.llnNonGFCoexist = false;
            pBeaconParams->paramChangeBitmap |= PARAM_NON_GF_DEVICES_PRESENT_CHANGED;
        }
    }
