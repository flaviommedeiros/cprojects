switch (sdata->vif.type) {
	case NL80211_IFTYPE_AP_VLAN:
	case NL80211_IFTYPE_AP:
		ra = skb->data;
		break;
	case NL80211_IFTYPE_WDS:
		ra = sdata->u.wds.remote_addr;
		break;
#ifdef CONFIG_MAC80211_MESH
	case NL80211_IFTYPE_MESH_POINT:
		/*
		 * XXX: This is clearly broken ... but already was before,
		 * because ieee80211_fill_mesh_addresses() would clear A1
		 * except for multicast addresses.
		 */
		break;
#endif
	case NL80211_IFTYPE_STATION:
		ra = sdata->u.mgd.bssid;
		break;
	case NL80211_IFTYPE_ADHOC:
		ra = skb->data;
		break;
	default:
		break;
	}
