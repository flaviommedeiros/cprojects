#ifdef WLAN_SOFTAP_FEATURE
if(psessionEntry->limSystemRole == eLIM_AP_ROLE){
        if ((enable) && (false == psessionEntry->beaconParams.fLsigTXOPProtectionFullSupport))
        {
            PELOG1(limLog(pMac, LOG1, FL(" => Prtection from LsigTxop Enabled\n"));)
            pBeaconParams->fLsigTXOPProtectionFullSupport = psessionEntry->beaconParams.fLsigTXOPProtectionFullSupport = true;
            pBeaconParams->paramChangeBitmap |= PARAM_LSIG_TXOP_FULL_SUPPORT_CHANGED;
        }
        else if (!enable && (true == psessionEntry->beaconParams.fLsigTXOPProtectionFullSupport))
        {
            PELOG1(limLog(pMac, LOG1, FL("===> Protection from LsigTxop Disabled\n"));)
            pBeaconParams->fLsigTXOPProtectionFullSupport= psessionEntry->beaconParams.fLsigTXOPProtectionFullSupport = false;
            pBeaconParams->paramChangeBitmap |= PARAM_LSIG_TXOP_FULL_SUPPORT_CHANGED;
        }
    }else
#endif
    {
        if ((enable) && (false == psessionEntry->beaconParams.fLsigTXOPProtectionFullSupport))
        {
            PELOG1(limLog(pMac, LOG1, FL(" => Prtection from LsigTxop Enabled\n"));)
            pBeaconParams->fLsigTXOPProtectionFullSupport = psessionEntry->beaconParams.fLsigTXOPProtectionFullSupport = true;
            pBeaconParams->paramChangeBitmap |= PARAM_LSIG_TXOP_FULL_SUPPORT_CHANGED;
        }
        else if (!enable && (true == psessionEntry->beaconParams.fLsigTXOPProtectionFullSupport))
        {
            PELOG1(limLog(pMac, LOG1, FL("===> Protection from LsigTxop Disabled\n"));)
            pBeaconParams->fLsigTXOPProtectionFullSupport= psessionEntry->beaconParams.fLsigTXOPProtectionFullSupport = false;
            pBeaconParams->paramChangeBitmap |= PARAM_LSIG_TXOP_FULL_SUPPORT_CHANGED;
        }
    }
