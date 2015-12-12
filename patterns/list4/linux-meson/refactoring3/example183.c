switch (cmd) {
#ifdef CONFIG_TI_CPTS
	case SIOCSHWTSTAMP:
		return cpsw_hwtstamp_ioctl(dev, req);
#endif
	case SIOCGMIIPHY:
		data->phy_id = priv->slaves[slave_no].phy->addr;
		break;
	default:
		return -ENOTSUPP;
	}
