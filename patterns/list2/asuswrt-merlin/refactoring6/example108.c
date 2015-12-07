if (set80211priv(drv,
#ifdef MADWIFI_NG
			 IEEE80211_IOCTL_STA_STATS,
#else /* MADWIFI_NG */
			 IEEE80211_IOCTL_GETSTASTATS,
#endif /* MADWIFI_NG */
			 &stats, sizeof(stats))) {
		wpa_printf(MSG_DEBUG, "%s: Failed to fetch STA stats (addr "
			   MACSTR ")", __func__, MAC2STR(addr));
		if (memcmp(addr, drv->acct_mac, ETH_ALEN) == 0) {
			memcpy(data, &drv->acct_data, sizeof(*data));
			return 0;
		}

		printf("Failed to get station stats information element.\n");
		return -1;
	}
