#if (WNI_POLARIS_FW_PACKAGE == ADVANCED) && (WNI_POLARIS_FW_PRODUCT == AP)
if (!limIsBssInfoValidInSmeReqMessage(
                     pMac,
                     pJoinReq->neighborBssList.bssList))
#else
    if (!limIsBssDescrValidInSmeReqMessage(pMac,
                                           &pJoinReq->bssDescription))
#endif
    {
        /// Received eWNI_SME_JOIN_REQ with invalid BSS Info
        // Log the event
        limLog(pMac, LOGE,
               FL("received SME_JOIN_REQ with invalid bssInfo\n"));

        valid = false;
        goto end;
    }
