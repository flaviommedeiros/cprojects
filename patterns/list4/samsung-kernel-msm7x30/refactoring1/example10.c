if(pMac->lim.gpSession[i].limMlmState == eLIM_MLM_LINK_ESTABLISHED_STATE)
            {
               if ((pMac->lim.gpSession[i].limSystemRole != eLIM_BT_AMP_STA_ROLE) &&
                   (pInitScanParam->scanEntry.activeBSScnt < HAL_NUM_BSSID))
                {
                    pInitScanParam->scanEntry.bssIdx[pInitScanParam->scanEntry.activeBSScnt] 
                        = pMac->lim.gpSession[i].bssIdx;
                    pInitScanParam->scanEntry.activeBSScnt++;

                }
            }
#ifdef WLAN_FEATURE_P2P
            else if( (eLIM_AP_ROLE == pMac->lim.gpSession[i].limSystemRole ) 
                    && ( VOS_P2P_GO_MODE == pMac->lim.gpSession[i].pePersona )
                   )
            {
                pInitScanParam->useNoA = TRUE;
            }
#endif
