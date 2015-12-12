#ifndef WLAN_MDM_CODE_REDUCTION_OPT
if( btcIsReadyForUapsd( pMac ) )
#endif /* WLAN_MDM_CODE_REDUCTION_OPT*/
            {
               /* Put device in BMPS mode first. This step should NEVER fail.
                  That is why no need to buffer the UAPSD request*/
               if(pmcEnterRequestBmpsState(hHal) != eHAL_STATUS_SUCCESS)
               {
                   smsLog(pMac, LOGE, "PMC: Device in Full Power. Enter Request Bmps failed. "
                            "UAPSD request will be dropped \n");
                  return eHAL_STATUS_FAILURE;
               }
            }
#ifndef WLAN_MDM_CODE_REDUCTION_OPT
            else
            {
               (void)pmcStartTrafficTimer(hHal, pMac->pmc.bmpsConfig.trafficMeasurePeriod);
            }
