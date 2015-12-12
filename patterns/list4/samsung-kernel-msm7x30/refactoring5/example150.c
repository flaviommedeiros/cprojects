#ifdef WLAN_SOFTAP_FEATURE
if (limIsAuthAlgoSupported(
                                      pMac,
                                      (tAniAuthType)
                                      pRxAuthFrameBody->authAlgoNumber, psessionEntry))
#else
            if (limIsAuthAlgoSupported(
                                      pMac,
                                      (tAniAuthType)
                                      pRxAuthFrameBody->authAlgoNumber))

#endif
            {
                switch (pRxAuthFrameBody->authAlgoNumber)
                {
                    case eSIR_OPEN_SYSTEM:
                        PELOGW(limLog(pMac, LOGW, FL("=======> eSIR_OPEN_SYSTEM  ...\n"));)
                        /// Create entry for this STA in pre-auth list
                        pAuthNode = limAcquireFreePreAuthNode(pMac, &pMac->lim.gLimPreAuthTimerTable);
                        if (pAuthNode == NULL)
                        {
                            // Log error
                            limLog(pMac, LOGW,
                                   FL("Max pre-auth nodes reached "));
                            limPrintMacAddr(pMac, pHdr->sa, LOGW);

                            return;
                        }

                        PELOG1(limLog(pMac, LOG1, FL("Alloc new data: %x peer \n"), pAuthNode);
                        limPrintMacAddr(pMac, pHdr->sa, LOG1);)

                        palCopyMemory( pMac->hHdd,
                                     (tANI_U8 *) pAuthNode->peerMacAddr,
                                     pHdr->sa,
                                     sizeof(tSirMacAddr));

                        pAuthNode->mlmState =
                        eLIM_MLM_AUTHENTICATED_STATE;
                        pAuthNode->authType = (tAniAuthType)
                                              pRxAuthFrameBody->authAlgoNumber;
                        pAuthNode->fSeen = 0;
                        pAuthNode->fTimerStarted = 0;
                        limAddPreAuthNode(pMac, pAuthNode);

                        /**
                         * Send Authenticaton frame with Success
                         * status code.
                         */

                        authFrame.authAlgoNumber =
                        pRxAuthFrameBody->authAlgoNumber;
                        authFrame.authTransactionSeqNumber =
                        pRxAuthFrameBody->authTransactionSeqNumber + 1;
                        authFrame.authStatusCode = eSIR_MAC_SUCCESS_STATUS;
                        limSendAuthMgmtFrame(
                                            pMac, &authFrame,
                                            pHdr->sa,
                                            LIM_NO_WEP_IN_FC,psessionEntry);

                        /// Send Auth indication to SME

                        palCopyMemory( pMac->hHdd,
                                     (tANI_U8 *) mlmAuthInd.peerMacAddr,
                                     (tANI_U8 *) pHdr->sa,
                                     sizeof(tSirMacAddr));
                        mlmAuthInd.authType = (tAniAuthType)
                                              pRxAuthFrameBody->authAlgoNumber;
                        mlmAuthInd.sessionId = psessionEntry->smeSessionId;

                        limPostSmeMessage(pMac,
                                          LIM_MLM_AUTH_IND,
                                          (tANI_U32 *) &mlmAuthInd);
                        break;

                    case eSIR_SHARED_KEY:
                        PELOGW(limLog(pMac, LOGW, FL("=======> eSIR_SHARED_KEY  ...\n"));)
#ifdef WLAN_SOFTAP_FEATURE
                        if(psessionEntry->limSystemRole == eLIM_AP_ROLE)
                        {
                            val = psessionEntry->privacy;
                        }
                        else   
#endif
                        if (wlan_cfgGetInt(pMac, WNI_CFG_PRIVACY_ENABLED,
                                      &val) != eSIR_SUCCESS)
                        {
                            /**
                             * Could not get Privacy option
                             * from CFG. Log error.
                             */
                            limLog(pMac, LOGP,
                                   FL("could not retrieve Privacy option\n"));
                        }
                        cfgPrivacyOptImp = (tANI_U8)val;
                        if (!cfgPrivacyOptImp)
                        {
                            /**
                             * Authenticator does not have WEP
                             * implemented.
                             * Reject by sending Authentication frame
                             * with Auth algorithm not supported status
                             * code.
                             */

                            authFrame.authAlgoNumber =
                            pRxAuthFrameBody->authAlgoNumber;
                            authFrame.authTransactionSeqNumber =
                            pRxAuthFrameBody->authTransactionSeqNumber + 1;
                            authFrame.authStatusCode =
                            eSIR_MAC_AUTH_ALGO_NOT_SUPPORTED_STATUS;

                            limSendAuthMgmtFrame(
                                                pMac, &authFrame,
                                                pHdr->sa,
                                                LIM_NO_WEP_IN_FC,psessionEntry);

                            // Log error
                            PELOGE(limLog(pMac, LOGE,
                                   FL("received Auth frame for unsupported auth algorithm %d "
                                   MAC_ADDRESS_STR), pRxAuthFrameBody->authAlgoNumber, 
                                   MAC_ADDR_ARRAY(pHdr->sa));)

                            return;
                        }
                        else
                        {
                            // Create entry for this STA
                            //in pre-auth list
                            pAuthNode = limAcquireFreePreAuthNode(pMac, &pMac->lim.gLimPreAuthTimerTable);
                            if (pAuthNode == NULL)
                            {
                                // Log error
                                limLog(pMac, LOGW,
                                       FL("Max pre-auth nodes reached "));
                                limPrintMacAddr(pMac, pHdr->sa, LOGW);

                                return;
                            }

                            palCopyMemory( pMac->hHdd,
                                         (tANI_U8 *) pAuthNode->peerMacAddr,
                                         pHdr->sa,
                                         sizeof(tSirMacAddr));

                            pAuthNode->mlmState =
                            eLIM_MLM_WT_AUTH_FRAME3_STATE;
                            pAuthNode->authType =
                            (tAniAuthType)
                            pRxAuthFrameBody->authAlgoNumber;
                            pAuthNode->fSeen = 0;
                            pAuthNode->fTimerStarted = 0;
                            limAddPreAuthNode(pMac, pAuthNode);

                            PELOG1(limLog(pMac, LOG1, FL("Alloc new data: %x id %d peer \n"),
                                          pAuthNode, pAuthNode->authNodeIdx);)
                            PELOG1(limPrintMacAddr(pMac, pHdr->sa, LOG1);)

                            /// Create and activate Auth Response timer
                            if (tx_timer_change_context(&pAuthNode->timer, pAuthNode->authNodeIdx) != TX_SUCCESS)
                            {
                                /// Could not start Auth response timer.
                                // Log error
                                limLog(pMac, LOGP,
                                   FL("Unable to chg context auth response timer for peer "));
                                limPrintMacAddr(pMac, pHdr->sa, LOGP);

                                /**
                                 * Send Authenticaton frame with
                                 * unspecified failure status code.
                                 */

                                authFrame.authAlgoNumber =
                                        pRxAuthFrameBody->authAlgoNumber;
                                authFrame.authTransactionSeqNumber =
                                        pRxAuthFrameBody->authTransactionSeqNumber + 1;
                                authFrame.authStatusCode =
                                        eSIR_MAC_UNSPEC_FAILURE_STATUS;

                                limSendAuthMgmtFrame(pMac, &authFrame,
                                                     pHdr->sa,
                                                     LIM_NO_WEP_IN_FC,psessionEntry);

                                limDeletePreAuthNode(pMac, pHdr->sa);
                                return;
                            }

                            limActivateAuthRspTimer(pMac, pAuthNode);

                            pAuthNode->fTimerStarted = 1;

                            // get random bytes and use as
                            // challenge text
                            // TODO
                            //if( !VOS_IS_STATUS_SUCCESS( vos_rand_get_bytes( 0, (tANI_U8 *)challengeTextArray, SIR_MAC_AUTH_CHALLENGE_LENGTH ) ) )
                            {
                               limLog(pMac, LOGE,FL("Challenge text preparation failed in limProcessAuthFrame"));
                            }
                            
                            pChallenge = pAuthNode->challengeText;

                            palCopyMemory( pMac->hHdd,
                                           pChallenge,
                                          (tANI_U8 *) challengeTextArray,
                                          sizeof(challengeTextArray));

                            /**
                             * Sending Authenticaton frame with challenge.
                             */

                            authFrame.authAlgoNumber =
                            pRxAuthFrameBody->authAlgoNumber;
                            authFrame.authTransactionSeqNumber =
                            pRxAuthFrameBody->authTransactionSeqNumber + 1;
                            authFrame.authStatusCode =
                            eSIR_MAC_SUCCESS_STATUS;
                            authFrame.type   = SIR_MAC_CHALLENGE_TEXT_EID;
                            authFrame.length = SIR_MAC_AUTH_CHALLENGE_LENGTH;
                            palCopyMemory( pMac->hHdd,
                                         authFrame.challengeText,
                                         pAuthNode->challengeText,
                                         SIR_MAC_AUTH_CHALLENGE_LENGTH);

                            limSendAuthMgmtFrame(
                                                pMac, &authFrame,
                                                pHdr->sa,
                                                LIM_NO_WEP_IN_FC,psessionEntry);
                        } // if (wlan_cfgGetInt(CFG_PRIVACY_OPTION_IMPLEMENTED))

                        break;

                    default:
                        /**
                         * Responding party does not support the
                         * authentication algorithm requested by
                         * sending party.
                         * Reject by sending Authentication frame
                         * with auth algorithm not supported status code
                         */

                        authFrame.authAlgoNumber =
                        pRxAuthFrameBody->authAlgoNumber;
                        authFrame.authTransactionSeqNumber =
                        pRxAuthFrameBody->authTransactionSeqNumber + 1;
                        authFrame.authStatusCode =
                        eSIR_MAC_AUTH_ALGO_NOT_SUPPORTED_STATUS;

                        limSendAuthMgmtFrame(
                                            pMac, &authFrame,
                                            pHdr->sa,
                                            LIM_NO_WEP_IN_FC,psessionEntry);

                        // Log error
                       PELOGE( limLog(pMac, LOGE,
                               FL("received Auth frame for unsupported auth algorithm %d "
                               MAC_ADDRESS_STR), pRxAuthFrameBody->authAlgoNumber, 
                               MAC_ADDR_ARRAY(pHdr->sa));)

                        return;
                } // end switch(pRxAuthFrameBody->authAlgoNumber)
            } // if (limIsAuthAlgoSupported(pRxAuthFrameBody->authAlgoNumber))
            else
            {
                /**
                 * Responding party does not support the
                 * authentication algorithm requested by sending party.
                 * Reject Authentication with StatusCode=13.
                 */
                authFrame.authAlgoNumber =
                pRxAuthFrameBody->authAlgoNumber;
                authFrame.authTransactionSeqNumber =
                pRxAuthFrameBody->authTransactionSeqNumber + 1;
                authFrame.authStatusCode =
                eSIR_MAC_AUTH_ALGO_NOT_SUPPORTED_STATUS;

                limSendAuthMgmtFrame(pMac, &authFrame,
                                     pHdr->sa,
                                     LIM_NO_WEP_IN_FC,psessionEntry);

                // Log error
                PELOGE(limLog(pMac, LOGE,
                       FL("received Authentication frame for unsupported auth algorithm %d "
                       MAC_ADDRESS_STR), pRxAuthFrameBody->authAlgoNumber, 
                       MAC_ADDR_ARRAY(pHdr->sa));)
                return;
            }
