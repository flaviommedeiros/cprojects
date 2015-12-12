#ifdef WLAN_SOFTAP_FEATURE
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
