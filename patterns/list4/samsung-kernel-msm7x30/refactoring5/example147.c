#ifdef WLAN_SOFTAP_FEATURE
if (subType == LIM_ASSOC || subType == LIM_REASSOC)
#else
    if (subType == LIM_ASSOC )
#endif
    {
        temp  = sizeof(tLimMlmAssocInd);
#if (WNI_POLARIS_FW_PACKAGE == ADVANCED) && defined(ANI_PRODUCT_TYPE_AP)        
        temp += pAssocReq->propIEinfo.numBss * sizeof(tSirNeighborBssInfo);
#endif        

        if( eHAL_STATUS_SUCCESS != palAllocateMemory( pMac->hHdd, (void **)&pMlmAssocInd, temp))
        {
            limReleaseAID(pMac, pStaDs->assocId);
            limLog(pMac, LOGP, FL("palAllocateMemory failed for pMlmAssocInd\n"));
            return;
        }
        palZeroMemory( pMac->hHdd, pMlmAssocInd, temp);

        palCopyMemory( pMac->hHdd,(tANI_U8 *)pMlmAssocInd->peerMacAddr,(tANI_U8 *)pStaDs->staAddr,sizeof(tSirMacAddr));
 
        pMlmAssocInd->aid    = pStaDs->assocId;
        palCopyMemory( pMac->hHdd, (tANI_U8 *)&pMlmAssocInd->ssId,(tANI_U8 *)&(pAssocReq->ssId), pAssocReq->ssId.length + 1);
        pMlmAssocInd->sessionId = psessionEntry->peSessionId;
        pMlmAssocInd->authType =  pStaDs->mlmStaContext.authType;
 
#if (WNI_POLARIS_FW_PACKAGE == ADVANCED) && defined(ANI_PRODUCT_TYPE_AP)
        // Note for BTAMP: no need to fill in pMlmAssocInd->seqNum
        pMlmAssocInd->wniIndicator = (tAniBool) pAssocReq->propIEinfo.aniIndicator;
        pMlmAssocInd->bpIndicator  = (tAniBool) pAssocReq->propIEinfo.bpIndicator;
        pMlmAssocInd->bpType       = (tSirBpIndicatorType) pAssocReq->propIEinfo.bpType;
        if (pAssocReq->extendedRatesPresent)
        {
            pMlmAssocInd->nwType = eSIR_11G_NW_TYPE;
            limSetStaHashErpMode(pMac, pStaDs->assocId, eHAL_SET);
        }
        else
        {
            if (phyMode == WNI_CFG_PHY_MODE_11A)
                pMlmAssocInd->nwType = eSIR_11A_NW_TYPE;
            else
            {
                pMlmAssocInd->nwType = eSIR_11B_NW_TYPE;
                limSetStaHashErpMode(pMac, pStaDs->assocId, eHAL_CLEAR);
            }
        }
        pMlmAssocInd->assocType = (tSirAssocType)pAssocReq->propIEinfo.assocType;
        pMlmAssocInd->load.numStas = pMac->lim.gLimNumOfCurrentSTAs;
        pMlmAssocInd->load.channelUtilization =(pMac->lim.gpLimMeasData) ? pMac->lim.gpLimMeasData->avgChannelUtilization : 0;
        pMlmAssocInd->numBss = (tANI_U32) pAssocReq->propIEinfo.numBss;
        if (pAssocReq->propIEinfo.numBss)
        {
            palCopyMemory( pMac->hHdd,(tANI_U8 *) pMlmAssocInd->neighborList,(tANI_U8 *)pAssocReq->propIEinfo.pBssList,
                           (sizeof(tSirNeighborBssInfo) * pAssocReq->propIEinfo.numBss));
        } 
#endif
        pMlmAssocInd->capabilityInfo = pAssocReq->capabilityInfo;

        // Fill in RSN IE information
        pMlmAssocInd->rsnIE.length = 0;
#ifdef WLAN_SOFTAP_FEATURE
        // if WPS IE is present, ignore RSN IE
        if (pAssocReq->addIEPresent && pAssocReq->addIE.length ) {
            wpsIe = limGetWscIEPtr(pMac, pAssocReq->addIE.addIEdata, pAssocReq->addIE.length);
        }
        if (pAssocReq->rsnPresent && (NULL == wpsIe))
#else
        if (pAssocReq->rsnPresent)
#endif
        {
            limLog(pMac, LOG2, FL("Assoc Req RSN IE len = %d\n"), pAssocReq->rsn.length);
            pMlmAssocInd->rsnIE.length = 2 + pAssocReq->rsn.length;
            pMlmAssocInd->rsnIE.rsnIEdata[0] = SIR_MAC_RSN_EID;
            pMlmAssocInd->rsnIE.rsnIEdata[1] = pAssocReq->rsn.length;
            palCopyMemory( pMac->hHdd, 
                           &pMlmAssocInd->rsnIE.rsnIEdata[2],
                           pAssocReq->rsn.info,
                           pAssocReq->rsn.length);
        }

        // Fill in 802.11h related info
        if (pAssocReq->powerCapabilityPresent && pAssocReq->supportedChannelsPresent)
        {
            pMlmAssocInd->spectrumMgtIndicator = eSIR_TRUE;
            pMlmAssocInd->powerCap.minTxPower = pAssocReq->powerCapability.minTxPower;
            pMlmAssocInd->powerCap.maxTxPower = pAssocReq->powerCapability.maxTxPower;
            limConvertSupportedChannels(pMac, pMlmAssocInd, pAssocReq);
        }
        else
            pMlmAssocInd->spectrumMgtIndicator = eSIR_FALSE;


#ifdef WLAN_SOFTAP_FEATURE
        /* This check is to avoid extra Sec IEs present incase of WPS */
        if (pAssocReq->wpaPresent && (NULL == wpsIe))
#else
        if ((pAssocReq->wpaPresent) && (pMlmAssocInd->rsnIE.length < SIR_MAC_MAX_IE_LENGTH))
#endif
        {
            if((pMlmAssocInd->rsnIE.length + pAssocReq->wpa.length) >= SIR_MAC_MAX_IE_LENGTH)
            {
                PELOGE(limLog(pMac, LOGE, FL("rsnIEdata index out of bounds %d\n"), pMlmAssocInd->rsnIE.length);)
                return;
            }
            pMlmAssocInd->rsnIE.rsnIEdata[pMlmAssocInd->rsnIE.length] = SIR_MAC_WPA_EID;
            pMlmAssocInd->rsnIE.rsnIEdata[pMlmAssocInd->rsnIE.length + 1] = pAssocReq->wpa.length;
            palCopyMemory( pMac->hHdd,
                           &pMlmAssocInd->rsnIE.rsnIEdata[pMlmAssocInd->rsnIE.length + 2],
                           pAssocReq->wpa.info,
                           pAssocReq->wpa.length);
            pMlmAssocInd->rsnIE.length += 2 + pAssocReq->wpa.length;
        }


       pMlmAssocInd->addIE.length = 0;
       if (pAssocReq->addIEPresent)
       {
            palCopyMemory( pMac->hHdd,
                           &pMlmAssocInd->addIE.addIEdata,
                           pAssocReq->addIE.addIEdata,
                           pAssocReq->addIE.length);

            pMlmAssocInd->addIE.length = pAssocReq->addIE.length;
       }

#ifdef WLAN_SOFTAP_FEATURE
        if(pAssocReq->wmeInfoPresent)
        {

            if (wlan_cfgGetInt(pMac, (tANI_U16) WNI_CFG_WME_ENABLED, &tmp) != eSIR_SUCCESS)
                 limLog(pMac, LOGP, FL("wlan_cfgGetInt failed for id %d\n"), WNI_CFG_WME_ENABLED );

            /* check whether AP is enabled with WMM */
            if(tmp)
            {
                pMlmAssocInd->WmmStaInfoPresent = 1;
            }
            else
            {
                pMlmAssocInd->WmmStaInfoPresent= 0;
            }
            /* Note: we are not rejecting association here because IOT will fail */

        }
#endif

        // Required for indicating the frames to upper layer
        pMlmAssocInd->assocReqLength = pAssocReq->assocReqFrameLength;
        pMlmAssocInd->assocReqPtr = pAssocReq->assocReqFrame;
        
        pMlmAssocInd->beaconPtr = psessionEntry->beacon;
        pMlmAssocInd->beaconLength = psessionEntry->bcnLen;

        limPostSmeMessage(pMac, LIM_MLM_ASSOC_IND, (tANI_U32 *) pMlmAssocInd);
        palFreeMemory( pMac->hHdd, pMlmAssocInd);
    }
    else
    {
        // If its of Reassociation Request, then post LIM_MLM_REASSOC_IND 
        temp  = sizeof(tLimMlmReassocInd);

#if (WNI_POLARIS_FW_PACKAGE == ADVANCED)
        temp += pAssocReq->propIEinfo.numBss * sizeof(tSirNeighborBssInfo);
#endif
        if( eHAL_STATUS_SUCCESS != palAllocateMemory( pMac->hHdd, (void **)&pMlmReassocInd, temp))
        {
            limLog(pMac, LOGP, FL("call to palAllocateMemory failed for pMlmReassocInd\n"));
            limReleaseAID(pMac, pStaDs->assocId);
            return;
        }
        palZeroMemory( pMac->hHdd, pMlmReassocInd, temp);

        palCopyMemory( pMac->hHdd,(tANI_U8 *) pMlmReassocInd->peerMacAddr, (tANI_U8 *)pStaDs->staAddr, sizeof(tSirMacAddr));
        palCopyMemory( pMac->hHdd,(tANI_U8 *) pMlmReassocInd->currentApAddr, (tANI_U8 *)&(pAssocReq->currentApAddr), sizeof(tSirMacAddr));
        pMlmReassocInd->aid = pStaDs->assocId;
        pMlmReassocInd->authType = pStaDs->mlmStaContext.authType;
        palCopyMemory( pMac->hHdd,(tANI_U8 *)&pMlmReassocInd->ssId, (tANI_U8 *)&(pAssocReq->ssId), pAssocReq->ssId.length + 1);

#if (WNI_POLARIS_FW_PACKAGE == ADVANCED) && defined(ANI_PRODUCT_TYPE_AP)
        // Note for BTAMP: no need to fill in pMlmAssocInd->seqNum
        pMlmReassocInd->wniIndicator = (tAniBool) pAssocReq->propIEinfo.aniIndicator;
        pMlmReassocInd->bpIndicator  = (tAniBool) pAssocReq->propIEinfo.bpIndicator;
        pMlmReassocInd->bpType       = (tSirBpIndicatorType) pAssocReq->propIEinfo.bpType;
        if (pAssocReq->extendedRatesPresent)
        {
            pMlmReassocInd->nwType = eSIR_11G_NW_TYPE;
            limSetStaHashErpMode(pMac, pStaDs->assocId, eHAL_SET);
        }
        else
        {
            if (phyMode == WNI_CFG_PHY_MODE_11A)
                pMlmReassocInd->nwType = eSIR_11A_NW_TYPE;
            else
            {
                pMlmReassocInd->nwType = eSIR_11B_NW_TYPE;
                limSetStaHashErpMode(pMac, pStaDs->assocId, eHAL_CLEAR);
            }
        }

        pMlmReassocInd->reassocType  = (tSirAssocType)pAssocReq->propIEinfo.assocType;
        pMlmReassocInd->load.numStas = pMac->lim.gLimNumOfCurrentSTAs;
        pMlmReassocInd->load.channelUtilization = (pMac->lim.gpLimMeasData) ?
                                                  pMac->lim.gpLimMeasData->avgChannelUtilization : 0;
        pMlmReassocInd->numBss = (tANI_U32) pAssocReq->propIEinfo.numBss;
        if (pAssocReq->propIEinfo.numBss)
        {
            palCopyMemory( pMac->hHdd, 
                           (tANI_U8 *) pMlmReassocInd->neighborList,
                           (tANI_U8 *) pAssocReq->propIEinfo.pBssList,
                           (sizeof(tSirNeighborBssInfo) * pAssocReq->propIEinfo.numBss));
        }
#endif
        if (pAssocReq->propIEinfo.aniIndicator)
            pStaDs->aniPeer = 1;

        pMlmReassocInd->capabilityInfo = pAssocReq->capabilityInfo;
        pMlmReassocInd->rsnIE.length = 0;

#ifdef WLAN_SOFTAP_FEATURE
        if (pAssocReq->addIEPresent && pAssocReq->addIE.length )
            wpsIe = limGetWscIEPtr(pMac, pAssocReq->addIE.addIEdata, pAssocReq->addIE.length);

        if (pAssocReq->rsnPresent && (NULL == wpsIe))
#else
        if (pAssocReq->rsnPresent)
#endif
        {
            limLog(pMac, LOG2, FL("Assoc Req: RSN IE length = %d\n"), pAssocReq->rsn.length);
            pMlmReassocInd->rsnIE.length = 2 + pAssocReq->rsn.length;
            pMlmReassocInd->rsnIE.rsnIEdata[0] = SIR_MAC_RSN_EID;
            pMlmReassocInd->rsnIE.rsnIEdata[1] = pAssocReq->rsn.length;
            palCopyMemory( pMac->hHdd, &pMlmReassocInd->rsnIE.rsnIEdata[2], pAssocReq->rsn.info, pAssocReq->rsn.length);
        }

        // 802.11h support
        if (pAssocReq->powerCapabilityPresent && pAssocReq->supportedChannelsPresent)
        {
            pMlmReassocInd->spectrumMgtIndicator = eSIR_TRUE;
            pMlmReassocInd->powerCap.minTxPower = pAssocReq->powerCapability.minTxPower;
            pMlmReassocInd->powerCap.maxTxPower = pAssocReq->powerCapability.maxTxPower;
            pMlmReassocInd->supportedChannels.numChnl = (tANI_U8)(pAssocReq->supportedChannels.length / 2);

            limLog(pMac, LOG1,
                FL("Sending Reassoc Ind: spectrum ON, minPwr %d, maxPwr %d, numChnl %d\n"),
                pMlmReassocInd->powerCap.minTxPower,
                pMlmReassocInd->powerCap.maxTxPower,
                pMlmReassocInd->supportedChannels.numChnl);

            for(i=0; i < pMlmReassocInd->supportedChannels.numChnl; i++)
            {
                pMlmReassocInd->supportedChannels.channelList[i] = pAssocReq->supportedChannels.supportedChannels[j];
                limLog(pMac, LOG1, FL("Sending ReassocInd: chn[%d] = %d \n"),
                       i, pMlmReassocInd->supportedChannels.channelList[i]);
                j+=2;
            }
        }
        else
            pMlmReassocInd->spectrumMgtIndicator = eSIR_FALSE;


#ifdef WLAN_SOFTAP_FEATURE
        /* This check is to avoid extra Sec IEs present incase of WPS */
        if (pAssocReq->wpaPresent && (NULL == wpsIe))
#else
        if (pAssocReq->wpaPresent)
#endif
        {
            limLog(pMac, LOG2, FL("Received WPA IE length in Assoc Req is %d\n"), pAssocReq->wpa.length);
            pMlmReassocInd->rsnIE.rsnIEdata[pMlmReassocInd->rsnIE.length] = SIR_MAC_WPA_EID;
            pMlmReassocInd->rsnIE.rsnIEdata[pMlmReassocInd->rsnIE.length + 1] = pAssocReq->wpa.length;
            palCopyMemory( pMac->hHdd,
                           &pMlmReassocInd->rsnIE.rsnIEdata[pMlmReassocInd->rsnIE.length + 2],
                           pAssocReq->wpa.info,
                           pAssocReq->wpa.length);
            pMlmReassocInd->rsnIE.length += 2 + pAssocReq->wpa.length;
        }

       pMlmReassocInd->addIE.length = 0;
       if (pAssocReq->addIEPresent)
       {
            palCopyMemory( pMac->hHdd,
                           &pMlmReassocInd->addIE.addIEdata,
                           pAssocReq->addIE.addIEdata,
                           pAssocReq->addIE.length);

            pMlmReassocInd->addIE.length = pAssocReq->addIE.length;
       }

#ifdef WLAN_SOFTAP_FEATURE
        if(pAssocReq->wmeInfoPresent)
        {

            if (wlan_cfgGetInt(pMac, (tANI_U16) WNI_CFG_WME_ENABLED, &tmp) != eSIR_SUCCESS)
                 limLog(pMac, LOGP, FL("wlan_cfgGetInt failed for id %d\n"), WNI_CFG_WME_ENABLED );

            /* check whether AP is enabled with WMM */
            if(tmp)
            {
                pMlmReassocInd->WmmStaInfoPresent = 1;
            }
            else
            {
                pMlmReassocInd->WmmStaInfoPresent = 0;
            }
            /* Note: we are not rejecting Re-association here because IOT will fail */

        }
#endif

        // Required for indicating the frames to upper layer
        pMlmReassocInd->assocReqLength = pAssocReq->assocReqFrameLength;
        pMlmReassocInd->assocReqPtr = pAssocReq->assocReqFrame;

        pMlmReassocInd->beaconPtr = psessionEntry->beacon;
        pMlmReassocInd->beaconLength = psessionEntry->bcnLen;

        limPostSmeMessage(pMac, LIM_MLM_REASSOC_IND, (tANI_U32 *) pMlmReassocInd);
        palFreeMemory( pMac->hHdd, pMlmReassocInd);
    }
