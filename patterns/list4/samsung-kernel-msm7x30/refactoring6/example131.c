if( (pMlmStartReq->bssType == eSIR_BTAMP_STA_MODE) || (pMlmStartReq->bssType == eSIR_BTAMP_AP_MODE )
#ifdef WLAN_SOFTAP_FEATURE
            || (pMlmStartReq->bssType == eSIR_INFRA_AP_MODE)
#endif
        )
        {
            //len = sizeof(tSirMacAddr);
            //retStatus = wlan_cfgGetStr(pMac, WNI_CFG_STA_ID, (tANI_U8 *) pMlmStartReq->bssId, &len);
            //if (retStatus != eSIR_SUCCESS)
            //limLog(pMac, LOGP, FL("could not retrive BSSID, retStatus=%d\n"), retStatus);

            /* Copy the BSSId from sessionTable to mlmStartReq struct */
            sirCopyMacAddr(pMlmStartReq->bssId,psessionEntry->bssId);
        }

        else // ibss mode
        {
            pMac->lim.gLimIbssCoalescingHappened = false;

            if((retStatus = wlan_cfgGetInt(pMac, WNI_CFG_IBSS_AUTO_BSSID, &autoGenBssId)) != eSIR_SUCCESS)
            {
                limLog(pMac, LOGP, FL("Could not retrieve Auto Gen BSSID, retStatus=%d\n"), retStatus);
                retCode = eSIR_LOGP_EXCEPTION;
                goto free;
            }

            if(!autoGenBssId)
            {   
                // We're not auto generating BSSID. Instead, get it from session entry
                sirCopyMacAddr(pMlmStartReq->bssId,psessionEntry->bssId);
                
                if(pMlmStartReq->bssId[0] & 0x01)
                {
                   PELOGE(limLog(pMac, LOGE, FL("Request to start IBSS with group BSSID\n Autogenerating the BSSID\n"));)                    
                   autoGenBssId = TRUE;
                }             
            }

            if( autoGenBssId )
            {   //if BSSID is not any uc id. then use locally generated BSSID.
                //Autogenerate the BSSID
                limGetRandomBssid( pMac, pMlmStartReq->bssId);
                pMlmStartReq->bssId[0]= 0x02;
                
                /* Copy randomly generated BSSID to the session Table */
                sirCopyMacAddr(psessionEntry->bssId,pMlmStartReq->bssId);
            }
        }
