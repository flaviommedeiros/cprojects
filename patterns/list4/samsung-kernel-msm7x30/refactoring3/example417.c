switch (timerId)
    {
        case eLIM_ADDTS_RSP_TIMER:
            pMac->lim.gLimAddtsRspTimerCount++;
            if (tx_timer_deactivate(&pMac->lim.limTimers.gLimAddtsRspTimer) != TX_SUCCESS)
            {
                // Could not deactivate AddtsRsp Timer
                // Log error
                limLog(pMac, LOGP,
                       FL("Unable to deactivate AddtsRsp timer\n"));
            }
            break;

        case eLIM_MIN_CHANNEL_TIMER:
            if (tx_timer_deactivate(&pMac->lim.limTimers.gLimMinChannelTimer)
                                         != TX_SUCCESS)
            {
                // Could not deactivate min channel timer.
                // Log error
                limLog(pMac, LOGP,
                       FL("Unable to deactivate min channel timer\n"));
            }

#if 0
            // If a background was triggered via Quiet BSS,
            // then we need to adjust the MIN and MAX channel
            // timer's accordingly to the Quiet duration that
            // was specified
            if( eLIM_QUIET_RUNNING == pMac->lim.gLimSpecMgmt.quietState &&
                pMac->lim.gLimTriggerBackgroundScanDuringQuietBss )
            {
                // gLimQuietDuration is already cached in units of
                // system ticks. No conversion is reqd...
                val = pMac->lim.gLimSpecMgmt.quietDuration;
            }
            else
            {
#endif
                if(pMac->lim.gpLimMlmScanReq)
                {
                    val = SYS_MS_TO_TICKS(pMac->lim.gpLimMlmScanReq->minChannelTime);
                }
                else
                {
                    limLog(pMac, LOGE, FL(" gpLimMlmScanReq is NULL "));
                    //No need to change min timer. This is not a scan
                    break;
                }
#if 0
            }
#endif

            if (tx_timer_change(&pMac->lim.limTimers.gLimMinChannelTimer,
                                val, 0) != TX_SUCCESS)
            {
                // Could not change min channel timer.
                // Log error
                limLog(pMac, LOGP, FL("Unable to change min channel timer\n"));
            }

            break;

        case eLIM_PERIODIC_PROBE_REQ_TIMER:
            if (tx_timer_deactivate(&pMac->lim.limTimers.gLimPeriodicProbeReqTimer)
                                         != TX_SUCCESS)
            {
                // Could not deactivate min channel timer.
                // Log error
                limLog(pMac, LOGP,
                       FL("Unable to deactivate periodic timer\n"));
            }

            val = SYS_MS_TO_TICKS(pMac->lim.gpLimMlmScanReq->minChannelTime)/2;
            if (tx_timer_change(&pMac->lim.limTimers.gLimPeriodicProbeReqTimer,
                                val, 0) != TX_SUCCESS)
            {
                // Could not change min channel timer.
                // Log error
                limLog(pMac, LOGP, FL("Unable to change periodic timer\n"));
            }

            break;

        case eLIM_MAX_CHANNEL_TIMER:
            if (tx_timer_deactivate(&pMac->lim.limTimers.gLimMaxChannelTimer)
                                      != TX_SUCCESS)
            {
                // Could not deactivate max channel timer.
                // Log error
                limLog(pMac, LOGP,
                       FL("Unable to deactivate max channel timer\n"));
            }

#if defined(ANI_PRODUCT_TYPE_CLIENT) || defined(ANI_AP_CLIENT_SDK)
            // If a background was triggered via Quiet BSS,
            // then we need to adjust the MIN and MAX channel
            // timer's accordingly to the Quiet duration that
            // was specified
            if (pMac->lim.gLimSystemRole != eLIM_AP_ROLE)
            {
#if 0

                if( eLIM_QUIET_RUNNING == pMac->lim.gLimSpecMgmt.quietState &&
                    pMac->lim.gLimTriggerBackgroundScanDuringQuietBss )
                {
                    // gLimQuietDuration is already cached in units of
                    // system ticks. No conversion is reqd...
                    val = pMac->lim.gLimSpecMgmt.quietDuration;
                }
                else
                {
#endif
                    if(pMac->lim.gpLimMlmScanReq)
                    {
                        val = SYS_MS_TO_TICKS(pMac->lim.gpLimMlmScanReq->maxChannelTime);
                    }
                    else
                    {
                        limLog(pMac, LOGE, FL(" gpLimMlmScanReq is NULL "));
                        //No need to change max timer. This is not a scan
                        break;
                    }
#if 0
                }
#endif
            }
#endif
#if defined(ANI_PRODUCT_TYPE_AP)
            if (pMac->lim.gLimSystemRole == eLIM_AP_ROLE)
            {
                if (wlan_cfgGetInt(pMac, WNI_CFG_ACTIVE_MAXIMUM_CHANNEL_TIME,
                          &val) != eSIR_SUCCESS)
                {
                    /**
                    * Could not get max channel value
                    * from CFG. Log error.
                    */
                    limLog(pMac, LOGP,
                   FL("could not retrieve max channel value\n"));
                }
                val = SYS_MS_TO_TICKS(val);
            }
#endif

            if (tx_timer_change(&pMac->lim.limTimers.gLimMaxChannelTimer,
                                val, 0) != TX_SUCCESS)
            {
                // Could not change max channel timer.
                // Log error
                limLog(pMac, LOGP,
                       FL("Unable to change max channel timer\n"));
            }

            break;

        case eLIM_JOIN_FAIL_TIMER:
            if (tx_timer_deactivate(&pMac->lim.limTimers.gLimJoinFailureTimer)
                                         != TX_SUCCESS)
            {
                /**
                 * Could not deactivate Join Failure
                 * timer. Log error.
                 */
                limLog(pMac, LOGP,
                       FL("Unable to deactivate Join Failure timer\n"));
            }

            if (wlan_cfgGetInt(pMac, WNI_CFG_JOIN_FAILURE_TIMEOUT,
                          &val) != eSIR_SUCCESS)
            {
                /**
                 * Could not get JoinFailureTimeout value
                 * from CFG. Log error.
                 */
                limLog(pMac, LOGP,
                   FL("could not retrieve JoinFailureTimeout value\n"));
            }
            val = SYS_MS_TO_TICKS(val);

            if (tx_timer_change(&pMac->lim.limTimers.gLimJoinFailureTimer,
                                val, 0) != TX_SUCCESS)
            {
                /**
                 * Could not change Join Failure
                 * timer. Log error.
                 */
                limLog(pMac, LOGP,
                       FL("Unable to change Join Failure timer\n"));
            }

            break;

        case eLIM_AUTH_FAIL_TIMER:
            if (tx_timer_deactivate(&pMac->lim.limTimers.gLimAuthFailureTimer)
                                              != TX_SUCCESS)
            {
                // Could not deactivate Auth failure timer.
                // Log error
                limLog(pMac, LOGP,
                       FL("Unable to deactivate auth failure timer\n"));
            }

            // Change timer to reactivate it in future
            if (wlan_cfgGetInt(pMac, WNI_CFG_AUTHENTICATE_FAILURE_TIMEOUT,
                          &val) != eSIR_SUCCESS)
            {
                /**
                 * Could not get AuthFailureTimeout value
                 * from CFG. Log error.
                 */
                limLog(pMac, LOGP,
                   FL("could not retrieve AuthFailureTimeout value\n"));
            }
            val = SYS_MS_TO_TICKS(val);

            if (tx_timer_change(&pMac->lim.limTimers.gLimAuthFailureTimer,
                                val, 0) != TX_SUCCESS)
            {
                // Could not change Authentication failure timer.
                // Log error
                limLog(pMac, LOGP,
                       FL("unable to change Auth failure timer\n"));
            }

            break;

        case eLIM_ASSOC_FAIL_TIMER:
            if (tx_timer_deactivate(&pMac->lim.limTimers.gLimAssocFailureTimer) !=
                                    TX_SUCCESS)
            {
                // Could not deactivate Association failure timer.
                // Log error
                limLog(pMac, LOGP,
                   FL("unable to deactivate Association failure timer\n"));
            }

            // Change timer to reactivate it in future
            if (wlan_cfgGetInt(pMac, WNI_CFG_ASSOCIATION_FAILURE_TIMEOUT,
                          &val) != eSIR_SUCCESS)
            {
                /**
                 * Could not get AssocFailureTimeout value
                 * from CFG. Log error.
                 */
                limLog(pMac, LOGP,
                   FL("could not retrieve AssocFailureTimeout value\n"));
            }
            val = SYS_MS_TO_TICKS(val);

            if (tx_timer_change(&pMac->lim.limTimers.gLimAssocFailureTimer,
                                val, 0) != TX_SUCCESS)
            {
                // Could not change Association failure timer.
                // Log error
                limLog(pMac, LOGP,
                       FL("unable to change Assoc failure timer\n"));
            }

            break;

        case eLIM_REASSOC_FAIL_TIMER:
            if (tx_timer_deactivate(&pMac->lim.limTimers.gLimReassocFailureTimer) !=
                                    TX_SUCCESS)
            {
                // Could not deactivate Reassociation failure timer.
                // Log error
                limLog(pMac, LOGP,
                   FL("unable to deactivate Reassoc failure timer\n"));
            }

            // Change timer to reactivate it in future
            if (wlan_cfgGetInt(pMac, WNI_CFG_REASSOCIATION_FAILURE_TIMEOUT,
                          &val) != eSIR_SUCCESS)
            {
                /**
                 * Could not get ReassocFailureTimeout value
                 * from CFG. Log error.
                 */
                limLog(pMac, LOGP,
                   FL("could not retrieve ReassocFailureTimeout value\n"));
            }
            val = SYS_MS_TO_TICKS(val);

            if (tx_timer_change(&pMac->lim.limTimers.gLimReassocFailureTimer,
                                val, 0) != TX_SUCCESS)
            {
                // Could not change Reassociation failure timer.
                // Log error
                limLog(pMac, LOGP,
                   FL("unable to change Reassociation failure timer\n"));
            }

            break;

        case eLIM_HEART_BEAT_TIMER:
            if (tx_timer_deactivate(&pMac->lim.limTimers.gLimHeartBeatTimer) !=
                                    TX_SUCCESS)
            {
                // Could not deactivate Heartbeat timer.
                // Log error
                limLog(pMac, LOGP,
                       FL("unable to deactivate Heartbeat timer\n"));
            }

            if (wlan_cfgGetInt(pMac, WNI_CFG_BEACON_INTERVAL,
                          &val) != eSIR_SUCCESS)
            {
                /**
                 * Could not get BEACON_INTERVAL value
                 * from CFG. Log error.
                 */
                limLog(pMac, LOGP,
                       FL("could not retrieve BEACON_INTERVAL value\n"));
            }

            if (wlan_cfgGetInt(pMac, WNI_CFG_HEART_BEAT_THRESHOLD, &val1) !=
                                                          eSIR_SUCCESS)
                limLog(pMac, LOGP,
                   FL("could not retrieve heartbeat failure value\n"));

            // Change timer to reactivate it in future
            val = SYS_MS_TO_TICKS(val * val1);

            if (tx_timer_change(&pMac->lim.limTimers.gLimHeartBeatTimer,
                                val, 0) != TX_SUCCESS)
            {
                // Could not change HeartBeat timer.
                // Log error
                limLog(pMac, LOGP,
                       FL("unable to change HeartBeat timer\n"));
            }

            break;

        case eLIM_PROBE_AFTER_HB_TIMER:
            if (tx_timer_deactivate(&pMac->lim.limTimers.gLimProbeAfterHBTimer) !=
                                    TX_SUCCESS)
            {
                // Could not deactivate Heartbeat timer.
                // Log error
                limLog(pMac, LOGP,
                   FL("unable to deactivate probeAfterHBTimer\n"));
            }

            if (wlan_cfgGetInt(pMac, WNI_CFG_PROBE_AFTER_HB_FAIL_TIMEOUT,
                          &val) != eSIR_SUCCESS)
            {
                /**
                 * Could not get PROBE_AFTER_HB_FAILURE
                 * value from CFG. Log error.
                 */
                limLog(pMac, LOGP,
                   FL("could not retrieve PROBE_AFTER_HB_FAIL_TIMEOUT value\n"));
            }

            // Change timer to reactivate it in future
            val = SYS_MS_TO_TICKS(val);

            if (tx_timer_change(&pMac->lim.limTimers.gLimProbeAfterHBTimer,
                                val, 0) != TX_SUCCESS)
            {
                // Could not change HeartBeat timer.
                // Log error
                limLog(pMac, LOGP,
                       FL("unable to change ProbeAfterHBTimer\n"));
            }

            break;

        case eLIM_KEEPALIVE_TIMER:
            if (tx_timer_deactivate(&pMac->lim.limTimers.gLimKeepaliveTimer)
                            != TX_SUCCESS)
            {
                // Could not deactivate Keepalive timer.
                // Log error
                limLog(pMac, LOGP,
                   FL("unable to deactivate KeepaliveTimer timer\n"));
            }

            // Change timer to reactivate it in future

            if (wlan_cfgGetInt(pMac, WNI_CFG_KEEPALIVE_TIMEOUT,
                          &val) != eSIR_SUCCESS)
            {
                /**
                 * Could not get keepalive timeout value
                 * from CFG. Log error.
                 */
                limLog(pMac, LOGP,
                   FL("could not retrieve keepalive timeout value\n"));
            }
            if (val == 0)
            {
                val = 3000;
                pMac->sch.keepAlive = 0;
            } else
                pMac->sch.keepAlive = 1;



            val = SYS_MS_TO_TICKS(val + SYS_TICK_DUR_MS - 1);

            if (tx_timer_change(&pMac->lim.limTimers.gLimKeepaliveTimer,
                                val, val) != TX_SUCCESS)
            {
                // Could not change KeepaliveTimer timer.
                // Log error
                limLog(pMac, LOGP,
                   FL("unable to change KeepaliveTimer timer\n"));
            }

            break;

#if defined(ANI_PRODUCT_TYPE_CLIENT) || defined(ANI_AP_CLIENT_SDK)
        case eLIM_BACKGROUND_SCAN_TIMER:
            if (tx_timer_deactivate(&pMac->lim.limTimers.gLimBackgroundScanTimer)
                            != TX_SUCCESS)
            {
                // Could not deactivate BackgroundScanTimer timer.
                // Log error
                limLog(pMac, LOGP,
                   FL("unable to deactivate BackgroundScanTimer timer\n"));
            }

            // Change timer to reactivate it in future
            if (wlan_cfgGetInt(pMac, WNI_CFG_BACKGROUND_SCAN_PERIOD,
                          &val) != eSIR_SUCCESS)
            {
                /**
                 * Could not get Background scan period value
                 * from CFG. Log error.
                 */
                limLog(pMac, LOGP,
                   FL("could not retrieve Background scan period value\n"));
            }
            if (val == 0)
            {
                val = LIM_BACKGROUND_SCAN_PERIOD_DEFAULT_MS;
                pMac->lim.gLimBackgroundScanDisable = true;
            }
            else
                pMac->lim.gLimBackgroundScanDisable = false;

            val = SYS_MS_TO_TICKS(val);

            if (tx_timer_change(&pMac->lim.limTimers.gLimBackgroundScanTimer,
                                val, val) != TX_SUCCESS)
            {
                // Could not change BackgroundScanTimer timer.
                // Log error
                limLog(pMac, LOGP,
                   FL("unable to change BackgroundScanTimer timer\n"));
            }

            break;
#endif

#ifdef ANI_PRODUCT_TYPE_AP
        case eLIM_PRE_AUTH_CLEANUP_TIMER:
            if (tx_timer_deactivate(&pMac->lim.limTimers.gLimPreAuthClnupTimer) !=
                                    TX_SUCCESS)
            {
                // Could not deactivate Pre-auth cleanup timer.
                // Log error
                limLog(pMac, LOGP,
                   FL("unable to deactivate Pre-auth cleanup timer\n"));
            }

            // Change timer to reactivate it in future
            if (wlan_cfgGetInt(pMac, WNI_CFG_PREAUTH_CLNUP_TIMEOUT,
                          &val) != eSIR_SUCCESS)
            {
                /**
                 * Could not get pre-auth cleanup value
                 * from CFG. Log error.
                 */
                limLog(pMac, LOGP,
                   FL("could not retrieve pre-auth cleanup value\n"));
            }
            val = SYS_MS_TO_TICKS(val);

            if (tx_timer_change(&pMac->lim.limTimers.gLimPreAuthClnupTimer,
                                val, val) != TX_SUCCESS)
            {
                // Could not change pre-auth cleanup timer.
                // Log error
                limLog(pMac, LOGP,
                   FL("unable to change pre-auth cleanup timer\n"));
            }

            break;

        case eLIM_LEARN_INTERVAL_TIMER:
            {
            // Restart Learn Interval timer
            tANI_U32 learnInterval =
              pMac->lim.gpLimMeasReq->measDuration.shortTermPeriod /
              pMac->lim.gpLimMeasReq->channelList.numChannels;

              if (tx_timer_deactivate(
                     &pMac->lim.gLimMeasParams.learnIntervalTimer) != TX_SUCCESS)
              {
                  // Could not deactivate Learn Interval timer.
                  // Log error
                  limLog(pMac, LOGP,
                         FL("Unable to deactivate Learn Interval timer\n"));
              }

              if (tx_timer_change(
                         &pMac->lim.gLimMeasParams.learnIntervalTimer,
                         SYS_MS_TO_TICKS(learnInterval), 0) != TX_SUCCESS)
              {
                  // Could not change Learn Interval timer.
                  // Log error
                  limLog(pMac, LOGP, FL("Unable to change Learn Interval timer\n"));

                  return;
              }

              limLog( pMac, LOG3,
                  FL("Setting the Learn Interval TIMER to %d ticks\n"),
                  SYS_MS_TO_TICKS(learnInterval));
            }
            break;

#endif
#if 0
        case eLIM_CHANNEL_SWITCH_TIMER:
            if (tx_timer_deactivate(&pMac->lim.limTimers.gLimChannelSwitchTimer) != eSIR_SUCCESS)
            {
                limLog(pMac, LOGP, FL("tx_timer_deactivate failed!\n"));
                return;
            }

            if (tx_timer_change(&pMac->lim.limTimers.gLimChannelSwitchTimer,
                        pMac->lim.gLimChannelSwitch.switchTimeoutValue,
                                    0) != TX_SUCCESS)
            {
                limLog(pMac, LOGP, FL("tx_timer_change failed \n"));
                return;
            }
            break;
#endif

        case eLIM_LEARN_DURATION_TIMER:
#ifdef ANI_PRODUCT_TYPE_AP
            if (tx_timer_deactivate(&pMac->lim.gLimMeasParams.learnDurationTimer) != TX_SUCCESS)
            {
                limLog(pMac, LOGP, FL("Could not deactivate learn duration timer\n"));
                return;
            }

            if (pMac->lim.gpLimMeasReq->measControl.longChannelScanPeriodicity &&
                                 (pMac->lim.gLimMeasParams.shortDurationCount ==
                                  pMac->lim.gpLimMeasReq->measControl.longChannelScanPeriodicity))
            {
#ifdef ANI_AP_SDK
                val = pMac->lim.gLimScanDurationConvert.longChannelScanDuration_tick;
#else
                val = SYS_MS_TO_TICKS(pMac->lim.gpLimMeasReq->measDuration.longChannelScanDuration
                                                                    + SYS_TICK_DUR_MS - 1);
                if(val > 1)
                    val--;
#endif /* ANI_AP_SDK */
                // Time to perform measurements for longer term
                if (tx_timer_change(&pMac->lim.gLimMeasParams.learnDurationTimer,
                                                   val, 0) != TX_SUCCESS)
                {
                    // Could not change Learn duration timer.
                    // Log error
                    limLog(pMac, LOGP, FL("Unable to change Learn duration timer\n"));
                    return;
                }
                pMac->lim.gLimMeasParams.shortDurationCount = 0;
            }
            else
            {
#ifdef ANI_AP_SDK
                val = pMac->lim.gLimScanDurationConvert.shortChannelScanDuration_tick;
#else
                val = SYS_MS_TO_TICKS(pMac->lim.gpLimMeasReq->measDuration.shortChannelScanDuration
                                                               + SYS_TICK_DUR_MS - 1);
                if(val > 1)
                    val--;
#endif /* ANI_AP_SDK */
                if (tx_timer_change(&pMac->lim.gLimMeasParams.learnDurationTimer,
                                                       val, 0) != TX_SUCCESS)
                {
                    // Could not change Learn duration timer.
                    // Log error
                    limLog(pMac, LOGP, FL("Unable to change Learn duration timer\n"));
                }
            }
            pMac->lim.gpLimMeasData->duration = val * SYS_TICK_DUR_MS;
#endif
            break;

#if 0
        case eLIM_QUIET_BSS_TIMER:
            if (TX_SUCCESS !=
            tx_timer_deactivate(&pMac->lim.limTimers.gLimQuietBssTimer))
            {
                limLog( pMac, LOGE,
                  FL("Unable to de-activate gLimQuietBssTimer! Will attempt to activate anyway...\n"));
            }

            // gLimQuietDuration appears to be in units of ticks
            // Use it as is
            if (TX_SUCCESS !=
                tx_timer_change( &pMac->lim.limTimers.gLimQuietBssTimer,
                  pMac->lim.gLimSpecMgmt.quietDuration,
                  0))
            {
                limLog( pMac, LOGE,
                  FL("Unable to change gLimQuietBssTimer! Will still attempt to activate anyway...\n"));
            }
            break;

        case eLIM_QUIET_TIMER:
            if( TX_SUCCESS != tx_timer_deactivate(&pMac->lim.limTimers.gLimQuietTimer))
            {
                limLog( pMac, LOGE,
                    FL( "Unable to deactivate gLimQuietTimer! Will still attempt to re-activate anyway...\n" ));
            }

            // Set the NEW timeout value, in ticks
            if( TX_SUCCESS != tx_timer_change( &pMac->lim.limTimers.gLimQuietTimer,
                              SYS_MS_TO_TICKS(pMac->lim.gLimSpecMgmt.quietTimeoutValue), 0))
            {
                limLog( pMac, LOGE,
                    FL( "Unable to change gLimQuietTimer! Will still attempt to re-activate anyway...\n" ));
            }
            break;
#endif

#ifdef WLAN_SOFTAP_FEATURE
#if 0
        case eLIM_WPS_OVERLAP_TIMER:
            {
            // Restart Learn Interval timer

              tANI_U32 WPSOverlapTimer = SYS_MS_TO_TICKS(LIM_WPS_OVERLAP_TIMER_MS);

              if (tx_timer_deactivate(
                     &pMac->lim.limTimers.gLimWPSOverlapTimerObj.gLimWPSOverlapTimer) != TX_SUCCESS)
              {
                  // Could not deactivate Learn Interval timer.
                  // Log error
                  limLog(pMac, LOGP,
                         FL("Unable to deactivate WPS overlap timer\n"));
              }

              if (tx_timer_change(
                         &pMac->lim.limTimers.gLimWPSOverlapTimerObj.gLimWPSOverlapTimer,
                         WPSOverlapTimer, 0) != TX_SUCCESS)
              {
                  // Could not change Learn Interval timer.
                  // Log error
                  limLog(pMac, LOGP, FL("Unable to change WPS overlap timer\n"));

                  return;
              }

              limLog( pMac, LOGE,
                  FL("Setting WPS overlap TIMER to %d ticks\n"),
                  WPSOverlapTimer);
            }
            break;
#endif
#endif

#ifdef WLAN_FEATURE_VOWIFI_11R
        case eLIM_FT_PREAUTH_RSP_TIMER:
            if (tx_timer_deactivate(&pMac->lim.limTimers.gLimFTPreAuthRspTimer) != TX_SUCCESS)
            {
                /**
                ** Could not deactivate Join Failure
                ** timer. Log error.
                **/
                limLog(pMac, LOGP, FL("Unable to deactivate Preauth response Failure timer\n"));
            }
            val = 1000;
            val = SYS_MS_TO_TICKS(val);
            if (tx_timer_change(&pMac->lim.limTimers.gLimFTPreAuthRspTimer,
                                                val, 0) != TX_SUCCESS)
            {
                /**
                * Could not change Join Failure
                * timer. Log error.
                */
                limLog(pMac, LOGP, FL("Unable to change Join Failure timer\n"));
            }
            break;
#endif
#ifdef FEATURE_WLAN_CCX
         case eLIM_TSM_TIMER:
             if (tx_timer_deactivate(&pMac->lim.limTimers.gLimCcxTsmTimer)
                                                                != TX_SUCCESS)
             {
                 limLog(pMac, LOGE, FL("Unable to deactivate TSM timer\n"));
             }
             break;
#endif
#ifdef WLAN_FEATURE_P2P
        case eLIM_REMAIN_CHN_TIMER:
            if (tx_timer_deactivate(&pMac->lim.limTimers.gLimRemainOnChannelTimer) != TX_SUCCESS)
            {
                /**
                ** Could not deactivate Join Failure
                ** timer. Log error.
                **/
                limLog(pMac, LOGP, FL("Unable to deactivate Remain on Chn timer\n"));
            }
            val = 1000;
            val = SYS_MS_TO_TICKS(val);
            if (tx_timer_change(&pMac->lim.limTimers.gLimRemainOnChannelTimer,
                                                val, 0) != TX_SUCCESS)
            {
                /**
                * Could not change Join Failure
                * timer. Log error.
                */
                limLog(pMac, LOGP, FL("Unable to change timer\n"));
            }
            break;
#endif

        default:
            // Invalid timerId. Log error
            break;
    }
