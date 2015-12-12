#ifdef ANI_MANF_DIAG
if (VOS_FTM_MODE != hdd_get_conparam())
#endif /* ANI_MANF_DIAG */
      {
         pAdapter = hdd_get_adapter(pHddCtx,
                                    WLAN_HDD_INFRA_STATION);
      }
