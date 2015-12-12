#ifdef FEATURE_WLAN_INTEGRATED_SOC
if(txMetaInfo->ucBcast)
#else
   if(WLANTL_STA_ID_BCAST == STAid)
#endif /* FEATURE_WLAN_INTEGRATED_SOC */
   {
      TLLOG1(VOS_TRACE(VOS_MODULE_ID_TL, VOS_TRACE_LEVEL_INFO,"This TX is BC frame"));
      statistics->txBCFcnt++;
#ifdef FEATURE_WLAN_INTEGRATED_SOC
      statistics->txBCBcnt += packetSize;
#else
      statistics->txBCBcnt += (packetSize - WLANHAL_TX_BD_HEADER_SIZE);
#endif /* FEATURE_WLAN_INTEGRATED_SOC */
   }
   else if(txMetaInfo->ucMcast)
   {
      TLLOG1(VOS_TRACE(VOS_MODULE_ID_TL, VOS_TRACE_LEVEL_INFO,"This TX is MC frame"));
      statistics->txMCFcnt++;
#ifdef FEATURE_WLAN_INTEGRATED_SOC
      statistics->txMCBcnt += packetSize;
#else
      statistics->txMCBcnt += (packetSize - WLANHAL_RX_BD_HEADER_SIZE);
#endif /* FEATURE_WLAN_INTEGRATED_SOC */
   }
   else
   {
      TLLOG1(VOS_TRACE(VOS_MODULE_ID_TL, VOS_TRACE_LEVEL_INFO,"This is TX UC frame"));
      statistics->txUCFcnt++;
#ifdef FEATURE_WLAN_INTEGRATED_SOC
      statistics->txUCBcnt += packetSize;
#else
      statistics->txUCBcnt += (packetSize - WLANHAL_RX_BD_HEADER_SIZE);
#endif /* FEATURE_WLAN_INTEGRATED_SOC */
   }
