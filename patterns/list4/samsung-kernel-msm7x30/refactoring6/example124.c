if (((pSetContextReq->keyMaterial.edType == eSIR_ED_WEP40) &&
             (pKey->keyLength != 5)) ||
            ((pSetContextReq->keyMaterial.edType == eSIR_ED_WEP104) &&
             (pKey->keyLength != 13)) ||
            ((pSetContextReq->keyMaterial.edType == eSIR_ED_TKIP) &&
             (pKey->keyLength != 32)) ||
#ifdef FEATURE_WLAN_WAPI 
            ((pSetContextReq->keyMaterial.edType == eSIR_ED_WPI) &&
             (pKey->keyLength != 32)) ||
#endif 
            ((pSetContextReq->keyMaterial.edType == eSIR_ED_CCMP) &&
             (pKey->keyLength != 16)))
        {
            /**
             * Invalid key length for a given ED type
             * Log error.
             */
            limLog(pMac, LOGW,
               FL("Invalid keyLength =%d for edType=%d in SME_SETCONTEXT_REQ\n"),
               pKey->keyLength, pSetContextReq->keyMaterial.edType);

            valid = false;
            goto end;
        }
