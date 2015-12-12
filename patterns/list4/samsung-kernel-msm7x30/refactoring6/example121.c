if ((pRSNie->rsnIEdata[0] == SIR_MAC_RSN_EID) &&
#if 0 // Comparison always false
            (pRSNie->rsnIEdata[1] > SIR_MAC_RSN_IE_MAX_LENGTH) ||
#endif
             (pRSNie->rsnIEdata[1] < SIR_MAC_RSN_IE_MIN_LENGTH))
        {
            limLog(pMac, LOGE, FL("RSN IE len %d not [%d,%d]\n"), 
                   pRSNie->rsnIEdata[1], SIR_MAC_RSN_IE_MIN_LENGTH, 
                   SIR_MAC_RSN_IE_MAX_LENGTH);
            return false;
        }
