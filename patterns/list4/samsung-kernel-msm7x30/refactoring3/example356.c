switch(sub_cmd)
    {
        case WE_SET_WLAN_DBG:
        {
            vos_trace_setValue( value[1], value[2], value[3]);
            break;
        }
#ifdef FEATURE_WLAN_INTEGRATED_SOC
        case WE_SET_WDI_DBG:
        {
            wpalTraceSetLevel( value[1], value[2], value[3]);
            break;
        }
#endif // FEATURE_WLAN_INTEGRATED_SOC
        case WE_SET_SAP_CHANNELS:
        {
            ret = iw_softap_set_channel_range( dev, value[1], value[2], value[3]);
            break;
        }

        default:
        {
            hddLog(LOGE, "Invalid IOCTL command %d  \n",  sub_cmd );
            break;
        }
    }
