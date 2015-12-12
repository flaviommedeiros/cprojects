if (((((psessionEntry->limSystemRole== eLIM_STA_ROLE) || (psessionEntry->limSystemRole == eLIM_BT_AMP_STA_ROLE)) &&
          ((psessionEntry->limMlmState == eLIM_MLM_JOINED_STATE) ||
           (psessionEntry->limMlmState ==
                                  eLIM_MLM_LINK_ESTABLISHED_STATE))) ||
         ((psessionEntry->limSystemRole == eLIM_STA_IN_IBSS_ROLE) &&
          (psessionEntry->limMlmState == eLIM_MLM_BSS_STARTED_STATE))) &&
        (limIsGroupAddr(pMac->lim.gpLimMlmAuthReq->peerMacAddr)
                                                   == false) &&
#ifdef WLAN_SOFTAP_FEATURE
        (limIsAuthAlgoSupported(
                        pMac,
                        pMac->lim.gpLimMlmAuthReq->authType,
                        psessionEntry) == true)
#else
        (limIsAuthAlgoSupported(
                        pMac,
                        pMac->lim.gpLimMlmAuthReq->authType) == true)
#endif
        )        
    {
        /**
         * This is a request for pre-authentication.
         * Check if there exists context already for
         * the requsted peer OR
         * if this request is for the AP we're currently
         * associated with.
         * If yes, return auth confirm immediately when
         * requested auth type is same as the one used before.
         */
        if ((((psessionEntry->limSystemRole == eLIM_STA_ROLE) ||(psessionEntry->limSystemRole == eLIM_BT_AMP_STA_ROLE) )&&
             (psessionEntry->limMlmState ==
                                  eLIM_MLM_LINK_ESTABLISHED_STATE) &&
             (((pStaDs = dphGetHashEntry(pMac, DPH_STA_HASH_INDEX_PEER, &psessionEntry->dph.dphHashTable)) != NULL) &&
              (pMac->lim.gpLimMlmAuthReq->authType ==
                                   pStaDs->mlmStaContext.authType)) &&
             (palEqualMemory( pMac->hHdd,pMac->lim.gpLimMlmAuthReq->peerMacAddr,
                        currentBssId,
                        sizeof(tSirMacAddr)) )) ||
            (((preAuthNode =
               limSearchPreAuthList(
                     pMac,
                     pMac->lim.gpLimMlmAuthReq->peerMacAddr)) != NULL) &&
             (preAuthNode->authType ==
                                   pMac->lim.gpLimMlmAuthReq->authType)))
        {
           PELOG2(limLog(pMac, LOG2,
                   FL("Already have pre-auth context with peer\n"));
            limPrintMacAddr(pMac, pMac->lim.gpLimMlmAuthReq->peerMacAddr,
                            LOG2);)

            mlmAuthCnf.resultCode = (tSirResultCodes)
                                    eSIR_MAC_SUCCESS_STATUS;
            

            goto end;
        }
        else
        {
            if (wlan_cfgGetInt(pMac, WNI_CFG_MAX_NUM_PRE_AUTH,
                          (tANI_U32 *) &numPreAuthContexts) != eSIR_SUCCESS)
            {
                limLog(pMac, LOGP,
                   FL("Could not retrieve NumPreAuthLimit from CFG\n"));
            }
#ifdef ANI_AP_SDK_OPT
            if(numPreAuthContexts > SIR_SDK_OPT_MAX_NUM_PRE_AUTH)
                numPreAuthContexts = SIR_SDK_OPT_MAX_NUM_PRE_AUTH;
#endif // ANI_AP_SDK_OPT

            if (pMac->lim.gLimNumPreAuthContexts == numPreAuthContexts)
            {
                PELOGW(limLog(pMac, LOGW,
                       FL("Number of pre-auth reached max limit\n"));)

                /// Return Auth confirm with reject code
                mlmAuthCnf.resultCode =
                               eSIR_SME_MAX_NUM_OF_PRE_AUTH_REACHED;

                goto end;
            }
        }

        // Delete pre-auth node if exists
        if (preAuthNode)
            limDeletePreAuthNode(pMac,
                                 pMac->lim.gpLimMlmAuthReq->peerMacAddr);

        psessionEntry->limPrevMlmState = psessionEntry->limMlmState;
        psessionEntry->limMlmState = eLIM_MLM_WT_AUTH_FRAME2_STATE;
        MTRACE(macTrace(pMac, TRACE_CODE_MLM_STATE, psessionEntry->peSessionId, psessionEntry->limMlmState));

        /// Prepare & send Authentication frame
        authFrameBody.authAlgoNumber =
                                  (tANI_U8) pMac->lim.gpLimMlmAuthReq->authType;
        authFrameBody.authTransactionSeqNumber = SIR_MAC_AUTH_FRAME_1;
        authFrameBody.authStatusCode = 0;
        limSendAuthMgmtFrame(pMac,
                             &authFrameBody,
                             pMac->lim.gpLimMlmAuthReq->peerMacAddr,
                             LIM_NO_WEP_IN_FC,psessionEntry);

        //assign appropriate sessionId to the timer object
        pMac->lim.limTimers.gLimAuthFailureTimer.sessionId = sessionId;
 
        // Activate Auth failure timer
        MTRACE(macTrace(pMac, TRACE_CODE_TIMER_ACTIVATE, psessionEntry->peSessionId, eLIM_AUTH_FAIL_TIMER));
        if (tx_timer_activate(&pMac->lim.limTimers.gLimAuthFailureTimer)
                                       != TX_SUCCESS)
        {
            /// Could not start Auth failure timer.
            // Log error
            limLog(pMac, LOGP,
                   FL("could not start Auth failure timer\n"));
            // Cleanup as if auth timer expired
            limProcessAuthFailureTimeout(pMac);
        }

        return;
    }
    else
    {
        /**
         * Unexpected auth request.
         * Return Auth confirm with Invalid parameters code.
         */
        mlmAuthCnf.resultCode = eSIR_SME_INVALID_PARAMETERS;

        goto end;
    }
