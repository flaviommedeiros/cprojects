switch (sub_cmd)
    {
        case WE_CLEAR_STATS:
        {
            VOS_TRACE(VOS_MODULE_ID_HDD, VOS_TRACE_LEVEL_INFO,"%s: clearing", __FUNCTION__);
            memset(&pAdapter->stats, 0, sizeof(pAdapter->stats));
            memset(&pAdapter->hdd_stats, 0, sizeof(pAdapter->hdd_stats));
            break;
        }
#ifdef WLAN_SOFTAP_FEATURE
        case WE_INIT_AP:
        {
          pr_info("Init AP trigger\n");
          hdd_open_adapter( WLAN_HDD_GET_CTX(pAdapter), WLAN_HDD_SOFTAP, "softap.%d",
                 wlan_hdd_get_intf_addr( WLAN_HDD_GET_CTX(pAdapter) ),TRUE);
          break;
        }
        case WE_STOP_AP:
        {
           /*FIX ME: Need to be revisited if multiple SAPs to be supported */
           /* As Soft AP mode has been changed to STA already with killing of Hostapd,
            * this is a dead code and need to find the adpater by name rather than mode */
           hdd_adapter_t* pAdapter_to_stop =
                hdd_get_adapter_by_name(WLAN_HDD_GET_CTX(pAdapter), "softap.0");
           if( pAdapter_to_stop )
           {
               hdd_context_t *pHddCtx = WLAN_HDD_GET_CTX(pAdapter);

               pr_info("Stopping AP mode\n");

               /*Make sure that pAdapter cleaned properly*/
               hdd_stop_adapter( pHddCtx, pAdapter_to_stop );
               hdd_deinit_adapter( pHddCtx, pAdapter_to_stop );
               memset(&pAdapter_to_stop->sessionCtx, 0, sizeof(pAdapter_to_stop->sessionCtx));

               wlan_hdd_release_intf_addr(WLAN_HDD_GET_CTX(pAdapter),
                       pAdapter_to_stop->macAddressCurrent.bytes);
               hdd_close_adapter(WLAN_HDD_GET_CTX(pAdapter), pAdapter_to_stop,
                       TRUE);
           }
           else
           {
              printk(KERN_ERR"SAP adaptor not found to stop it!\n");
           }

           break;
        }
#endif
#ifdef WLAN_BTAMP_FEATURE
        case WE_ENABLE_AMP:
        {
            VOS_TRACE(VOS_MODULE_ID_HDD, VOS_TRACE_LEVEL_INFO,"%s: enabling AMP", __FUNCTION__);
            WLANBAP_RegisterWithHCI(pAdapter);
            break;
        }
        case WE_DISABLE_AMP:
        {
            hdd_context_t *pHddCtx = WLAN_HDD_GET_CTX( pAdapter );
            VOS_STATUS status;

            VOS_TRACE(VOS_MODULE_ID_HDD, VOS_TRACE_LEVEL_INFO,"%s: disabling AMP", __FUNCTION__);

            pHddCtx = WLAN_HDD_GET_CTX( pAdapter );
            status = WLANBAP_StopAmp();
            if(VOS_STATUS_SUCCESS != status )
            {
               pHddCtx->isAmpAllowed = VOS_TRUE;
               hddLog(VOS_TRACE_LEVEL_FATAL,
                      "%s: Failed to stop AMP", __func__);
            }
            else
            {
               //a state m/c implementation in PAL is TBD to avoid this delay
               msleep(500);
               pHddCtx->isAmpAllowed = VOS_FALSE;
               WLANBAP_DeregisterFromHCI();
            }

            break;
        }
#endif

        case WE_ENABLE_DXE_STALL_DETECT:
        {
            sme_transportDebug(VOS_FALSE, VOS_TRUE);
            break;
        }
        case WE_DISPLAY_DXE_SNAP_SHOT:
        {
            sme_transportDebug(VOS_TRUE, VOS_FALSE);
            break;
        }

        default:
        {
            hddLog(LOGE, "%s: unknown ioctl %d", __FUNCTION__, sub_cmd);
            break;
        }
    }
