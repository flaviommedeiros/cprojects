switch(sub_cmd)
    {
       case WE_WOWL_ADD_PTRN:
          VOS_TRACE(VOS_MODULE_ID_HDD, VOS_TRACE_LEVEL_INFO, "ADD_PTRN\n");
          hdd_add_wowl_ptrn((char*)wrqu->data.pointer);
          break;
       case WE_WOWL_DEL_PTRN:
          VOS_TRACE(VOS_MODULE_ID_HDD, VOS_TRACE_LEVEL_INFO, "DEL_PTRN\n");
          hdd_del_wowl_ptrn((char*)wrqu->data.pointer);
          break;
#if defined WLAN_FEATURE_VOWIFI
       case WE_NEIGHBOR_REPORT_REQUEST:
          {
             tRrmNeighborReq neighborReq;
             tRrmNeighborRspCallbackInfo callbackInfo;

             if (pConfig->fRrmEnable)
             {
                VOS_TRACE(VOS_MODULE_ID_HDD, VOS_TRACE_LEVEL_INFO, "Neighbor Request\n");
                neighborReq.no_ssid = (wrqu->data.length - 1) ? false : true ;
                if( !neighborReq.no_ssid )
                {
                   neighborReq.ssid.length = (wrqu->data.length - 1) > 32 ? 32 : (wrqu->data.length - 1) ;
                   vos_mem_copy( neighborReq.ssid.ssId, wrqu->data.pointer, neighborReq.ssid.length );
                }

                callbackInfo.neighborRspCallback = NULL;
                callbackInfo.neighborRspCallbackContext = NULL;
                callbackInfo.timeout = 5000;   //5 seconds
                sme_NeighborReportRequest(  WLAN_HDD_GET_HAL_CTX(pAdapter), pAdapter->sessionId, &neighborReq, &callbackInfo );
             }
             else
             {
                hddLog(LOGE, "%s: Ignoring neighbor request as RRM is not enabled\n", __func__);
                ret = -EINVAL;
             }
          }
          break;
#endif
#ifdef WLAN_FEATURE_P2P
       case WE_SET_AP_WPS_IE:
          hddLog( LOGE, "Received WE_SET_AP_WPS_IE" );
#ifdef WLAN_FEATURE_P2P
          sme_updateP2pIe( WLAN_HDD_GET_HAL_CTX(pAdapter), wrqu->data.pointer, wrqu->data.length );
#endif // WLAN_FEATURE_P2P
          break;
#endif
       case WE_SET_CONFIG:
          vstatus = hdd_execute_config_command(pHddCtx, wrqu->data.pointer);
          if (VOS_STATUS_SUCCESS != vstatus)
          {
             ret = -EINVAL;
          }
          break;
       default:
       {
           hddLog(LOGE, "%s: Invalid sub command %d\n",__FUNCTION__, sub_cmd);
           ret = -EINVAL;
           break;
       }
    }
