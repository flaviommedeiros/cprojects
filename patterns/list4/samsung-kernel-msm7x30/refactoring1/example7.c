if (CSR_IS_WDS(&pSession->connectedProfile)){
#endif
                pSession->connectState = eCSR_ASSOC_STATE_TYPE_WDS_DISCONNECTED;
                csrRoamCallCallback(pMac, sessionId, &roamInfo, pCommand->u.roamCmd.roamId, 
                                        eCSR_ROAM_WDS_IND, 
                                        eCSR_ROAM_RESULT_WDS_DISASSOCIATED);
#ifdef  WLAN_SOFTAP_FEATURE
                                }else if (CSR_IS_INFRA_AP(&pSession->connectedProfile)){
                                        pSession->connectState = eCSR_ASSOC_STATE_TYPE_INFRA_DISCONNECTED;
                                        csrRoamCallCallback(pMac, sessionId, &roamInfo, pCommand->u.roamCmd.roamId,
                                                                                eCSR_ROAM_INFRA_IND,
                                                                                eCSR_ROAM_RESULT_INFRA_DISASSOCIATED);
                                }
#endif
