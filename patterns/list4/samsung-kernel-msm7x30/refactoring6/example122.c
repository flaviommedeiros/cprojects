if ((pRSNie->rsnIEdata[wpaIndex] == SIR_MAC_WPA_EID) &&
#if 0 // Comparison always false
            (pRSNie->rsnIEdata[wpaIndex + 1] > SIR_MAC_WPA_IE_MAX_LENGTH) ||
#endif
             ((pRSNie->rsnIEdata[wpaIndex + 1] < SIR_MAC_WPA_IE_MIN_LENGTH) ||
             (SIR_MAC_WPA_OUI != val)))
        {
            limLog(pMac, LOGE,
               FL("WPA IE len %d not [%d,%d] OR data 0x%x not 0x%x\n"),
               pRSNie->rsnIEdata[1], SIR_MAC_RSN_IE_MIN_LENGTH, 
               SIR_MAC_RSN_IE_MAX_LENGTH, val, SIR_MAC_WPA_OUI);

            return false;
        }
        else
        {
            /* Both RSN and WPA IEs are present */
            dot11fUnpackIeRSN(pMac,&pRSNie->rsnIEdata[2],
                  (tANI_U8)pRSNie->length,&pSessionEntry->gStartBssRSNIe);

            dot11fUnpackIeWPA(pMac,&pRSNie->rsnIEdata[wpaIndex + 6],
                              pRSNie->rsnIEdata[wpaIndex + 1]-4,
                                &pSessionEntry->gStartBssWPAIe);

        }
