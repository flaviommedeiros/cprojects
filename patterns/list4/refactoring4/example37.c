#ifdef WLAN_SOFTAP_FEATURE
if(CSR_IS_WDS_AP( pRoamInfo->u.pConnectedProfile))
#endif 
                        status = csrRoamCallCallback(pMac, sessionId, pRoamInfo, 0, eCSR_ROAM_WDS_IND, eCSR_ROAM_RESULT_WDS_ASSOCIATION_IND);
