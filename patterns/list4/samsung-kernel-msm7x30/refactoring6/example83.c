if ( (WLAN_HDD_SOFTAP == pAdapter->device_mode )
                 || (WLAN_HDD_MONITOR == pAdapter->device_mode )
#ifdef WLAN_FEATURE_P2P
                 || (WLAN_HDD_P2P_GO == pAdapter->device_mode )
#endif
      )
   {
      /* SoftAP mode, so return from here */
      EXIT();
      return 0;
   }
