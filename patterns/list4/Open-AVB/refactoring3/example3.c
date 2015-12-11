switch (cmd) {
#ifdef SIOCGMIIPHY
	case SIOCGMIIPHY:
	case SIOCGMIIREG:
	case SIOCSMIIREG:
		return igb_mii_ioctl(netdev, ifr, cmd);
#endif
#ifdef HAVE_PTP_1588_CLOCK
#ifdef SIOCGHWTSTAMP
	case SIOCGHWTSTAMP:
		return igb_ptp_get_ts_config(netdev, ifr);
#endif
	case SIOCSHWTSTAMP:
		return igb_ptp_set_ts_config(netdev, ifr);
#endif /* HAVE_PTP_1588_CLOCK */
#ifdef ETHTOOL_OPS_COMPAT
	case SIOCETHTOOL:
		return ethtool_ioctl(ifr);
#endif
	default:
		return -EOPNOTSUPP;
	}
