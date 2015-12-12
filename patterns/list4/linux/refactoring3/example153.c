switch (network_mode) {
	case 1:
		priv->ieee->iw_mode = IW_MODE_ADHOC;
		priv->net_dev->type = ARPHRD_ETHER;

		break;
#ifdef CONFIG_IPW2200_MONITOR
	case 2:
		priv->ieee->iw_mode = IW_MODE_MONITOR;
#ifdef CONFIG_IPW2200_RADIOTAP
		priv->net_dev->type = ARPHRD_IEEE80211_RADIOTAP;
#else
		priv->net_dev->type = ARPHRD_IEEE80211;
#endif
		break;
#endif
	default:
	case 0:
		priv->net_dev->type = ARPHRD_ETHER;
		priv->ieee->iw_mode = IW_MODE_INFRA;
		break;
	}
