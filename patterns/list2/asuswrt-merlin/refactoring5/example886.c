#ifdef CONFIG_IPW2200_MONITOR
if (priv->ieee->iw_mode == IW_MODE_MONITOR) {
		u8 channel;
		u8 band = 0;

		switch (ieee80211_is_valid_channel(priv->ieee, priv->channel)) {
		case IEEE80211_52GHZ_BAND:
			band = (u8) (IPW_A_MODE << 6) | 1;
			channel = priv->channel;
			break;

		case IEEE80211_24GHZ_BAND:
			band = (u8) (IPW_B_MODE << 6) | 1;
			channel = priv->channel;
			break;

		default:
			band = (u8) (IPW_B_MODE << 6) | 1;
			channel = 9;
			break;
		}

		scan.channels_list[0] = band;
		scan.channels_list[1] = channel;
		ipw_set_scan_type(&scan, 1, IPW_SCAN_PASSIVE_FULL_DWELL_SCAN);

		/* NOTE:  The card will sit on this channel for this time
		 * period.  Scan aborts are timing sensitive and frequently
		 * result in firmware restarts.  As such, it is best to
		 * set a small dwell_time here and just keep re-issuing
		 * scans.  Otherwise fast channel hopping will not actually
		 * hop channels.
		 *
		 * TODO: Move SPEED SCAN support to all modes and bands */
		scan.dwell_time[IPW_SCAN_PASSIVE_FULL_DWELL_SCAN] =
			cpu_to_le16(2000);
	} else {
#endif				/* CONFIG_IPW2200_MONITOR */
		/* If we are roaming, then make this a directed scan for the
		 * current network.  Otherwise, ensure that every other scan
		 * is a fast channel hop scan */
		if ((priv->status & STATUS_ROAMING)
		    || (!(priv->status & STATUS_ASSOCIATED)
			&& (priv->config & CFG_STATIC_ESSID)
			&& (le32_to_cpu(scan.full_scan_index) % 2))) {
			err = ipw_send_ssid(priv, priv->essid, priv->essid_len);
			if (err) {
				IPW_DEBUG_HC("Attempt to send SSID command "
					     "failed.\n");
				goto done;
			}

			scan_type = IPW_SCAN_ACTIVE_BROADCAST_AND_DIRECT_SCAN;
		} else
			scan_type = IPW_SCAN_ACTIVE_BROADCAST_SCAN;

		ipw_add_scan_channels(priv, &scan, scan_type);
#ifdef CONFIG_IPW2200_MONITOR
	}
