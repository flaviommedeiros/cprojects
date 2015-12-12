if ( csrIsBssTypeIBSS( pCommand->u.roamCmd.roamProfile.BSSType ) ||
                 CSR_IS_WDS( &pCommand->u.roamCmd.roamProfile ) 
#ifdef WLAN_SOFTAP_FEATURE
                  || CSR_IS_INFRA_AP(&pCommand->u.roamCmd.roamProfile) 
#endif
            )
            {
                if(!HAL_STATUS_SUCCESS(csrRoamIssueStartBss( pMac, sessionId,
                                        &pSession->bssParams, &pCommand->u.roamCmd.roamProfile, 
                                        pBssDesc, pCommand->u.roamCmd.roamId )))
                {
                    smsLog(pMac, LOGW, " CSR start BSS failed\n");
                    //We need to complete the command
                    csrRoamComplete(pMac, eCsrStartBssFailure, NULL);
                }
            }
            else
            {
                if (!pCommand->u.roamCmd.pRoamBssEntry)
                {
                    smsLog(pMac, LOGW, " pRoamBssEntry is NULL\n");
                    //We need to complete the command
                    csrRoamComplete(pMac, eCsrJoinFailure, NULL);
                    return;
                } 
                // If we are roaming TO an Infrastructure BSS...
                VOS_ASSERT(pScanResult != NULL); 
                if ( csrIsInfraBssDesc( pBssDesc ) )
                {
                    tDot11fBeaconIEs *pIesLocal = (tDot11fBeaconIEs *)pScanResult->Result.pvIes;
                    if(pIesLocal || (HAL_STATUS_SUCCESS(csrGetParsedBssDescriptionIEs(pMac, pBssDesc, &pIesLocal))) )
                    {
                    // ..and currently in an Infrastructure connection....
                    if( csrIsConnStateConnectedInfra( pMac, sessionId ) )
                    {
                        // ...and the SSIDs are equal, then we Reassoc.
                        if (  csrIsSsidEqual( pMac, pSession->pConnectBssDesc, pBssDesc, 
                                                    pIesLocal ) )
                        // ..and currently in an infrastructure connection
                        {
                            // then issue a Reassoc.
                            pCommand->u.roamCmd.fReassoc = eANI_BOOLEAN_TRUE;
                                csrRoamIssueReassociate( pMac, sessionId, pBssDesc, pIesLocal,
                                                        &pCommand->u.roamCmd.roamProfile );
                        }
                        else
                        {
                                                     
                            // otherwise, we have to issue a new Join request to LIM because we disassociated from the
                            // previously associated AP.
                            if(!HAL_STATUS_SUCCESS(csrRoamIssueJoin( pMac, sessionId, pBssDesc, 
                                                                                                            pIesLocal, 
                                                    &pCommand->u.roamCmd.roamProfile, pCommand->u.roamCmd.roamId )))
                            {
                                //try something else
                                csrRoam( pMac, pCommand );
                            }
                        }
                    }
                    else
                    {
                        eHalStatus  status = eHAL_STATUS_SUCCESS;
                         
                        /* We need to come with other way to figure out that this is because of HO in BMP
                           The below API will be only available for Android as it uses a different HO algorithm */
                        /* Reassoc request will be used only for CCX and 11r handoff whereas other legacy roaming should 
                         * use join request */
#ifdef WLAN_FEATURE_VOWIFI_11R
                        if (csrRoamIsHandoffInProgress(pMac) && 
                                                csrRoamIs11rAssoc(pMac))
                        {
                            status = csrRoamIssueReassociate(pMac, sessionId, pBssDesc, 
                                    (tDot11fBeaconIEs *)( pScanResult->Result.pvIes ), &pCommand->u.roamCmd.roamProfile);
                        }
                        else
#endif
#ifdef FEATURE_WLAN_CCX
                        if (csrRoamIsHandoffInProgress(pMac) && 
                                                csrRoamIsCCXAssoc(pMac))
                        {
                            // Now serialize the reassoc command.
                            status = csrRoamIssueReassociateCmd(pMac, sessionId);
                        }
                        else
#endif
#ifdef FEATURE_WLAN_LFR
                        if (csrRoamIsHandoffInProgress(pMac) && 
                                                csrRoamIsFastRoamEnabled(pMac))
                        {
                            // Now serialize the reassoc command.
                            status = csrRoamIssueReassociateCmd(pMac, sessionId);
                        }
                        else
#endif
                        // else we are not connected and attempting to Join.  Issue the
                        // Join request.
                        {
                            status = csrRoamIssueJoin( pMac, sessionId, pBssDesc, 
                                                (tDot11fBeaconIEs *)( pScanResult->Result.pvIes ),
                                                &pCommand->u.roamCmd.roamProfile, pCommand->u.roamCmd.roamId );
                        }
                        if(!HAL_STATUS_SUCCESS(status))
                        {
                            //try something else
                            csrRoam( pMac, pCommand );
                        }
                    }
                        if( !pScanResult->Result.pvIes )
                        {
                            //Locally allocated
                            palFreeMemory(pMac->hHdd, pIesLocal);
                        }
                    }
                }//if ( csrIsInfraBssDesc( pBssDesc ) )
                else
                {
                    smsLog(pMac, LOGW, FL("  found BSSType mismatching the one in BSS description\n"));
                }
            }
