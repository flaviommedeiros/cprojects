switch(rtm->rtm_type) {
	case RTM_IFINFO:	/* iface going up/down etc. */
		ifm = (struct if_msghdr *)buf;
		syslog(LOG_DEBUG, " RTM_IFINFO: addrs=%x flags=%x index=%hu",
		       ifm->ifm_addrs, ifm->ifm_flags, ifm->ifm_index);
		break;
	case RTM_ADD:	/* Add Route */
		syslog(LOG_DEBUG, " RTM_ADD");
		break;
	case RTM_DELETE:	/* Delete Route */
		syslog(LOG_DEBUG, " RTM_DELETE");
		break;
	case RTM_CHANGE:	/* Change Metrics or flags */
		syslog(LOG_DEBUG, " RTM_CHANGE");
		break;
	case RTM_GET:	/* Report Metrics */
		syslog(LOG_DEBUG, " RTM_GET");
		break;
#ifdef RTM_IFANNOUNCE
	case RTM_IFANNOUNCE:	/* iface arrival/departure */
		ifanm = (struct if_announcemsghdr *)buf;
		syslog(LOG_DEBUG, " RTM_IFANNOUNCE: index=%hu what=%hu ifname=%s",
		       ifanm->ifan_index, ifanm->ifan_what, ifanm->ifan_name);
		break;
#endif
#ifdef RTM_IEEE80211
	case RTM_IEEE80211:	/* IEEE80211 wireless event */
		syslog(LOG_DEBUG, " RTM_IEEE80211");
		break;
#endif
	case RTM_NEWADDR:	/* address being added to iface */
		ifam = (struct ifa_msghdr *)buf;
		syslog(LOG_DEBUG, " RTM_NEWADDR: addrs=%x flags=%x index=%hu",
		       ifam->ifam_addrs, ifam->ifam_flags, ifam->ifam_index);
		p = buf + sizeof(struct ifa_msghdr);
		while(p < buf + len) {
			sa = (struct sockaddr *)p;
			sockaddr_to_string(sa, tmp, sizeof(tmp));
			syslog(LOG_DEBUG, "  %s", tmp);
			p += SA_RLEN(sa);
		}
		if(ifam->ifam_index == ext_if_name_index) {
			should_send_public_address_change_notif = 1;
		}
		break;
	case RTM_DELADDR:	/* address being removed from iface */
		ifam = (struct ifa_msghdr *)buf;
		if(ifam->ifam_index == ext_if_name_index) {
			should_send_public_address_change_notif = 1;
		}
		break;
	default:
		syslog(LOG_DEBUG, "unprocessed RTM message type=%d", rtm->rtm_type);
	}
