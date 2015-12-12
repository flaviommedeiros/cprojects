switch (priv->ieee->iw_mode) {
	case IW_MODE_ADHOC:
		name = "ipw2200-ibss.fw";
		break;
#ifdef CONFIG_IPW2200_MONITOR
	case IW_MODE_MONITOR:
		name = "ipw2200-sniffer.fw";
		break;
#endif
	case IW_MODE_INFRA:
		name = "ipw2200-bss.fw";
		break;
	}
