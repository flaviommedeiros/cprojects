switch (mode) {
	case IW_MODE_INFRA:
		priv->net_dev->type = ARPHRD_ETHER;
		break;
	case IW_MODE_ADHOC:
		priv->net_dev->type = ARPHRD_ETHER;
		break;
#ifdef CONFIG_IPW2100_MONITOR
	case IW_MODE_MONITOR:
		priv->last_mode = priv->ieee->iw_mode;
		priv->net_dev->type = ARPHRD_IEEE80211_RADIOTAP;
		break;
#endif				/* CONFIG_IPW2100_MONITOR */
	}
