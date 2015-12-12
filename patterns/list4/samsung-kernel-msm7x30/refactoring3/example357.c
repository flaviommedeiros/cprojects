switch(sub_cmd)
    {
        case WE_WLAN_VERSION:
        {
#ifdef FEATURE_WLAN_NON_INTEGRATED_SOC
            status = hdd_wlan_get_version(pAdapter, wrqu, extra);
#else // FEATURE_WLAN_NON_INTEGRATED_SOC
            char *buf = extra;
            wrqu->data.length = snprintf(buf, WE_MAX_STR_LEN, "%s_",
                                         WLAN_CHIP_VERSION);
#endif
            break;
        }

        case WE_GET_STATS:
        {
            hdd_context_t *pHddCtx = WLAN_HDD_GET_CTX(pAdapter);
            hdd_tx_rx_stats_t *pStats = &pAdapter->hdd_stats.hddTxRxStats;
            hdd_chip_reset_stats_t *pResetStats = &pHddCtx->hddChipResetStats;

            snprintf(extra, WE_MAX_STR_LEN,
                     "\nTransmit"
                     "\ncalled %u, dropped %u, backpressured %u, queued %u"
                     "\n      dropped BK %u, BE %u, VI %u, VO %u"
                     "\n   classified BK %u, BE %u, VI %u, VO %u"
                     "\nbackpressured BK %u, BE %u, VI %u, VO %u"
                     "\n       queued BK %u, BE %u, VI %u, VO %u"
                     "\nfetched %u, empty %u, lowres %u, deqerr %u"
                     "\ndequeued %u, depressured %u, completed %u, flushed %u"
                     "\n      fetched BK %u, BE %u, VI %u, VO %u"
                     "\n     dequeued BK %u, BE %u, VI %u, VO %u"
                     "\n  depressured BK %u, BE %u, VI %u, VO %u"
                     "\n      flushed BK %u, BE %u, VI %u, VO %u"
                     "\n\nReceive"
                     "\nchains %u, packets %u, dropped %u, delivered %u, refused %u"
                     "\n\nResetsStats"
                     "\n TotalLogp %u Cmd53 %u MutexRead %u  MIF-Error %u FW-Heartbeat %u Others %u"
                     "\n",
                     pStats->txXmitCalled,
                     pStats->txXmitDropped,
                     pStats->txXmitBackPressured,
                     pStats->txXmitQueued,

                     pStats->txXmitDroppedAC[WLANTL_AC_BK],
                     pStats->txXmitDroppedAC[WLANTL_AC_BE],
                     pStats->txXmitDroppedAC[WLANTL_AC_VI],
                     pStats->txXmitDroppedAC[WLANTL_AC_VO],

                     pStats->txXmitClassifiedAC[WLANTL_AC_BK],
                     pStats->txXmitClassifiedAC[WLANTL_AC_BE],
                     pStats->txXmitClassifiedAC[WLANTL_AC_VI],
                     pStats->txXmitClassifiedAC[WLANTL_AC_VO],

                     pStats->txXmitBackPressuredAC[WLANTL_AC_BK],
                     pStats->txXmitBackPressuredAC[WLANTL_AC_BE],
                     pStats->txXmitBackPressuredAC[WLANTL_AC_VI],
                     pStats->txXmitBackPressuredAC[WLANTL_AC_VO],

                     pStats->txXmitQueuedAC[WLANTL_AC_BK],
                     pStats->txXmitQueuedAC[WLANTL_AC_BE],
                     pStats->txXmitQueuedAC[WLANTL_AC_VI],
                     pStats->txXmitQueuedAC[WLANTL_AC_VO],

                     pStats->txFetched,
                     pStats->txFetchEmpty,
                     pStats->txFetchLowResources,
                     pStats->txFetchDequeueError,

                     pStats->txFetchDequeued,
                     pStats->txFetchDePressured,
                     pStats->txCompleted,
                     pStats->txFlushed,

                     pStats->txFetchedAC[WLANTL_AC_BK],
                     pStats->txFetchedAC[WLANTL_AC_BE],
                     pStats->txFetchedAC[WLANTL_AC_VI],
                     pStats->txFetchedAC[WLANTL_AC_VO],

                     pStats->txFetchDequeuedAC[WLANTL_AC_BK],
                     pStats->txFetchDequeuedAC[WLANTL_AC_BE],
                     pStats->txFetchDequeuedAC[WLANTL_AC_VI],
                     pStats->txFetchDequeuedAC[WLANTL_AC_VO],

                     pStats->txFetchDePressuredAC[WLANTL_AC_BK],
                     pStats->txFetchDePressuredAC[WLANTL_AC_BE],
                     pStats->txFetchDePressuredAC[WLANTL_AC_VI],
                     pStats->txFetchDePressuredAC[WLANTL_AC_VO],

                     pStats->txFlushedAC[WLANTL_AC_BK],
                     pStats->txFlushedAC[WLANTL_AC_BE],
                     pStats->txFlushedAC[WLANTL_AC_VI],
                     pStats->txFlushedAC[WLANTL_AC_VO],

                     pStats->rxChains,
                     pStats->rxPackets,
                     pStats->rxDropped,
                     pStats->rxDelivered,
                     pStats->rxRefused,

                     pResetStats->totalLogpResets,
                     pResetStats->totalCMD53Failures,
                     pResetStats->totalMutexReadFailures,
                     pResetStats->totalMIFErrorFailures,
                     pResetStats->totalFWHearbeatFailures,
                     pResetStats->totalUnknownExceptions
                     );
            wrqu->data.length = strlen(extra)+1;
            break;
        }

        case WE_GET_CFG:
        {
            hdd_cfg_get_config(WLAN_HDD_GET_CTX(pAdapter), extra, WE_MAX_STR_LEN);
            wrqu->data.length = strlen(extra)+1;
            break;
        }
#ifdef WLAN_FEATURE_11AC
        case WE_GET_RSSI:
        {
            v_S7_t s7Rssi = 0;
            wlan_hdd_get_rssi(pAdapter, &s7Rssi);
            snprintf(extra, WE_MAX_STR_LEN, "rssi=%d",s7Rssi);
            wrqu->data.length = strlen(extra)+1;
            break;
        }
#endif
           
        case WE_GET_WMM_STATUS:
        {
            snprintf(extra, WE_MAX_STR_LEN,
                    "\nDir: 0=up, 1=down, 3=both\n"
                    "|------------------------|\n"
                    "|AC | ACM |Admitted| Dir |\n"
                    "|------------------------|\n"
                    "|VO |  %d  |  %3s   |  %d  |\n"
                    "|VI |  %d  |  %3s   |  %d  |\n"
                    "|BE |  %d  |  %3s   |  %d  |\n"
                    "|BK |  %d  |  %3s   |  %d  |\n"
                    "|------------------------|\n",
                    pAdapter->hddWmmStatus.wmmAcStatus[WLANTL_AC_VO].wmmAcAccessRequired,
                    pAdapter->hddWmmStatus.wmmAcStatus[WLANTL_AC_VO].wmmAcAccessAllowed?"YES":"NO",
                    pAdapter->hddWmmStatus.wmmAcStatus[WLANTL_AC_VO].wmmAcTspecInfo.ts_info.direction,
                    pAdapter->hddWmmStatus.wmmAcStatus[WLANTL_AC_VI].wmmAcAccessRequired,
                    pAdapter->hddWmmStatus.wmmAcStatus[WLANTL_AC_VI].wmmAcAccessAllowed?"YES":"NO",
                    pAdapter->hddWmmStatus.wmmAcStatus[WLANTL_AC_VI].wmmAcTspecInfo.ts_info.direction,
                    pAdapter->hddWmmStatus.wmmAcStatus[WLANTL_AC_BE].wmmAcAccessRequired,
                    pAdapter->hddWmmStatus.wmmAcStatus[WLANTL_AC_BE].wmmAcAccessAllowed?"YES":"NO",
                    pAdapter->hddWmmStatus.wmmAcStatus[WLANTL_AC_BE].wmmAcTspecInfo.ts_info.direction,
                    pAdapter->hddWmmStatus.wmmAcStatus[WLANTL_AC_BK].wmmAcAccessRequired,
                    pAdapter->hddWmmStatus.wmmAcStatus[WLANTL_AC_BK].wmmAcAccessAllowed?"YES":"NO",
                    pAdapter->hddWmmStatus.wmmAcStatus[WLANTL_AC_BK].wmmAcTspecInfo.ts_info.direction);


            wrqu->data.length = strlen(extra)+1;
            break;
        }
        case WE_GET_CHANNEL_LIST:
        {
            VOS_STATUS status;
            v_U8_t i, len;
            char* buf ;
            tChannelListInfo channel_list;

            status = iw_softap_get_channel_list(dev, info, wrqu, (char *)&channel_list);
            if ( !VOS_IS_STATUS_SUCCESS( status ) ) 
            {
                hddLog(VOS_TRACE_LEVEL_ERROR, "%s GetChannelList Failed!!!\n",__func__);
                return -EINVAL;
            }
            buf = extra;

            /**
                       * Maximum channels = WNI_CFG_VALID_CHANNEL_LIST_LEN. Maximum buffer
                       * needed = 5 * number of channels. Check if sufficient buffer is available and 
                       * then proceed to fill the buffer.
                       */
            if(WE_MAX_STR_LEN < (5 * WNI_CFG_VALID_CHANNEL_LIST_LEN))
            {
                hddLog(VOS_TRACE_LEVEL_ERROR, "%s Insufficient Buffer to populate channel list\n",__func__);
                return -EINVAL;
            }
            len = snprintf(buf, 5, "%u ", channel_list.num_channels);
            buf += len;
            for(i = 0 ; i < channel_list.num_channels; i++)
            {
                len = snprintf(buf, 5,
                               "%u ", channel_list.channels[i]);
                buf += len;
            }
            wrqu->data.length = strlen(extra)+1;

            break;
        }
        default:  
        {
            hddLog(LOGE, "Invalid IOCTL command %d  \n",  sub_cmd );
            break;
        }
    }
