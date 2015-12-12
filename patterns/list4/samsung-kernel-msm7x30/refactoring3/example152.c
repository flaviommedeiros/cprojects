switch (cmd) {
		/* Private ioctls (iwpriv) that have not yet been converted
		 * into new wireless extensions API */

	case PRISM2_IOCTL_INQUIRE:
		if (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		else ret = prism2_ioctl_priv_inquire(dev, (int *) wrq->u.name);
		break;

	case PRISM2_IOCTL_MONITOR:
		if (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		else ret = prism2_ioctl_priv_monitor(dev, (int *) wrq->u.name);
		break;

	case PRISM2_IOCTL_RESET:
		if (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		else ret = prism2_ioctl_priv_reset(dev, (int *) wrq->u.name);
		break;

	case PRISM2_IOCTL_WDS_ADD:
		if (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		else ret = prism2_wds_add(local, wrq->u.ap_addr.sa_data, 1);
		break;

	case PRISM2_IOCTL_WDS_DEL:
		if (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		else ret = prism2_wds_del(local, wrq->u.ap_addr.sa_data, 1, 0);
		break;

	case PRISM2_IOCTL_SET_RID_WORD:
		if (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		else ret = prism2_ioctl_priv_set_rid_word(dev,
							  (int *) wrq->u.name);
		break;

#ifndef PRISM2_NO_KERNEL_IEEE80211_MGMT
	case PRISM2_IOCTL_MACCMD:
		if (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		else ret = ap_mac_cmd_ioctl(local, (int *) wrq->u.name);
		break;

	case PRISM2_IOCTL_ADDMAC:
		if (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		else ret = ap_control_add_mac(&local->ap->mac_restrictions,
					      wrq->u.ap_addr.sa_data);
		break;
	case PRISM2_IOCTL_DELMAC:
		if (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		else ret = ap_control_del_mac(&local->ap->mac_restrictions,
					      wrq->u.ap_addr.sa_data);
		break;
	case PRISM2_IOCTL_KICKMAC:
		if (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		else ret = ap_control_kick_mac(local->ap, local->dev,
					       wrq->u.ap_addr.sa_data);
		break;
#endif /* PRISM2_NO_KERNEL_IEEE80211_MGMT */


		/* Private ioctls that are not used with iwpriv;
		 * in SIOCDEVPRIVATE range */

#ifdef PRISM2_DOWNLOAD_SUPPORT
	case PRISM2_IOCTL_DOWNLOAD:
		if (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		else ret = prism2_ioctl_priv_download(local, &wrq->u.data);
		break;
#endif /* PRISM2_DOWNLOAD_SUPPORT */

	case PRISM2_IOCTL_HOSTAPD:
		if (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		else ret = prism2_ioctl_priv_hostapd(local, &wrq->u.data);
		break;

	default:
		ret = -EOPNOTSUPP;
		break;
	}
