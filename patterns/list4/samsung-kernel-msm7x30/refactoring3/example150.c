switch (*param) {
	case PRISM2_PARAM_TXRATECTRL:
		*param = local->fw_tx_rate_control;
		break;

	case PRISM2_PARAM_BEACON_INT:
		*param = local->beacon_int;
		break;

	case PRISM2_PARAM_PSEUDO_IBSS:
		*param = local->pseudo_adhoc;
		break;

	case PRISM2_PARAM_ALC:
		ret = -EOPNOTSUPP; /* FIX */
		break;

	case PRISM2_PARAM_DUMP:
		*param = local->frame_dump;
		break;

	case PRISM2_PARAM_OTHER_AP_POLICY:
		if (local->ap != NULL)
			*param = local->ap->ap_policy;
		else
			ret = -EOPNOTSUPP;
		break;

	case PRISM2_PARAM_AP_MAX_INACTIVITY:
		if (local->ap != NULL)
			*param = local->ap->max_inactivity / HZ;
		else
			ret = -EOPNOTSUPP;
		break;

	case PRISM2_PARAM_AP_BRIDGE_PACKETS:
		if (local->ap != NULL)
			*param = local->ap->bridge_packets;
		else
			ret = -EOPNOTSUPP;
		break;

	case PRISM2_PARAM_DTIM_PERIOD:
		*param = local->dtim_period;
		break;

	case PRISM2_PARAM_AP_NULLFUNC_ACK:
		if (local->ap != NULL)
			*param = local->ap->nullfunc_ack;
		else
			ret = -EOPNOTSUPP;
		break;

	case PRISM2_PARAM_MAX_WDS:
		*param = local->wds_max_connections;
		break;

	case PRISM2_PARAM_AP_AUTOM_AP_WDS:
		if (local->ap != NULL)
			*param = local->ap->autom_ap_wds;
		else
			ret = -EOPNOTSUPP;
		break;

	case PRISM2_PARAM_AP_AUTH_ALGS:
		*param = local->auth_algs;
		break;

	case PRISM2_PARAM_MONITOR_ALLOW_FCSERR:
		*param = local->monitor_allow_fcserr;
		break;

	case PRISM2_PARAM_HOST_ENCRYPT:
		*param = local->host_encrypt;
		break;

	case PRISM2_PARAM_HOST_DECRYPT:
		*param = local->host_decrypt;
		break;

	case PRISM2_PARAM_HOST_ROAMING:
		*param = local->host_roaming;
		break;

	case PRISM2_PARAM_BCRX_STA_KEY:
		*param = local->bcrx_sta_key;
		break;

	case PRISM2_PARAM_IEEE_802_1X:
		*param = local->ieee_802_1x;
		break;

	case PRISM2_PARAM_ANTSEL_TX:
		*param = local->antsel_tx;
		break;

	case PRISM2_PARAM_ANTSEL_RX:
		*param = local->antsel_rx;
		break;

	case PRISM2_PARAM_MONITOR_TYPE:
		*param = local->monitor_type;
		break;

	case PRISM2_PARAM_WDS_TYPE:
		*param = local->wds_type;
		break;

	case PRISM2_PARAM_HOSTSCAN:
		ret = -EOPNOTSUPP;
		break;

	case PRISM2_PARAM_AP_SCAN:
		*param = local->passive_scan_interval;
		break;

	case PRISM2_PARAM_ENH_SEC:
		*param = local->enh_sec;
		break;

#ifdef PRISM2_IO_DEBUG
	case PRISM2_PARAM_IO_DEBUG:
		*param = local->io_debug_enabled;
		break;
#endif /* PRISM2_IO_DEBUG */

	case PRISM2_PARAM_BASIC_RATES:
		*param = local->basic_rates;
		break;

	case PRISM2_PARAM_OPER_RATES:
		*param = local->tx_rate_control;
		break;

	case PRISM2_PARAM_HOSTAPD:
		*param = local->hostapd;
		break;

	case PRISM2_PARAM_HOSTAPD_STA:
		*param = local->hostapd_sta;
		break;

	case PRISM2_PARAM_WPA:
		if (local->sta_fw_ver < PRISM2_FW_VER(1,7,0))
			ret = -EOPNOTSUPP;
		*param = local->wpa;
		break;

	case PRISM2_PARAM_PRIVACY_INVOKED:
		*param = local->privacy_invoked;
		break;

	case PRISM2_PARAM_TKIP_COUNTERMEASURES:
		*param = local->tkip_countermeasures;
		break;

	case PRISM2_PARAM_DROP_UNENCRYPTED:
		*param = local->drop_unencrypted;
		break;

	case PRISM2_PARAM_SCAN_CHANNEL_MASK:
		*param = local->scan_channel_mask;
		break;

	default:
		printk(KERN_DEBUG "%s: get_prism2_param: unknown param %d\n",
		       dev->name, *param);
		ret = -EOPNOTSUPP;
		break;
	}
