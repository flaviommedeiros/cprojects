#ifdef ANI_BUS_TYPE_SDIO
if (VOS_STA_SAP_MODE != hdd_get_conparam())
#endif
   {
#ifdef ANI_MANF_DIAG
      if (VOS_FTM_MODE != hdd_get_conparam())
#endif /* ANI_MANF_DIAG */
      {
         hdd_adapter_t* pAdapter = hdd_get_adapter(pHddCtx,
                                      WLAN_HDD_INFRA_STATION);
         if (pAdapter == NULL)
            pAdapter = hdd_get_adapter(pHddCtx, WLAN_HDD_P2P_CLIENT);

         if (pAdapter != NULL)
         {
            wlan_hdd_cfg80211_pre_voss_stop(pAdapter);
            hdd_UnregisterWext(pAdapter->dev);
         }
      }
   }
