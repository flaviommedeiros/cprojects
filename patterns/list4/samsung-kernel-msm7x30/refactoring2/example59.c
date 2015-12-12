#ifdef CONFIG_HAS_EARLYSUSPEND
if (VOS_STA_SAP_MODE != hdd_get_conparam())
#endif
   {
      wlan_hdd_cfg80211_post_voss_start(pP2pAdapter);
   }
