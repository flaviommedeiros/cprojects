switch (Msg->type)
    {
        case LIM_MLM_START_REQ:             limProcessMlmStartReq(pMac, Msg->bodyptr);   break;
        case LIM_MLM_SCAN_REQ:              limProcessMlmScanReq(pMac, Msg->bodyptr);    break;
#ifdef FEATURE_OEM_DATA_SUPPORT
        case LIM_MLM_OEM_DATA_REQ: limProcessMlmOemDataReq(pMac, Msg->bodyptr); break;
#endif
        case LIM_MLM_JOIN_REQ:              limProcessMlmJoinReq(pMac, Msg->bodyptr);    break;
        case LIM_MLM_AUTH_REQ:              limProcessMlmAuthReq(pMac, Msg->bodyptr);    break;
        case LIM_MLM_ASSOC_REQ:             limProcessMlmAssocReq(pMac, Msg->bodyptr);   break;
        case LIM_MLM_REASSOC_REQ:           limProcessMlmReassocReq(pMac, Msg->bodyptr); break;
        case LIM_MLM_DISASSOC_REQ:          limProcessMlmDisassocReq(pMac, Msg->bodyptr);  break;
        case LIM_MLM_DEAUTH_REQ:            limProcessMlmDeauthReq(pMac, Msg->bodyptr);  break;
        case LIM_MLM_SETKEYS_REQ:           limProcessMlmSetKeysReq(pMac, Msg->bodyptr);  break;
        case LIM_MLM_REMOVEKEY_REQ:         limProcessMlmRemoveKeyReq(pMac, Msg->bodyptr); break;
        case SIR_LIM_MIN_CHANNEL_TIMEOUT:   limProcessMinChannelTimeout(pMac);  break;
        case SIR_LIM_MAX_CHANNEL_TIMEOUT:   limProcessMaxChannelTimeout(pMac);  break;
        case SIR_LIM_PERIODIC_PROBE_REQ_TIMEOUT:
                               limProcessPeriodicProbeReqTimer(pMac);  break;
        case SIR_LIM_JOIN_FAIL_TIMEOUT:     limProcessJoinFailureTimeout(pMac);  break;
        case SIR_LIM_AUTH_FAIL_TIMEOUT:     limProcessAuthFailureTimeout(pMac);  break;
        case SIR_LIM_AUTH_RSP_TIMEOUT:      limProcessAuthRspTimeout(pMac, Msg->bodyval);  break;
        case SIR_LIM_ASSOC_FAIL_TIMEOUT:    limProcessAssocFailureTimeout(pMac, Msg->bodyval);  break;
#ifdef WLAN_FEATURE_VOWIFI_11R
        case SIR_LIM_FT_PREAUTH_RSP_TIMEOUT:limProcessFTPreauthRspTimeout(pMac); break;
#endif
#ifdef WLAN_FEATURE_P2P
        case SIR_LIM_REMAIN_CHN_TIMEOUT:    limProcessRemainOnChnTimeout(pMac); break;
#endif
        case LIM_MLM_ADDBA_REQ:             limProcessMlmAddBAReq( pMac, Msg->bodyptr ); break;
        case LIM_MLM_ADDBA_RSP:             limProcessMlmAddBARsp( pMac, Msg->bodyptr ); break;
        case LIM_MLM_DELBA_REQ:             limProcessMlmDelBAReq( pMac, Msg->bodyptr ); break;
        case LIM_MLM_TSPEC_REQ:                 
        default:
            break;
    }
