switch (param) {
	case PRISM2_PARAM_TXRATECTRL:
		local->fw_tx_rate_control = value;
		break;

	case PRISM2_PARAM_BEACON_INT:
		if (hostap_set_word(dev, HFA384X_RID_CNFBEACONINT, value) ||
		    local->func->reset_port(dev))
			ret = -EINVAL;
		else
			local->beacon_int = value;
		break;

#ifndef PRISM2_NO_STATION_MODES
	case PRISM2_PARAM_PSEUDO_IBSS:
		if (value == local->pseudo_adhoc)
			break;

		if (value != 0 && value != 1) {
			ret = -EINVAL;
			break;
		}

		printk(KERN_DEBUG "prism2: %s: pseudo IBSS change %d -> %d\n",
		       dev->name, local->pseudo_adhoc, value);
		local->pseudo_adhoc = value;
		if (local->iw_mode != IW_MODE_ADHOC)
			break;

		if (hostap_set_word(dev, HFA384X_RID_CNFPORTTYPE,
				    hostap_get_porttype(local))) {
			ret = -EOPNOTSUPP;
			break;
		}

		if (local->func->reset_port(dev))
			ret = -EINVAL;
		break;
#endif /* PRISM2_NO_STATION_MODES */

	case PRISM2_PARAM_ALC:
		printk(KERN_DEBUG "%s: %s ALC\n", dev->name,
		       value == 0 ? "Disabling" : "Enabling");
		val = HFA384X_TEST_CFG_BIT_ALC;
		local->func->cmd(dev, HFA384X_CMDCODE_TEST |
				 (HFA384X_TEST_CFG_BITS << 8),
				 value == 0 ? 0 : 1, &val, NULL);
		break;

	case PRISM2_PARAM_DUMP:
		local->frame_dump = value;
		break;

	case PRISM2_PARAM_OTHER_AP_POLICY:
		if (value < 0 || value > 3) {
			ret = -EINVAL;
			break;
		}
		if (local->ap != NULL)
			local->ap->ap_policy = value;
		break;

	case PRISM2_PARAM_AP_MAX_INACTIVITY:
		if (value < 0 || value > 7 * 24 * 60 * 60) {
			ret = -EINVAL;
			break;
		}
		if (local->ap != NULL)
			local->ap->max_inactivity = value * HZ;
		break;

	case PRISM2_PARAM_AP_BRIDGE_PACKETS:
		if (local->ap != NULL)
			local->ap->bridge_packets = value;
		break;

	case PRISM2_PARAM_DTIM_PERIOD:
		if (value < 0 || value > 65535) {
			ret = -EINVAL;
			break;
		}
		if (hostap_set_word(dev, HFA384X_RID_CNFOWNDTIMPERIOD, value)
		    || local->func->reset_port(dev))
			ret = -EINVAL;
		else
			local->dtim_period = value;
		break;

	case PRISM2_PARAM_AP_NULLFUNC_ACK:
		if (local->ap != NULL)
			local->ap->nullfunc_ack = value;
		break;

	case PRISM2_PARAM_MAX_WDS:
		local->wds_max_connections = value;
		break;

	case PRISM2_PARAM_AP_AUTOM_AP_WDS:
		if (local->ap != NULL) {
			if (!local->ap->autom_ap_wds && value) {
				/* add WDS link to all APs in STA table */
				hostap_add_wds_links(local);
			}
			local->ap->autom_ap_wds = value;
		}
		break;

	case PRISM2_PARAM_AP_AUTH_ALGS:
		local->auth_algs = value;
		if (hostap_set_auth_algs(local))
			ret = -EINVAL;
		break;

	case PRISM2_PARAM_MONITOR_ALLOW_FCSERR:
		local->monitor_allow_fcserr = value;
		break;

	case PRISM2_PARAM_HOST_ENCRYPT:
		local->host_encrypt = value;
		if (hostap_set_encryption(local) ||
		    local->func->reset_port(dev))
			ret = -EINVAL;
		break;

	case PRISM2_PARAM_HOST_DECRYPT:
		local->host_decrypt = value;
		if (hostap_set_encryption(local) ||
		    local->func->reset_port(dev))
			ret = -EINVAL;
		break;

#ifndef PRISM2_NO_STATION_MODES
	case PRISM2_PARAM_HOST_ROAMING:
		if (value < 0 || value > 2) {
			ret = -EINVAL;
			break;
		}
		local->host_roaming = value;
		if (hostap_set_roaming(local) || local->func->reset_port(dev))
			ret = -EINVAL;
		break;
#endif /* PRISM2_NO_STATION_MODES */

	case PRISM2_PARAM_BCRX_STA_KEY:
		local->bcrx_sta_key = value;
		break;

	case PRISM2_PARAM_IEEE_802_1X:
		local->ieee_802_1x = value;
		break;

	case PRISM2_PARAM_ANTSEL_TX:
		if (value < 0 || value > HOSTAP_ANTSEL_HIGH) {
			ret = -EINVAL;
			break;
		}
		local->antsel_tx = value;
		hostap_set_antsel(local);
		break;

	case PRISM2_PARAM_ANTSEL_RX:
		if (value < 0 || value > HOSTAP_ANTSEL_HIGH) {
			ret = -EINVAL;
			break;
		}
		local->antsel_rx = value;
		hostap_set_antsel(local);
		break;

	case PRISM2_PARAM_MONITOR_TYPE:
		if (value != PRISM2_MONITOR_80211 &&
		    value != PRISM2_MONITOR_CAPHDR &&
		    value != PRISM2_MONITOR_PRISM &&
		    value != PRISM2_MONITOR_RADIOTAP) {
			ret = -EINVAL;
			break;
		}
		local->monitor_type = value;
		if (local->iw_mode == IW_MODE_MONITOR)
			hostap_monitor_set_type(local);
		break;

	case PRISM2_PARAM_WDS_TYPE:
		local->wds_type = value;
		break;

	case PRISM2_PARAM_HOSTSCAN:
	{
		struct hfa384x_hostscan_request scan_req;
		u16 rate;

		memset(&scan_req, 0, sizeof(scan_req));
		scan_req.channel_list = cpu_to_le16(0x3fff);
		switch (value) {
		case 1: rate = HFA384X_RATES_1MBPS; break;
		case 2: rate = HFA384X_RATES_2MBPS; break;
		case 3: rate = HFA384X_RATES_5MBPS; break;
		case 4: rate = HFA384X_RATES_11MBPS; break;
		default: rate = HFA384X_RATES_1MBPS; break;
		}
		scan_req.txrate = cpu_to_le16(rate);
		/* leave SSID empty to accept all SSIDs */

		if (local->iw_mode == IW_MODE_MASTER) {
			if (hostap_set_word(dev, HFA384X_RID_CNFPORTTYPE,
					    HFA384X_PORTTYPE_BSS) ||
			    local->func->reset_port(dev))
				printk(KERN_DEBUG "Leaving Host AP mode "
				       "for HostScan failed\n");
		}

		if (local->func->set_rid(dev, HFA384X_RID_HOSTSCAN, &scan_req,
					 sizeof(scan_req))) {
			printk(KERN_DEBUG "HOSTSCAN failed\n");
			ret = -EINVAL;
		}
		if (local->iw_mode == IW_MODE_MASTER) {
			wait_queue_t __wait;
			init_waitqueue_entry(&__wait, current);
			add_wait_queue(&local->hostscan_wq, &__wait);
			set_current_state(TASK_INTERRUPTIBLE);
			schedule_timeout(HZ);
			if (signal_pending(current))
				ret = -EINTR;
			set_current_state(TASK_RUNNING);
			remove_wait_queue(&local->hostscan_wq, &__wait);

			if (hostap_set_word(dev, HFA384X_RID_CNFPORTTYPE,
					    HFA384X_PORTTYPE_HOSTAP) ||
			    local->func->reset_port(dev))
				printk(KERN_DEBUG "Returning to Host AP mode "
				       "after HostScan failed\n");
		}
		break;
	}

	case PRISM2_PARAM_AP_SCAN:
		local->passive_scan_interval = value;
		if (timer_pending(&local->passive_scan_timer))
			del_timer(&local->passive_scan_timer);
		if (value > 0) {
			local->passive_scan_timer.expires = jiffies +
				local->passive_scan_interval * HZ;
			add_timer(&local->passive_scan_timer);
		}
		break;

	case PRISM2_PARAM_ENH_SEC:
		if (value < 0 || value > 3) {
			ret = -EINVAL;
			break;
		}
		local->enh_sec = value;
		if (hostap_set_word(dev, HFA384X_RID_CNFENHSECURITY,
				    local->enh_sec) ||
		    local->func->reset_port(dev)) {
			printk(KERN_INFO "%s: cnfEnhSecurity requires STA f/w "
			       "1.6.3 or newer\n", dev->name);
			ret = -EOPNOTSUPP;
		}
		break;

#ifdef PRISM2_IO_DEBUG
	case PRISM2_PARAM_IO_DEBUG:
		local->io_debug_enabled = value;
		break;
#endif /* PRISM2_IO_DEBUG */

	case PRISM2_PARAM_BASIC_RATES:
		if ((value & local->tx_rate_control) != value || value == 0) {
			printk(KERN_INFO "%s: invalid basic rate set - basic "
			       "rates must be in supported rate set\n",
			       dev->name);
			ret = -EINVAL;
			break;
		}
		local->basic_rates = value;
		if (hostap_set_word(dev, HFA384X_RID_CNFBASICRATES,
				    local->basic_rates) ||
		    local->func->reset_port(dev))
			ret = -EINVAL;
		break;

	case PRISM2_PARAM_OPER_RATES:
		local->tx_rate_control = value;
		if (hostap_set_rate(dev))
			ret = -EINVAL;
		break;

	case PRISM2_PARAM_HOSTAPD:
		ret = hostap_set_hostapd(local, value, 1);
		break;

	case PRISM2_PARAM_HOSTAPD_STA:
		ret = hostap_set_hostapd_sta(local, value, 1);
		break;

	case PRISM2_PARAM_WPA:
		local->wpa = value;
		if (local->sta_fw_ver < PRISM2_FW_VER(1,7,0))
			ret = -EOPNOTSUPP;
		else if (hostap_set_word(dev, HFA384X_RID_SSNHANDLINGMODE,
					 value ? 1 : 0))
			ret = -EINVAL;
		break;

	case PRISM2_PARAM_PRIVACY_INVOKED:
		local->privacy_invoked = value;
		if (hostap_set_encryption(local) ||
		    local->func->reset_port(dev))
			ret = -EINVAL;
		break;

	case PRISM2_PARAM_TKIP_COUNTERMEASURES:
		local->tkip_countermeasures = value;
		break;

	case PRISM2_PARAM_DROP_UNENCRYPTED:
		local->drop_unencrypted = value;
		break;

	case PRISM2_PARAM_SCAN_CHANNEL_MASK:
		local->scan_channel_mask = value;
		break;

	default:
		printk(KERN_DEBUG "%s: prism2_param: unknown param %d\n",
		       dev->name, param);
		ret = -EOPNOTSUPP;
		break;
	}
