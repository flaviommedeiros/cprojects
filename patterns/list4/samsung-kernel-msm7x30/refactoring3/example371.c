switch(type)
       {
           case NL80211_IFTYPE_STATION:
#ifdef WLAN_FEATURE_P2P
           case NL80211_IFTYPE_P2P_CLIENT:
#endif
           case NL80211_IFTYPE_ADHOC:
                hdd_stop_adapter( pHddCtx, pAdapter );
                hdd_deinit_adapter( pHddCtx, pAdapter );
                wdev->iftype = type;
#ifdef WLAN_FEATURE_P2P
                pAdapter->device_mode = (type == NL80211_IFTYPE_STATION) ?
                                  WLAN_HDD_INFRA_STATION: WLAN_HDD_P2P_CLIENT;
#endif
                hdd_set_conparam(0);
                pHddCtx->change_iface = type;
                memset(&pAdapter->sessionCtx, 0, sizeof(pAdapter->sessionCtx));
                hdd_set_station_ops( pAdapter->dev );
                status = hdd_init_station_mode( pAdapter );
                if( VOS_STATUS_SUCCESS != status )
                    return -EOPNOTSUPP;
                /* In case of JB, for P2P-GO, only change interface will be called,
                 * This is the right place to enable back bmps_imps()
                 */
                hdd_enable_bmps_imps(pHddCtx);
                goto done;
            case NL80211_IFTYPE_AP:
#ifdef WLAN_FEATURE_P2P
            case NL80211_IFTYPE_P2P_GO:
#endif
                wdev->iftype = type;
#ifdef WLAN_FEATURE_P2P
                pAdapter->device_mode = (type == NL80211_IFTYPE_AP) ?
                                        WLAN_HDD_SOFTAP : WLAN_HDD_P2P_GO;
#endif
               goto done;
           default:
                hddLog(VOS_TRACE_LEVEL_ERROR, "%s: Unsupported interface Type",
                        __func__);
                return -EOPNOTSUPP;

       }
