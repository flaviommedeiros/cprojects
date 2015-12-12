if (pwdev->iftype != NL80211_IFTYPE_STATION
		#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,37)) || defined(COMPAT_KERNEL_RELEASE)
		&& pwdev->iftype != NL80211_IFTYPE_P2P_CLIENT
		#endif
	) {
		return;
	}
