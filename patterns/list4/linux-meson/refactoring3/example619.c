switch (cfg_cmd) {
          case UNIFI_CFG_POWER:
            r = unifi_cfg_power(priv, (unsigned char*)arg);
            break;
          case UNIFI_CFG_POWERSAVE:
            r = unifi_cfg_power_save(priv, (unsigned char*)arg);
            break;
          case UNIFI_CFG_POWERSUPPLY:
            r = unifi_cfg_power_supply(priv, (unsigned char*)arg);
            break;
          case UNIFI_CFG_FILTER:
            r = unifi_cfg_packet_filters(priv, (unsigned char*)arg);
            break;
          case UNIFI_CFG_GET:
            r = unifi_cfg_get_info(priv, (unsigned char*)arg);
            break;
          case UNIFI_CFG_WMM_QOSINFO:
            r = unifi_cfg_wmm_qos_info(priv, (unsigned char*)arg);
            break;
          case UNIFI_CFG_WMM_ADDTS:
            r = unifi_cfg_wmm_addts(priv, (unsigned char*)arg);
            break;
          case UNIFI_CFG_WMM_DELTS:
            r = unifi_cfg_wmm_delts(priv, (unsigned char*)arg);
            break;
          case UNIFI_CFG_STRICT_DRAFT_N:
            r = unifi_cfg_strict_draft_n(priv, (unsigned char*)arg);
            break;
          case UNIFI_CFG_ENABLE_OKC:
            r = unifi_cfg_enable_okc(priv, (unsigned char*)arg);
            break;
#ifdef CSR_SUPPORT_SME
          case UNIFI_CFG_CORE_DUMP:
            CsrWifiRouterCtrlWifiOffIndSend(priv->CSR_WIFI_SME_IFACEQUEUE,0,CSR_WIFI_SME_CONTROL_INDICATION_ERROR);
            unifi_trace(priv, UDBG2, "UNIFI_CFG_CORE_DUMP: sent wifi off indication\n");
            break;
#endif
#ifdef CSR_SUPPORT_WEXT_AP
          case UNIFI_CFG_SET_AP_CONFIG:
            r= unifi_cfg_set_ap_config(priv,(unsigned char*)arg);
            break;
#endif
          default:
            unifi_error(priv, "UNIFI_CFG: Unknown Command (%d)\n", cfg_cmd);
            r = -EINVAL;
            goto out;
        }
