if ( pBssDesc || CSR_IS_WDS_AP( pProfile )
#ifdef WLAN_SOFTAP_FEATURE
                     || CSR_IS_INFRA_AP(pProfile)
#endif
                    ) 
                    {      
                        // Set parameters for this Bss.    
                        status = csrRoamSetBssConfigCfg(pMac, sessionId, pProfile, pBssDesc, pBssConfig, pIes);
                    }
