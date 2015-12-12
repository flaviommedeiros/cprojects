#ifdef FEATURE_WLAN_WAPI
if ( WLANTL_STA_AUTHENTICATED == pTLCb->atlSTAClients[ucStaId].tlState && gUcIsWai != 1 )
#else
  if ( WLANTL_STA_AUTHENTICATED == pTLCb->atlSTAClients[ucStaId].tlState )
#endif
  {
    pw80211Header->wFrmCtrl.wep =
                 pTLCb->atlSTAClients[ucStaId].wSTADesc.ucProtectedFrame;
  }
