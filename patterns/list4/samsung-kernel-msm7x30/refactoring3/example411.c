switch(psessionEntry->limSystemRole){

    case eLIM_STA_IN_IBSS_ROLE:
    case eLIM_BT_AMP_AP_ROLE:
    case eLIM_BT_AMP_STA_ROLE:
        // generate IBSS parameter set
        if(psessionEntry->statypeForBss == STA_ENTRY_SELF)
            writeBeaconToMemory(pMac, (tANI_U16) beaconSize, (tANI_U16)beaconSize, psessionEntry);
    else
        PELOGE(schLog(pMac, LOGE, FL("can not send beacon for PEER session entry\n"));)
        break;

#ifdef WLAN_SOFTAP_FEATURE
    case eLIM_AP_ROLE:{
         tANI_U8 *ptr = &pMac->sch.schObject.gSchBeaconFrameBegin[pMac->sch.schObject.gSchBeaconOffsetBegin];
         tANI_U16 timLength = 0;
         if(psessionEntry->statypeForBss == STA_ENTRY_SELF){
             pmmGenerateTIM(pMac, &ptr, &timLength, psessionEntry->dtimPeriod);
         beaconSize += 2 + timLength;
         writeBeaconToMemory(pMac, (tANI_U16) beaconSize, (tANI_U16)beaconSize, psessionEntry);
     }
     else
         PELOGE(schLog(pMac, LOGE, FL("can not send beacon for PEER session entry\n"));)
         }
     break;
#endif

#ifdef ANI_PRODUCT_TYPE_AP
    case eLIM_AP_ROLE: 
    {
        tANI_U8 *ptr = &pMac->sch.schObject.gSchBeaconFrameBegin[pMac->sch.schObject.gSchBeaconOffsetBegin];
        tANI_U16 timLength = 0;

        if (pMac->sch.schObject.gSchCFPEnabled)
          ptr = __schUpdateCfpParam( pMac, ptr, &beaconSize);

        // generate TIM
        pmmGenerateTIM(pMac, &ptr, &timLength);
        beaconSize += 2 + timLength;

        /**
        * Safe to call this each time.
        * Based on the requirement for updating the
        * fixed beacon fields, this routine will
        * appropriately update the fixed fields
        */
        specialBeaconProcessing(pMac, beaconSize);
        writeBeaconToMemory(pMac, beaconSize, beaconSize, psessionEntry);
        pmmHandleTimBasedDisassociation( pMac, psessionEntry );
    }
    break;
#endif

    default:
        PELOGE(schLog(pMac, LOGE, FL("Error-PE has Receive PreBeconGenIndication when System is in %d role"),
               psessionEntry->limSystemRole);)
    }
