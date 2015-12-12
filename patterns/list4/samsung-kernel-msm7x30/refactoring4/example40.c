#ifdef FEATURE_WLAN_WAPI
if ( ( 1 == tlMetaInfo.ucIsWai ) ||
       ( 0 == tlMetaInfo.ucDisableFrmXtl ) )
#else
  /*------------------------------------------------------------------------
    Translate 802.3 frame to 802.11 if Frame translation is enabled 
   ------------------------------------------------------------------------*/
  if ( ( 0 == tlMetaInfo.ucDisableFrmXtl ) &&
      ( 0 != pTLCb->atlSTAClients[ucSTAId].wSTADesc.ucSwFrameTXXlation) )
#endif //#ifdef FEATURE_WLAN_WAPI
  {
    vosStatus =  WLANTL_Translate8023To80211Header( vosDataBuff, &vosStatus,
                                                    pTLCb, ucSTAId,
                                                    tlMetaInfo.ucUP, &ucWDSEnabled, &extraHeadSpace);

    if ( VOS_STATUS_SUCCESS != vosStatus )
    {
      TLLOGE(VOS_TRACE( VOS_MODULE_ID_TL, VOS_TRACE_LEVEL_ERROR,
                "WLAN TL:Error when translating header WLANTL_STATxConn"));

      return vosStatus;
    }

    tlMetaInfo.ucDisableFrmXtl = 1;
  }
