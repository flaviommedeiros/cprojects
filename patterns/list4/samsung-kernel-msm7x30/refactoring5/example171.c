#ifdef WLAN_FEATURE_P2P
if( pMac->lim.gpLimRemainOnChanReq )
    {
        nBytes += (pMac->lim.gpLimRemainOnChanReq->length - sizeof( tSirRemainOnChnReq ) );
    }
    //Only use CFG for non-listen mode. This CFG is not working for concurrency
    //In listening mode, probe rsp IEs is passed in the message from SME to PE
    else
#endif
    {

        if (wlan_cfgGetInt(pMac, WNI_CFG_PROBE_RSP_ADDNIE_FLAG,
                           &addnIEPresent) != eSIR_SUCCESS)
        {
            limLog(pMac, LOGP, FL("Unable to get WNI_CFG_PROBE_RSP_ADDNIE_FLAG"));
            palFreeMemory(pMac->hHdd, pFrm);
            return;
        }
    }
