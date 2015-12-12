#ifdef WLAN_SOFTAP_FEATURE
if (eLIM_AP_ROLE == psessionEntry->limSystemRole){
        if ((enable) && (false == psessionEntry->beaconParams.gHTObssMode) )
        {
            PELOG1(limLog(pMac, LOG1, FL("=>obss protection enabled\n"));)
            psessionEntry->beaconParams.gHTObssMode = true;
            pBeaconParams->paramChangeBitmap |= PARAM_OBSS_MODE_CHANGED; // UPDATE AN ENUM FOR OBSS MODE <todo>
        
         }
         else if (!enable && (true == psessionEntry->beaconParams.gHTObssMode)) 
         {
            PELOG1(limLog(pMac, LOG1, FL("===> obss Protection disabled\n"));)
            psessionEntry->beaconParams.gHTObssMode = false;
            pBeaconParams->paramChangeBitmap |= PARAM_OBSS_MODE_CHANGED;

         }
//CR-263021: OBSS bit is not switching back to 0 after disabling the overlapping legacy BSS
         if (!enable && !overlap)
         {
             psessionEntry->gLimOverlap11gParams.protectionEnabled = false;
         }
    } else
#endif
    {
        if ((enable) && (false == psessionEntry->beaconParams.gHTObssMode) )
        {
            PELOG1(limLog(pMac, LOG1, FL("=>obss protection enabled\n"));)
            psessionEntry->beaconParams.gHTObssMode = true;
            pBeaconParams->paramChangeBitmap |= PARAM_OBSS_MODE_CHANGED; // UPDATE AN ENUM FOR OBSS MODE <todo>

        }
        else if (!enable && (true == psessionEntry->beaconParams.gHTObssMode)) 
        {

            PELOG1(limLog(pMac, LOG1, FL("===> obss Protection disabled\n"));)
            psessionEntry->beaconParams.gHTObssMode = false;
            pBeaconParams->paramChangeBitmap |= PARAM_OBSS_MODE_CHANGED;

        }
    }
