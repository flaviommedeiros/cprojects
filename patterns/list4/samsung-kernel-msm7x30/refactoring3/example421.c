switch (psessionEntry->limSystemRole)
        {
            case eLIM_STA_ROLE:
            case eLIM_BT_AMP_STA_ROLE:
                switch (psessionEntry->limMlmState)
                {
                    case eLIM_MLM_WT_AUTH_FRAME2_STATE:
                        /**
                         * AP sent Deauth frame while waiting
                         * for Auth frame2. Report Auth failure
                         * to SME.
                         */

                        // Log error
                        PELOG1(limLog(pMac, LOG1,
                           FL("received Deauth frame with failure code %d from "),
                           reasonCode);
                        limPrintMacAddr(pMac, pHdr->sa, LOG1);)

                        limRestoreFromAuthState(pMac, eSIR_SME_DEAUTH_WHILE_JOIN,
                                                reasonCode,psessionEntry);

                        return;

                    case eLIM_MLM_AUTHENTICATED_STATE:
                        /// Issue Deauth Indication to SME.
                        palCopyMemory( pMac->hHdd,
                               (tANI_U8 *) &mlmDeauthInd.peerMacAddr,
                               pHdr->sa,
                               sizeof(tSirMacAddr));
                        mlmDeauthInd.reasonCode = reasonCode;

                        psessionEntry->limMlmState = eLIM_MLM_IDLE_STATE;
                        MTRACE(macTrace(pMac, TRACE_CODE_MLM_STATE, psessionEntry->peSessionId, psessionEntry->limMlmState));

                        
                        limPostSmeMessage(pMac,
                                          LIM_MLM_DEAUTH_IND,
                                          (tANI_U32 *) &mlmDeauthInd);
                        return;

                    case eLIM_MLM_WT_ASSOC_RSP_STATE:
                        /**
                         * AP may have 'aged-out' our Pre-auth
                         * context. Delete local pre-auth context
                         * if any and issue ASSOC_CNF to SME.
                         */
                        if (limSearchPreAuthList(pMac, pHdr->sa))
                            limDeletePreAuthNode(pMac, pHdr->sa);

                       if (psessionEntry->pLimMlmJoinReq)
                        {
                            palFreeMemory( pMac->hHdd, psessionEntry->pLimMlmJoinReq);
                            psessionEntry->pLimMlmJoinReq = NULL;
                        }

                        mlmAssocCnf.resultCode = eSIR_SME_DEAUTH_WHILE_JOIN;
                        mlmAssocCnf.protStatusCode = reasonCode;
                        
                        /* PE session Id*/
                        mlmAssocCnf.sessionId = psessionEntry->peSessionId;

                        psessionEntry->limMlmState =
                                   psessionEntry->limPrevMlmState;
                        MTRACE(macTrace(pMac, TRACE_CODE_MLM_STATE, psessionEntry->peSessionId, psessionEntry->limMlmState));

                        // Deactive Association response timeout
                        limDeactivateAndChangeTimer(
                                     pMac,
                                     eLIM_ASSOC_FAIL_TIMER);

                        limPostSmeMessage(
                            pMac,
                            LIM_MLM_ASSOC_CNF,
                            (tANI_U32 *) &mlmAssocCnf);
                        
                        return;

                    case eLIM_MLM_IDLE_STATE:
                    case eLIM_MLM_LINK_ESTABLISHED_STATE:
                        /**
                         * This could be Deauthentication frame from
                         * a BSS with which pre-authentication was
                         * performed. Delete Pre-auth entry if found.
                         */
                        if (limSearchPreAuthList(pMac, pHdr->sa))
                           limDeletePreAuthNode(pMac, pHdr->sa);

                        break;

                    case eLIM_MLM_WT_REASSOC_RSP_STATE:
                        break;

                    case eLIM_MLM_WT_FT_REASSOC_RSP_STATE:
                        PELOGE(limLog(pMac, LOGE,
                           FL("received Deauth frame in FT state %X with reasonCode=%d from "),
                           psessionEntry->limMlmState, reasonCode);)
                        limPrintMacAddr(pMac, pHdr->sa, LOGE);
                        break;

                    default:
                        PELOG1(limLog(pMac, LOG1,
                           FL("received Deauth frame in state %X with reasonCode=%d from "),
                           psessionEntry->limMlmState, reasonCode);)
                        limPrintMacAddr(pMac, pHdr->sa, LOG1);
                        return;
                }
                break;

            case eLIM_STA_IN_IBSS_ROLE:
                break;

#ifdef WLAN_SOFTAP_FEATURE
            case eLIM_AP_ROLE:
                break;
#endif 

            default: // eLIM_AP_ROLE or eLIM_BT_AMP_AP_ROLE

#if (WNI_POLARIS_FW_PRODUCT == AP)
                /// Check if there exists pre-auth context for this STA
                if (limSearchPreAuthList(pMac, pHdr->sa) == NULL)
                {
                    /**
                     * Received Deauthentication from a STA that is neither
                     * Associated nor Pre-authenticated. Log error,
                     * and ignore Deauthentication frame.
                     */
                    PELOG1(limLog(pMac, LOG1,
                       FL("received Deauth frame from peer that does not have context, addr "));
                    limPrintMacAddr(pMac, pHdr->sa, LOG1);)
                }
                else
                {
                    /// Delete STA from pre-auth STA list
                    limDeletePreAuthNode(pMac,
                                         pHdr->sa);

                    palCopyMemory( pMac->hHdd,
                           (tANI_U8 *) &mlmDeauthInd.peerMacAddr,
                           pHdr->sa,
                           sizeof(tSirMacAddr));
                    mlmDeauthInd.reasonCode = reasonCode;
                    mlmDeauthInd.aid        = 0;

                    limPostSmeMessage(pMac,
                                      LIM_MLM_DEAUTH_IND,
                                      (tANI_U32 *) &mlmDeauthInd);
                }
#endif

                return;
        }
