switch(csrtype)
    {
    case eCSR_BSS_TYPE_INFRASTRUCTURE:
        ret = eSIR_INFRASTRUCTURE_MODE;
        break;
    case eCSR_BSS_TYPE_IBSS:
    case eCSR_BSS_TYPE_START_IBSS:
        ret = eSIR_IBSS_MODE;
        break;
    case eCSR_BSS_TYPE_WDS_AP:
        ret = eSIR_BTAMP_AP_MODE;
        break;
    case eCSR_BSS_TYPE_WDS_STA:
        ret = eSIR_BTAMP_STA_MODE;
        break;
#ifdef WLAN_SOFTAP_FEATURE
    case eCSR_BSS_TYPE_INFRA_AP:
        ret = eSIR_INFRA_AP_MODE;
        break;
#endif
    case eCSR_BSS_TYPE_ANY:
    default:
        ret = eSIR_AUTO_MODE;
        break;
    }
