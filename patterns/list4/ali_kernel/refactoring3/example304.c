switch( eventArray[i] )
        {
            case ZM_EVENT_SCAN:
                {
                    zfScanMgrScanEventStart(dev);
                    eventBypass[eventBypassCount++] = ZM_EVENT_IN_SCAN;
                    eventBypass[eventBypassCount++] = ZM_EVENT_TIMEOUT_SCAN;
                }
                break;

            case ZM_EVENT_TIMEOUT_SCAN:
                {
                    u8_t res;

                    res = zfScanMgrScanEventTimeout(dev);
                    if ( res == 0 )
                    {
                        eventBypass[eventBypassCount++] = ZM_EVENT_TIMEOUT_SCAN;
                    }
                    else if ( res == 1 )
                    {
                        eventBypass[eventBypassCount++] = ZM_EVENT_IN_SCAN;
                    }
                }
                break;

            case ZM_EVENT_IBSS_MONITOR:
                {
                    zfStaIbssMonitoring(dev, 0);
                }
                break;

            case ZM_EVENT_IN_SCAN:
                {
                    zfScanMgrScanEventRetry(dev);
                }
                break;

            case ZM_EVENT_CM_TIMER:
                {
                    zm_msg0_mm(ZM_LV_0, "ZM_EVENT_CM_TIMER");

                    wd->sta.cmMicFailureCount = 0;
                }
                break;

            case ZM_EVENT_CM_DISCONNECT:
                {
                    zm_msg0_mm(ZM_LV_0, "ZM_EVENT_CM_DISCONNECT");

                    zfChangeAdapterState(dev, ZM_STA_STATE_DISCONNECT);

                    zmw_enter_critical_section(dev);
                    //zfTimerSchedule(dev, ZM_EVENT_CM_BLOCK_TIMER,
                    //                ZM_TICK_CM_BLOCK_TIMEOUT);

                    /* Timer Resolution on WinXP is 15/16 ms  */
                    /* Decrease Time offset for <XP> Counter Measure */
                    zfTimerSchedule(dev, ZM_EVENT_CM_BLOCK_TIMER,
                                         ZM_TICK_CM_BLOCK_TIMEOUT - ZM_TICK_CM_BLOCK_TIMEOUT_OFFSET);

                    zmw_leave_critical_section(dev);
                    wd->sta.cmMicFailureCount = 0;
                    //zfiWlanDisable(dev);
                    zfHpResetKeyCache(dev);
                    if (wd->zfcbConnectNotify != NULL)
                    {
                        wd->zfcbConnectNotify(dev, ZM_STATUS_MEDIA_DISCONNECT_MIC_FAIL,
                             wd->sta.bssid);
                    }
                }
                break;

            case ZM_EVENT_CM_BLOCK_TIMER:
                {
                    zm_msg0_mm(ZM_LV_0, "ZM_EVENT_CM_BLOCK_TIMER");

                    //zmw_enter_critical_section(dev);
                    wd->sta.cmDisallowSsidLength = 0;
                    if ( wd->sta.bAutoReconnect )
                    {
                        zm_msg0_mm(ZM_LV_0, "ZM_EVENT_CM_BLOCK_TIMER:bAutoReconnect!=0");
                        zfScanMgrScanStop(dev, ZM_SCAN_MGR_SCAN_INTERNAL);
                        zfScanMgrScanStart(dev, ZM_SCAN_MGR_SCAN_INTERNAL);
                    }
                    //zmw_leave_critical_section(dev);
                }
                break;

            case ZM_EVENT_TIMEOUT_ADDBA:
                {
                    if (!wd->addbaComplete && (wd->addbaCount < 5))
                    {
                        zfAggSendAddbaRequest(dev, wd->sta.bssid, 0, 0);
                        wd->addbaCount++;
                        zfTimerSchedule(dev, ZM_EVENT_TIMEOUT_ADDBA, 100);
                    }
                    else
                    {
                        zfTimerCancel(dev, ZM_EVENT_TIMEOUT_ADDBA);
                    }
                }
                break;

            #ifdef ZM_ENABLE_PERFORMANCE_EVALUATION
            case ZM_EVENT_TIMEOUT_PERFORMANCE:
                {
                    zfiPerformanceRefresh(dev);
                }
                break;
            #endif
            case ZM_EVENT_SKIP_COUNTERMEASURE:
				//enable the Countermeasure
				{
					zm_debug_msg0("Countermeasure : Enable MIC Check ");
					wd->TKIP_Group_KeyChanging = 0x0;
				}
				break;

            default:
                break;
        }
