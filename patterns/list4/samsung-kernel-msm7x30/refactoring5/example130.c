#ifdef WLAN_SOFTAP_FEATURE
if( WLAN_STA_SOFTAP == pTLCb->atlSTAClients[ucSTAId].wSTADesc.wSTAType)
    {
      WLANTL_FwdPktToHDD( pvosGCtx, vosDataBuff, ucSTAId );
    }
    else
#endif
    {
      wRxMetaInfo.ucUP = ucTid;
      pTLCb->atlSTAClients[ucSTAId].pfnSTARx( pvosGCtx, vosDataBuff, ucSTAId,
                                            &wRxMetaInfo );
    }
