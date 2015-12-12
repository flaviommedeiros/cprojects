if ( (pSmeStartBssReq->bssType == eSIR_BTAMP_AP_MODE)
#ifdef WLAN_SOFTAP_FEATURE
        || (pSmeStartBssReq->bssType == eSIR_INFRA_AP_MODE)
#endif
        )
        {
            if( eHAL_STATUS_SUCCESS != palAllocateMemory( pMac->hHdd, (void **)&psessionEntry->parsedAssocReq,
                                                          (psessionEntry->dph.dphHashTable.size * sizeof(tpSirAssocReq)) ))
            {
                limLog(pMac, LOGW, FL("palAllocateMemory() failed\n"));
                retCode = eSIR_SME_RESOURCES_UNAVAILABLE;
                goto free;
            }
            palZeroMemory(pMac->hHdd, psessionEntry->parsedAssocReq, (psessionEntry->dph.dphHashTable.size * sizeof(tpSirAssocReq)) );
        }
