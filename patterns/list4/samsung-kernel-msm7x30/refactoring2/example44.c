#ifndef WLAN_MDM_CODE_REDUCTION_OPT
if( btcIsReadyForUapsd(pMac) )
#endif /* WLAN_MDM_CODE_REDUCTION_OPT*/
    {
       *pBuf++ = uapsdMask;
    }
#ifndef WLAN_MDM_CODE_REDUCTION_OPT
    else
    {
        smsLog(pMac, LOGE, FL(" BTC doesn't allow UAPSD for uapsd_mask(0x%X)\n"), uapsdMask);
        *pBuf++ = 0;
    }
