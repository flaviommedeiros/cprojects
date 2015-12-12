switch (sdata->vif.type) {
	case NL80211_IFTYPE_AP_VLAN:
		sta = rcu_dereference(sdata->u.vlan.sta);
		if (sta) {
			*sta_out = sta;
			return 0;
		} else if (sdata->wdev.use_4addr) {
			return -ENOLINK;
		}
		/* fall through */
	case NL80211_IFTYPE_AP:
	case NL80211_IFTYPE_OCB:
	case NL80211_IFTYPE_ADHOC:
		if (is_multicast_ether_addr(skb->data)) {
			*sta_out = ERR_PTR(-ENOENT);
			return 0;
		}
		sta = sta_info_get_bss(sdata, skb->data);
		break;
	case NL80211_IFTYPE_WDS:
		sta = sta_info_get(sdata, sdata->u.wds.remote_addr);
		break;
#ifdef CONFIG_MAC80211_MESH
	case NL80211_IFTYPE_MESH_POINT:
		/* determined much later */
		*sta_out = NULL;
		return 0;
#endif
	case NL80211_IFTYPE_STATION:
		if (sdata->wdev.wiphy->flags & WIPHY_FLAG_SUPPORTS_TDLS) {
			sta = sta_info_get(sdata, skb->data);
			if (sta) {
				bool tdls_peer, tdls_auth;

				tdls_peer = test_sta_flag(sta,
							  WLAN_STA_TDLS_PEER);
				tdls_auth = test_sta_flag(sta,
						WLAN_STA_TDLS_PEER_AUTH);

				if (tdls_peer && tdls_auth) {
					*sta_out = sta;
					return 0;
				}

				/*
				 * TDLS link during setup - throw out frames to
				 * peer. Allow TDLS-setup frames to unauthorized
				 * peers for the special case of a link teardown
				 * after a TDLS sta is removed due to being
				 * unreachable.
				 */
				if (tdls_peer && !tdls_auth &&
				    !ieee80211_is_tdls_setup(skb))
					return -EINVAL;
			}

		}

		sta = sta_info_get(sdata, sdata->u.mgd.bssid);
		if (!sta)
			return -ENOLINK;
		break;
	default:
		return -EINVAL;
	}
