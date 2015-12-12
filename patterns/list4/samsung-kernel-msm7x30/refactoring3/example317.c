switch( pCommand->u.roamCmd.roamReason )
            {
                // If this transition is because of an 802.11 OID, then we transition
                // back to INIT state so we sit waiting for more OIDs to be issued and
                // we don't start the IDLE timer.
                case eCsrSmeIssuedFTReassoc:
                case eCsrSmeIssuedAssocToSimilarAP:
                case eCsrHddIssued:
                    csrRoamStateChange( pMac, eCSR_ROAMING_STATE_IDLE, sessionId );
                    palZeroMemory(pMac->hHdd, &roamInfo, sizeof(tCsrRoamInfo));
                    roamInfo.pBssDesc = pCommand->u.roamCmd.pLastRoamBss;
                    roamInfo.statusCode = pSession->joinFailStatusCode.statusCode;
                    roamInfo.reasonCode = pSession->joinFailStatusCode.reasonCode;
                    /* Defeaturize this later if needed */
#ifdef WLAN_FEATURE_NEIGHBOR_ROAMING
                    /* If Join fails while Handoff is in progress, indicate disassociated event to supplicant to reconnect */
                    if (csrRoamIsHandoffInProgress(pMac))
                    {
                        /* Should indicate neighbor roam algorithm about the connect failure here */
                        csrNeighborRoamIndicateConnect(pMac, (tANI_U8)sessionId, VOS_STATUS_E_FAILURE);
                    }
#endif
                        if(pSession->bRefAssocStartCnt > 0)
                        {
                            pSession->bRefAssocStartCnt--;
                            if(eCsrJoinFailureDueToConcurrency == Result)
                            {
                                csrRoamCallCallback(pMac, sessionId, &roamInfo, pCommand->u.roamCmd.roamId, 
                                                eCSR_ROAM_ASSOCIATION_COMPLETION, 
                                                eCSR_ROAM_RESULT_ASSOC_FAIL_CON_CHANNEL);
                            }
                            else
                            {
                                csrRoamCallCallback(pMac, sessionId, &roamInfo, pCommand->u.roamCmd.roamId, 
                                                eCSR_ROAM_ASSOCIATION_COMPLETION, 
                                                eCSR_ROAM_RESULT_FAILURE);
                            }
                        }
                    smsLog(pMac, LOG1, FL("  roam(reason %d) failed\n"), pCommand->u.roamCmd.roamReason);
#ifndef WLAN_MDM_CODE_REDUCTION_OPT
                    sme_QosCsrEventInd(pMac, (tANI_U8)sessionId, SME_QOS_CSR_DISCONNECT_IND, NULL);
#endif
                    csrRoamCompletion(pMac, sessionId, NULL, pCommand, eCSR_ROAM_RESULT_FAILURE, eANI_BOOLEAN_FALSE);
                    csrScanStartIdleScan(pMac);
#ifdef FEATURE_WLAN_BTAMP_UT_RF
                    //For WDS STA. To fix the issue where the WDS AP side may be too busy by
                    //BT activity and not able to recevie WLAN traffic. Retry the join
                    if( CSR_IS_WDS_STA(pProfile) )
                    {
                        csrRoamStartJoinRetryTimer(pMac, sessionId, CSR_JOIN_RETRY_TIMEOUT_PERIOD);
                    }
#endif
                    break;
                case eCsrHddIssuedReassocToSameAP:
                case eCsrSmeIssuedReassocToSameAP:
                    csrRoamStateChange( pMac, eCSR_ROAMING_STATE_IDLE, sessionId);

                    csrRoamCallCallback(pMac, sessionId, NULL, pCommand->u.roamCmd.roamId, eCSR_ROAM_DISASSOCIATED, eCSR_ROAM_RESULT_FORCED);
#ifndef WLAN_MDM_CODE_REDUCTION_OPT                                        
                    sme_QosCsrEventInd(pMac, (tANI_U8)sessionId, SME_QOS_CSR_DISCONNECT_IND, NULL);
#endif
                    csrRoamCompletion(pMac, sessionId, NULL, pCommand, eCSR_ROAM_RESULT_FAILURE, eANI_BOOLEAN_FALSE);
                    csrScanStartIdleScan(pMac);
                    break;
                case eCsrForcedDisassoc:
                case eCsrForcedDeauth:
                case eCsrSmeIssuedIbssJoinFailure:
                    csrRoamStateChange( pMac, eCSR_ROAMING_STATE_IDLE, sessionId);

                    if(eCsrSmeIssuedIbssJoinFailure == pCommand->u.roamCmd.roamReason)
                    {
                        // Notify HDD that IBSS join failed
                        csrRoamCallCallback(pMac, sessionId, NULL, 0, eCSR_ROAM_IBSS_IND, eCSR_ROAM_RESULT_IBSS_JOIN_FAILED);
                    }
                    else
                    {
                        csrRoamCallCallback(pMac, sessionId, NULL, 
                                            pCommand->u.roamCmd.roamId, 
                                            eCSR_ROAM_DISASSOCIATED, eCSR_ROAM_RESULT_FORCED);
                    }
#ifndef WLAN_MDM_CODE_REDUCTION_OPT
                    sme_QosCsrEventInd(pMac, (tANI_U8)sessionId, SME_QOS_CSR_DISCONNECT_IND, NULL);
#endif
                    csrRoamLinkDown(pMac, sessionId);
                    csrScanStartIdleScan(pMac);
                    break;
                case eCsrForcedIbssLeave:
                     csrRoamCallCallback(pMac, sessionId, NULL, 
                                        pCommand->u.roamCmd.roamId, 
                                        eCSR_ROAM_IBSS_LEAVE,
                                        eCSR_ROAM_RESULT_IBSS_STOP);
                    break;
                case eCsrForcedDisassocMICFailure:
                    csrRoamStateChange( pMac, eCSR_ROAMING_STATE_IDLE, sessionId );

                    csrRoamCallCallback(pMac, sessionId, NULL, pCommand->u.roamCmd.roamId, eCSR_ROAM_DISASSOCIATED, eCSR_ROAM_RESULT_MIC_FAILURE);
#ifndef WLAN_MDM_CODE_REDUCTION_OPT
                    sme_QosCsrEventInd(pMac, (tANI_U8)sessionId, SME_QOS_CSR_DISCONNECT_REQ, NULL);
#endif
                    csrScanStartIdleScan(pMac);
                    break;
#ifdef WLAN_SOFTAP_FEATURE
                case eCsrStopBss:
                    csrRoamCallCallback(pMac, sessionId, NULL, 
                                        pCommand->u.roamCmd.roamId, 
                                        eCSR_ROAM_INFRA_IND, 
                                        eCSR_ROAM_RESULT_INFRA_STOPPED);
                    break;
                case eCsrForcedDisassocSta:
                case eCsrForcedDeauthSta:
                   csrRoamStateChange( pMac, eCSR_ROAMING_STATE_JOINED, sessionId);
                   if( CSR_IS_SESSION_VALID(pMac, sessionId) )
                   {                    
                       pSession = CSR_GET_SESSION(pMac, sessionId);
                       if (!pSession)
                           break;

                       if ( CSR_IS_INFRA_AP(&pSession->connectedProfile) )
                       {
                           roamInfo.u.pConnectedProfile = &pSession->connectedProfile;
                           palCopyMemory(pMac->hHdd, roamInfo.peerMac, 
                              pCommand->u.roamCmd.peerMac, sizeof(tSirMacAddr));
                           roamInfo.reasonCode = eCSR_ROAM_RESULT_FORCED;
                           roamInfo.statusCode = eSIR_SME_SUCCESS;
                           status = csrRoamCallCallback(pMac, sessionId, 
                                       &roamInfo, pCommand->u.roamCmd.roamId, 
                                       eCSR_ROAM_LOSTLINK, eCSR_ROAM_RESULT_FORCED);
                       }
                   }
                   break;
#endif
                case eCsrLostLink1:
                    // if lost link roam1 failed, then issue lost link Scan2 ...
                    csrScanRequestLostLink2(pMac, sessionId);
                    break;
                case eCsrLostLink2:
                    // if lost link roam2 failed, then issue lost link scan3 ...
                    csrScanRequestLostLink3(pMac, sessionId);
                    break;
                case eCsrLostLink3:
                default:
                    csrRoamStateChange( pMac, eCSR_ROAMING_STATE_IDLE, sessionId );

                    //We are done with one round of lostlink roaming here
                    csrScanHandleFailedLostlink3(pMac, sessionId);
                    break;
            }
