#ifdef WLAN_SOFTAP_FEATURE
if ( (psessionEntry->limSystemRole == eLIM_AP_ROLE ) &&
         (val && psessionEntry->gLimNoShortSlotParams.numNonShortSlotSta == 0))
      {
         // enable short slot time
         PELOG1(limLog(pMac, LOG1, FL("All associated STAs have short slot time support now.\n"));)
         //reset the cache
         palZeroMemory( pMac->hHdd, (tANI_U8 *)&psessionEntry->gLimNoShortSlotParams , sizeof(tLimNoShortSlotParams));
         // in case of AP set SHORT_SLOT_TIME to enable
         if (psessionEntry->limSystemRole == eLIM_AP_ROLE)
         {
            pBeaconParams->fShortSlotTime = true;
            pBeaconParams->paramChangeBitmap |= PARAM_SHORT_SLOT_TIME_CHANGED;
            psessionEntry->shortSlotTimeSupported = true;
         }
      }
      else 
#endif
      {
         if (val && pMac->lim.gLimNoShortSlotParams.numNonShortSlotSta == 0)
         {
            // enable short slot time
            PELOG1(limLog(pMac, LOG1, FL("All associated STAs have short slot time support now.\n"));)
            //reset the cache
            palZeroMemory( pMac->hHdd, (tANI_U8 *)&pMac->lim.gLimNoShortSlotParams , sizeof(tLimNoShortSlotParams));
            // in case of AP set SHORT_SLOT_TIME to enable
            if (psessionEntry->limSystemRole == eLIM_AP_ROLE)
            {
               pBeaconParams->fShortSlotTime = true;
               pBeaconParams->paramChangeBitmap |= PARAM_SHORT_SLOT_TIME_CHANGED;
               psessionEntry->shortSlotTimeSupported = true;
            }
          }
       }
