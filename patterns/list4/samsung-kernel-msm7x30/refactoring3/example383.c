switch(session_type)
   {
      case WLAN_HDD_INFRA_STATION:
#ifdef WLAN_FEATURE_P2P
      case WLAN_HDD_P2P_CLIENT:
      case WLAN_HDD_P2P_DEVICE:
#endif
      {
         pAdapter = hdd_alloc_station_adapter( pHddCtx, macAddr, iface_name );

         if( NULL == pAdapter )
            return NULL;

#ifdef CONFIG_CFG80211
         pAdapter->wdev.iftype = (session_type == WLAN_HDD_P2P_CLIENT) ?
                                  NL80211_IFTYPE_P2P_CLIENT:
                                  NL80211_IFTYPE_STATION;
#endif

         pAdapter->device_mode = session_type;

         status = hdd_init_station_mode( pAdapter );
         if( VOS_STATUS_SUCCESS != status )
            goto err_free_netdev;

         status = hdd_register_interface( pAdapter, rtnl_held );
         if( VOS_STATUS_SUCCESS != status )
         {
            hdd_deinit_adapter(pHddCtx, pAdapter);
            goto err_free_netdev;
         }
         //Stop the Interface TX queue.
         netif_tx_disable(pAdapter->dev);
         //netif_tx_disable(pWlanDev);
         netif_carrier_off(pAdapter->dev);

         break;
      }

#ifdef WLAN_FEATURE_P2P
      case WLAN_HDD_P2P_GO:
#endif
      case WLAN_HDD_SOFTAP:
      {
         pAdapter = hdd_wlan_create_ap_dev( pHddCtx, macAddr, (tANI_U8 *)iface_name );
         if( NULL == pAdapter )
            return NULL;

#ifdef CONFIG_CFG80211
         pAdapter->wdev.iftype = (session_type == WLAN_HDD_SOFTAP) ?
                                  NL80211_IFTYPE_AP:
                                  NL80211_IFTYPE_P2P_GO;
#endif
         pAdapter->device_mode = session_type;

         status = hdd_init_ap_mode(pAdapter);
         if( VOS_STATUS_SUCCESS != status )
            goto err_free_netdev;

         status = hdd_register_hostapd( pAdapter, rtnl_held );
         if( VOS_STATUS_SUCCESS != status )
         {
            hdd_deinit_adapter(pHddCtx, pAdapter);
            goto err_free_netdev;
         }

         netif_tx_disable(pAdapter->dev);
         netif_carrier_off(pAdapter->dev);

         hdd_set_conparam( 1 );
         break;
      }
      case WLAN_HDD_MONITOR:
      {
#ifdef CONFIG_CFG80211   
         pAdapter = hdd_alloc_station_adapter( pHddCtx, macAddr, iface_name );
         if( NULL == pAdapter )
            return NULL;

         pAdapter->wdev.iftype = NL80211_IFTYPE_MONITOR; 
         pAdapter->device_mode = session_type;
         status = hdd_register_interface( pAdapter, rtnl_held );
#if LINUX_VERSION_CODE > KERNEL_VERSION(2,6,29)
         pAdapter->dev->netdev_ops = &wlan_mon_drv_ops;
#else
         pAdapter->dev->open = hdd_mon_open;
         pAdapter->dev->hard_start_xmit = hdd_mon_hard_start_xmit;
#endif
         hdd_init_tx_rx( pAdapter );
         set_bit(INIT_TX_RX_SUCCESS, &pAdapter->event_flags);
         //Set adapter to be used for data tx. It will use either GO or softap.
         pAdapter->sessionCtx.monitor.pAdapterForTx = 
                           hdd_get_adapter(pAdapter->pHddCtx, WLAN_HDD_SOFTAP);
#ifdef WLAN_FEATURE_P2P
         if (NULL == pAdapter->sessionCtx.monitor.pAdapterForTx)
         {
            pAdapter->sessionCtx.monitor.pAdapterForTx = 
                           hdd_get_adapter(pAdapter->pHddCtx, WLAN_HDD_P2P_GO);
         }
#endif
         /* This workqueue will be used to transmit management packet over
          * monitor interface. */
         INIT_WORK(&pAdapter->sessionCtx.monitor.pAdapterForTx->monTxWorkQueue,
                   hdd_mon_tx_work_queue);
#endif
      }
         break;
#ifdef ANI_MANF_DIAG
      case WLAN_HDD_FTM:
      {
         pAdapter = hdd_alloc_station_adapter( pHddCtx, macAddr, iface_name );

         if( NULL == pAdapter )
            return NULL;
         /* Assign NL80211_IFTYPE_STATION as interface type to resolve Kernel Warning
          * message while loading driver in FTM mode. */
         pAdapter->wdev.iftype = NL80211_IFTYPE_STATION;
         pAdapter->device_mode = session_type;
         status = hdd_register_interface( pAdapter, rtnl_held );
      }
         break;
#endif
      default:
      {
         VOS_ASSERT(0);
         return NULL;
      }
   }
