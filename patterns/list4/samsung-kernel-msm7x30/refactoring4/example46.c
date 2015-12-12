#ifdef WLAN_FEATURE_11AC
if (limPopulateMatchingRateSet(pMac,
                               pStaDs,
                               &(pAssocReq->supportedRates),
                               &(pAssocReq->extendedRates),
                               pAssocReq->HTCaps.supportedMCSSet,
                               &(pAssocReq->propIEinfo.propRates),
                               psessionEntry , &pAssocReq->VHTCaps) 
                               != eSIR_SUCCESS)
#else

    if (limPopulateMatchingRateSet(pMac,
                                   pStaDs,
                                   &(pAssocReq->supportedRates),
                                   &(pAssocReq->extendedRates),
                                   pAssocReq->HTCaps.supportedMCSSet,
                                   &(pAssocReq->propIEinfo.propRates), psessionEntry) != eSIR_SUCCESS)
#endif
    {
        // Could not update hash table entry at DPH with rateset
        limLog(pMac, LOGE,
           FL("could not update hash entry at DPH for aid=%d, MacAddr:\n"),
           aid);
        limPrintMacAddr(pMac, pHdr->sa, LOGE);

                // Release AID
        limReleaseAID(pMac, aid);


        limRejectAssociation(pMac, pHdr->sa,
                             subType, true, authType, aid, true,
                             (tSirResultCodes) eSIR_MAC_UNSPEC_FAILURE_STATUS, psessionEntry);

        /*return it from here rather than goto error statement.This is done as the memory is getting free twice*/
        return;
        //goto error;
    }
