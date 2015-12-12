#ifdef FEATURE_WLAN_LFR
if (csrRoamIsFastRoamEnabled(pMac))
        {
            // If "Legacy Fast Roaming" is enabled ALWAYS rebuild the RSN IE from 
            // scratch. So it contains the current PMK-IDs
            cbRsnIe = csrConstructRSNIe(pMac, sessionId, pProfile, pSirBssDesc, pIes, pRsnIe);
        }
        else 
#endif
        if(pProfile->nRSNReqIELength && pProfile->pRSNReqIE)
        {
            // If you have one started away, re-use it. 
            if(SIR_MAC_WPA_IE_MAX_LENGTH >= pProfile->nRSNReqIELength)
            {
                cbRsnIe = (tANI_U8)pProfile->nRSNReqIELength;
                palCopyMemory(pMac->hHdd, pRsnIe, pProfile->pRSNReqIE, cbRsnIe);
            }
            else
            {
                smsLog(pMac, LOGW, "  csrRetrieveRsnIe detect invalid RSN IE length (%d) \n", pProfile->nRSNReqIELength);
            }
        }
        else
        {
            cbRsnIe = csrConstructRSNIe(pMac, sessionId, pProfile, pSirBssDesc, pIes, pRsnIe);
        }
