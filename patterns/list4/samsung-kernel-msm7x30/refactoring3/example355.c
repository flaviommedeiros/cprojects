switch (value[0])
    {
        case WE_GET_11D_STATE:
        {
           tSmeConfigParams smeConfig;;
           
           sme_GetConfigParam(hHal,&smeConfig);
           
           *value = smeConfig.csrConfig.Is11dSupportEnabled;

            VOS_TRACE(VOS_MODULE_ID_HDD, VOS_TRACE_LEVEL_INFO, ("11D state=%ld!!\n"),*value);

           break;
        }

        case WE_IBSS_STATUS:
           VOS_TRACE(VOS_MODULE_ID_HDD, VOS_TRACE_LEVEL_INFO, "****Return IBSS Status*****\n");
           break;

        case WE_PMC_STATE:
        {
             *value = pmcGetPmcState(hHal);
             VOS_TRACE(VOS_MODULE_ID_HDD, VOS_TRACE_LEVEL_INFO, ("PMC state=%ld!!\n"),*value);
             break;
        }
        case WE_GET_WLAN_DBG:
        {
           vos_trace_display();
           *value = 0;
           break;
        }
        case WE_MODULE_DOWN_IND:
        {
            VOS_TRACE(VOS_MODULE_ID_HDD, VOS_TRACE_LEVEL_INFO,"%s: sending WLAN_MODULE_DOWN_IND", __FUNCTION__);
            send_btc_nlink_msg(WLAN_MODULE_DOWN_IND, 0);
#ifdef WLAN_BTAMP_FEATURE
            VOS_TRACE(VOS_MODULE_ID_HDD, VOS_TRACE_LEVEL_INFO,"%s: Take down AMP PAL", __FUNCTION__);
            BSL_Deinit(vos_get_global_context(VOS_MODULE_ID_HDD, NULL));
#endif
            //WLANBAP_Close(vos_get_global_context(VOS_MODULE_ID_HDD, NULL));

            *value = 0;
            break;
        }
        case WE_GET_MAX_ASSOC:
        {
            if (ccmCfgGetInt(hHal, WNI_CFG_ASSOC_STA_LIMIT, (tANI_U32 *)value) != eHAL_STATUS_SUCCESS)
            {
                ret = -EIO;
            }
            break;
        }

#ifdef FEATURE_WLAN_INTEGRATED_SOC
        case WE_GET_WDI_DBG:
        {
           wpalTraceDisplay();
           *value = 0;
           break;
        }
#endif // FEATURE_WLAN_INTEGRATED_SOC

        case WE_GET_SAP_AUTO_CHANNEL_SELECTION:
        {
            *value = (WLAN_HDD_GET_CTX(pAdapter))->cfg_ini->apAutoChannelSelection;
            break;
        }
        case WE_GET_CONCURRENCY_MODE:
        {
           *value = hdd_get_concurrency_mode ( );

           VOS_TRACE(VOS_MODULE_ID_HDD, VOS_TRACE_LEVEL_INFO, ("concurrency mode=%d \n"),*value);
           break;
        }

        default:
        {
            hddLog(LOGE, "Invalid IOCTL get_value command %d ",value[0]);
            break;
        }
    }
