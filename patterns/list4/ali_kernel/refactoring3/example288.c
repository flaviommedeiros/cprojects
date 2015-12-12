switch (ethcmd) {
	case ETHTOOL_GDRVINFO:
		info.cmd = ethcmd;
		snprintf(info.driver, sizeof(info.driver), "p80211_%s",
			 wlandev->nsdname);
		snprintf(info.version, sizeof(info.version), "%s",
			 WLAN_RELEASE);

		if (copy_to_user(useraddr, &info, sizeof(info)))
			return -EFAULT;
		return 0;
#ifdef ETHTOOL_GLINK
	case ETHTOOL_GLINK:
		edata.cmd = ethcmd;

		if (wlandev->linkstatus &&
		    (wlandev->macmode != WLAN_MACMODE_NONE)) {
			edata.data = 1;
		} else {
			edata.data = 0;
		}

		if (copy_to_user(useraddr, &edata, sizeof(edata)))
			return -EFAULT;
		return 0;
	}
