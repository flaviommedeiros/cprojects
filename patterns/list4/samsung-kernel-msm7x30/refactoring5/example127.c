#ifdef WLAN_SOFTAP_FEATURE
if( WLAN_STA_SOFTAP == pTLHandle->atlSTAClients[ucSTAID].wSTADesc.wSTAType)
   {
      WLANTL_FwdPktToHDD( expireHandle->pAdapter, vosDataBuff, ucSTAID);
   }
   else
#endif
   {
      wRxMetaInfo.ucUP = ucTID;
      pTLHandle->atlSTAClients[ucSTAID].pfnSTARx(expireHandle->pAdapter,
                                           vosDataBuff, ucSTAID, &wRxMetaInfo);
   }
