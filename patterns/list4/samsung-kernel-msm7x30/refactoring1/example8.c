if(CSR_IS_WDS_AP( pRoamInfo->u.pConnectedProfile))
                {
                    status = csrSendAssocIndToUpperLayerCnfMsg(pMac, pAssocInd, status, sessionId);
                }
#ifdef WLAN_SOFTAP_FEATURE
                else if(CSR_IS_INFRA_AP(pRoamInfo->u.pConnectedProfile) && (pRoamInfo->statusCode != eSIR_SME_ASSOC_REFUSED))
                {
                    pRoamInfo->fReassocReq = pAssocInd->reassocReq;
                    //status = csrRoamCallCallback(pMac, sessionId, pRoamInfo, 0, eCSR_ROAM_INFRA_IND, eCSR_ROAM_RESULT_INFRA_ASSOCIATION_CNF);
                    status = csrSendAssocIndToUpperLayerCnfMsg(pMac, pAssocInd, status, sessionId);
                }
#endif
