if( csrIsBssTypeIBSS(pProfile->BSSType) || CSR_IS_WDS( pProfile )
#ifdef WLAN_SOFTAP_FEATURE
              || CSR_IS_INFRA_AP(pProfile)
#endif
            )
            {
                csrRoamPrepareBssParams(pMac, sessionId, pProfile, pBssDesc, pBssConfig, pIes);
            }
