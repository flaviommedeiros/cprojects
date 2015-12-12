switch (network_mode) {
	case 1:
		priv->ieee->iw_mode = IW_MODE_ADHOC;
		break;
#ifdef CONFIG_IPW2100_MONITOR
	case 2:
		priv->ieee->iw_mode = IW_MODE_MONITOR;
		break;
#endif
	default:
	case 0:
		priv->ieee->iw_mode = IW_MODE_INFRA;
		break;
	}
