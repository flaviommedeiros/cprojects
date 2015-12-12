if ( (CSR_IS_WDS_AP(pProfile))
#ifdef WLAN_SOFTAP_FEATURE
             || (CSR_IS_INFRA_AP(pProfile))
#endif
            )
            {
                // Attempt to start this WDS...
                csrRoamAssignDefaultParam( pMac, pCommand );
                /* For AP WDS, we dont have any BSSDescription */
                status = csrRoamStartWds( pMac, sessionId, pProfile, NULL );
                if(HAL_STATUS_SUCCESS(status))
                {
                    eRoamState = eCsrContinueRoaming;
                }
                else 
                {
                    //it somehow fail need to stop
                    eRoamState = eCsrStopRoaming;
                }
            }
            else 
            {
                //Nothing we can do
                smsLog(pMac, LOGW, FL("cannot continue without BSS list\n"));
                eRoamState = eCsrStopRoaming;
                break;
            }
