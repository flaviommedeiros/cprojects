#ifdef WLAN_SOFTAP_FEATURE
if(psessionEntry->limSystemRole == eLIM_AP_ROLE){
        // Disabling the RIFS Protection means Enable the RIFS mode of operation in the BSS
        if ((!enable) && (false == psessionEntry->beaconParams.fRIFSMode))
        {
            PELOG1(limLog(pMac, LOG1, FL(" => Rifs protection Disabled\n"));)
            pBeaconParams->fRIFSMode = psessionEntry->beaconParams.fRIFSMode = true;
            pBeaconParams->paramChangeBitmap |= PARAM_RIFS_MODE_CHANGED;
        }
        // Enabling the RIFS Protection means Disable the RIFS mode of operation in the BSS
        else if (enable && (true == psessionEntry->beaconParams.fRIFSMode))
        {
            PELOG1(limLog(pMac, LOG1, FL("===> Rifs Protection Enabled\n"));)
            pBeaconParams->fRIFSMode = psessionEntry->beaconParams.fRIFSMode = false;
            pBeaconParams->paramChangeBitmap |= PARAM_RIFS_MODE_CHANGED;
        }
    }else
#endif
    {
        // Disabling the RIFS Protection means Enable the RIFS mode of operation in the BSS
        if ((!enable) && (false == psessionEntry->beaconParams.fRIFSMode))
        {
            PELOG1(limLog(pMac, LOG1, FL(" => Rifs protection Disabled\n"));)
            pBeaconParams->fRIFSMode = psessionEntry->beaconParams.fRIFSMode = true;
            pBeaconParams->paramChangeBitmap |= PARAM_RIFS_MODE_CHANGED;
        }
    // Enabling the RIFS Protection means Disable the RIFS mode of operation in the BSS
        else if (enable && (true == psessionEntry->beaconParams.fRIFSMode))
        {
            PELOG1(limLog(pMac, LOG1, FL("===> Rifs Protection Enabled\n"));)
            pBeaconParams->fRIFSMode = psessionEntry->beaconParams.fRIFSMode = false;
            pBeaconParams->paramChangeBitmap |= PARAM_RIFS_MODE_CHANGED;
        }
    }
