if ((pSetContextReq->keyMaterial.edType != eSIR_ED_WEP40) &&
        (pSetContextReq->keyMaterial.edType != eSIR_ED_WEP104) &&
        (pSetContextReq->keyMaterial.edType != eSIR_ED_NONE) &&
#ifdef FEATURE_WLAN_WAPI
        (pSetContextReq->keyMaterial.edType != eSIR_ED_WPI) && 
#endif
        !pSetContextReq->keyMaterial.numKeys)
    {
        /**
         * No keys present in case of TKIP or CCMP
         * Log error.
         */
        limLog(pMac, LOGW,
           FL("No keys present in SME_SETCONTEXT_REQ for edType=%d\n"),
           pSetContextReq->keyMaterial.edType);

        valid = false;
        goto end;
    }
