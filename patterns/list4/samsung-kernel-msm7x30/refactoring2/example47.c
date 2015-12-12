#ifndef WLAN_MDM_CODE_REDUCTION_OPT
if( btcIsReadyForUapsd(pMac) )
#endif /* WLAN_MDM_CODE_REDUCTION_OPT*/
         {
            /* Tell MAC to have device enter UAPSD mode. */
            if (pmcIssueCommand(hHal, eSmeCommandEnterUapsd, NULL, 0, FALSE) !=
               eHAL_STATUS_SUCCESS)
            {
               smsLog(pMac, LOGE, "PMC: failure to send message "
                  "eWNI_PMC_ENTER_BMPS_REQ\n");
               return eHAL_STATUS_FAILURE;
            }
         }
#ifndef WLAN_MDM_CODE_REDUCTION_OPT
         else
         {
            //Not ready for UAPSD at this time, save it first and wake up the chip
            smsLog(pMac, LOGE, " PMC state = %d\n",pMac->pmc.pmcState);
            pMac->pmc.uapsdSessionRequired = TRUE;
            /* While BTC traffic is going on, STA can be in BMPS
             * and need not go to Full Power */
            //fFullPower = VOS_TRUE;
         }
