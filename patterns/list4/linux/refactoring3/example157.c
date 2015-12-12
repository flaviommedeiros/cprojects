switch (wrqu->mode) {
#ifdef CONFIG_IPW2100_MONITOR
	case IW_MODE_MONITOR:
		err = ipw2100_switch_mode(priv, IW_MODE_MONITOR);
		break;
#endif				/* CONFIG_IPW2100_MONITOR */
	case IW_MODE_ADHOC:
		err = ipw2100_switch_mode(priv, IW_MODE_ADHOC);
		break;
	case IW_MODE_INFRA:
	case IW_MODE_AUTO:
	default:
		err = ipw2100_switch_mode(priv, IW_MODE_INFRA);
		break;
	}
