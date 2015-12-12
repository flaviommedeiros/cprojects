switch (type)
        {
            case NL80211_IFTYPE_STATION:
#ifdef WLAN_FEATURE_P2P
            case NL80211_IFTYPE_P2P_CLIENT:
#endif
                hddLog(VOS_TRACE_LEVEL_INFO,
                   "%s: setting interface Type to INFRASTRUCTURE", __func__);
                pRoamProfile->BSSType = eCSR_BSS_TYPE_INFRASTRUCTURE;
#ifdef WLAN_FEATURE_11AC
                if(pConfig->dot11Mode == eHDD_DOT11_MODE_AUTO)
                {
                    pConfig->dot11Mode = eHDD_DOT11_MODE_11ac;
                }
#endif
                pRoamProfile->phyMode = 
                hdd_cfg_xlate_to_csr_phy_mode(pConfig->dot11Mode);
                wdev->iftype = type;
#ifdef WLAN_FEATURE_P2P
                pAdapter->device_mode = (type == NL80211_IFTYPE_STATION) ?
                                WLAN_HDD_INFRA_STATION: WLAN_HDD_P2P_CLIENT;
#endif
                break;
            case NL80211_IFTYPE_ADHOC:
                hddLog(VOS_TRACE_LEVEL_INFO,
                  "%s: setting interface Type to ADHOC", __func__);
                pRoamProfile->BSSType = eCSR_BSS_TYPE_START_IBSS;
                pRoamProfile->phyMode =
                    hdd_cfg_xlate_to_csr_phy_mode(pConfig->dot11Mode);
                wdev->iftype = type;
                break;

            case NL80211_IFTYPE_AP:
#ifdef WLAN_FEATURE_P2P
            case NL80211_IFTYPE_P2P_GO:
#endif
            {
                hddLog(VOS_TRACE_LEVEL_INFO_HIGH,
                      "%s: setting interface Type to %s", __func__,
                      (type == NL80211_IFTYPE_AP) ? "SoftAP" : "P2pGo");

                //De-init the adapter.
                hdd_stop_adapter( pHddCtx, pAdapter );
                hdd_deinit_adapter( pHddCtx, pAdapter );
                memset(&pAdapter->sessionCtx, 0, sizeof(pAdapter->sessionCtx));
#ifdef WLAN_SOFTAP_FEATURE
#ifdef WLAN_FEATURE_P2P
                pAdapter->device_mode = (type == NL80211_IFTYPE_AP) ?
                                   WLAN_HDD_SOFTAP : WLAN_HDD_P2P_GO;
#else
                pAdapter->device_mode = WLAN_HDD_SOFTAP;
#endif

                //Disable BMPS and IMPS if enabled
                //before starting Go
                if(WLAN_HDD_P2P_GO == pAdapter->device_mode)
                {
                    if(VOS_STATUS_E_FAILURE == 
                       hdd_disable_bmps_imps(pHddCtx, WLAN_HDD_P2P_GO))
                    {
                       //Fail to Exit BMPS
                       VOS_ASSERT(0);
                    }
                }

                if ((WLAN_HDD_SOFTAP == pAdapter->device_mode) &&
                    (pConfig->apRandomBssidEnabled))
                {
                    /* To meet Android requirements create a randomized
                       MAC address of the form 02:1A:11:Fx:xx:xx */
                    get_random_bytes(&ndev->dev_addr[3], 3);
                    ndev->dev_addr[0] = 0x02;
                    ndev->dev_addr[1] = 0x1A;
                    ndev->dev_addr[2] = 0x11;
                    ndev->dev_addr[3] |= 0xF0;
                    memcpy(pAdapter->macAddressCurrent.bytes, ndev->dev_addr,
                           VOS_MAC_ADDR_SIZE);
                    pr_info("wlan: Generated HotSpot BSSID "
                            "%02x:%02x:%02x:%02x:%02x:%02x\n",
                            ndev->dev_addr[0],
                            ndev->dev_addr[1],
                            ndev->dev_addr[2],
                            ndev->dev_addr[3],
                            ndev->dev_addr[4],
                            ndev->dev_addr[5]);
                }

                hdd_set_ap_ops( pAdapter->dev );

                status = hdd_init_ap_mode(pAdapter);
                if(status != VOS_STATUS_SUCCESS)
                {
                    hddLog(VOS_TRACE_LEVEL_FATAL,
                           "%s: Error initializing the ap mode", __func__);
                    return -EINVAL;
                }
                hdd_set_conparam(1);

#endif
                /*interface type changed update in wiphy structure*/
                if(wdev)
                {
                    wdev->iftype = type;
                    pHddCtx->change_iface = type;
                }
                else
                {
                    hddLog(VOS_TRACE_LEVEL_ERROR,
                            "%s: ERROR !!!! Wireless dev is NULL", __func__);
                    return -EINVAL;
                }
                goto done;
            }

            default:
                hddLog(VOS_TRACE_LEVEL_ERROR, "%s: Unsupported interface Type",
                        __func__);
                return -EOPNOTSUPP;
        }
