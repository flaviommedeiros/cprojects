#ifdef WLAN_SOFTAP_FEATURE
if (!CSR_IS_INFRA_AP(pProfile))
#endif
                {
                    pScanResult = csrScanAppendBssDescription( pMac, pSirBssDesc, pIes );
                }
