switch (priv->ieee->iw_mode) {
	case IW_MODE_ADHOC:
		fw_name = IPW2100_FW_NAME("-i");
		break;
#ifdef CONFIG_IPW2100_MONITOR
	case IW_MODE_MONITOR:
		fw_name = IPW2100_FW_NAME("-p");
		break;
#endif
	case IW_MODE_INFRA:
	default:
		fw_name = IPW2100_FW_NAME("");
		break;
	}
