switch (sdata->vif.type) {
	case NL80211_IFTYPE_AP_VLAN:
		rcu_read_lock();
		sta = rcu_dereference(sdata->u.vlan.sta);
		if (sta) {
			fc |= cpu_to_le16(IEEE80211_FCTL_FROMDS | IEEE80211_FCTL_TODS);
			/* RA TA DA SA */
			memcpy(hdr.addr1, sta->sta.addr, ETH_ALEN);
			memcpy(hdr.addr2, sdata->vif.addr, ETH_ALEN);
			memcpy(hdr.addr3, skb->data, ETH_ALEN);
			memcpy(hdr.addr4, skb->data + ETH_ALEN, ETH_ALEN);
			hdrlen = 30;
			authorized = test_sta_flag(sta, WLAN_STA_AUTHORIZED);
			wme_sta = test_sta_flag(sta, WLAN_STA_WME);
		}
		rcu_read_unlock();
		if (sta)
			break;
		/* fall through */
	case NL80211_IFTYPE_AP:
		fc |= cpu_to_le16(IEEE80211_FCTL_FROMDS);
		/* DA BSSID SA */
		memcpy(hdr.addr1, skb->data, ETH_ALEN);
		memcpy(hdr.addr2, sdata->vif.addr, ETH_ALEN);
		memcpy(hdr.addr3, skb->data + ETH_ALEN, ETH_ALEN);
		hdrlen = 24;
		break;
	case NL80211_IFTYPE_WDS:
		fc |= cpu_to_le16(IEEE80211_FCTL_FROMDS | IEEE80211_FCTL_TODS);
		/* RA TA DA SA */
		memcpy(hdr.addr1, sdata->u.wds.remote_addr, ETH_ALEN);
		memcpy(hdr.addr2, sdata->vif.addr, ETH_ALEN);
		memcpy(hdr.addr3, skb->data, ETH_ALEN);
		memcpy(hdr.addr4, skb->data + ETH_ALEN, ETH_ALEN);
		hdrlen = 30;
		break;
#ifdef CONFIG_MAC80211_MESH
	case NL80211_IFTYPE_MESH_POINT:
		if (!sdata->u.mesh.mshcfg.dot11MeshTTL) {
			/* Do not send frames with mesh_ttl == 0 */
			sdata->u.mesh.mshstats.dropped_frames_ttl++;
			ret = NETDEV_TX_OK;
			goto fail;
		}
		rcu_read_lock();
		if (!is_multicast_ether_addr(skb->data))
			mppath = mpp_path_lookup(skb->data, sdata);

		/*
		 * Use address extension if it is a packet from
		 * another interface or if we know the destination
		 * is being proxied by a portal (i.e. portal address
		 * differs from proxied address)
		 */
		if (compare_ether_addr(sdata->vif.addr,
				       skb->data + ETH_ALEN) == 0 &&
		    !(mppath && compare_ether_addr(mppath->mpp, skb->data))) {
			hdrlen = ieee80211_fill_mesh_addresses(&hdr, &fc,
					skb->data, skb->data + ETH_ALEN);
			rcu_read_unlock();
			meshhdrlen = ieee80211_new_mesh_header(&mesh_hdr,
					sdata, NULL, NULL);
		} else {
			int is_mesh_mcast = 1;
			const u8 *mesh_da;

			if (is_multicast_ether_addr(skb->data))
				/* DA TA mSA AE:SA */
				mesh_da = skb->data;
			else {
				static const u8 bcast[ETH_ALEN] =
					{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
				if (mppath) {
					/* RA TA mDA mSA AE:DA SA */
					mesh_da = mppath->mpp;
					is_mesh_mcast = 0;
				} else {
					/* DA TA mSA AE:SA */
					mesh_da = bcast;
				}
			}
			hdrlen = ieee80211_fill_mesh_addresses(&hdr, &fc,
					mesh_da, sdata->vif.addr);
			rcu_read_unlock();
			if (is_mesh_mcast)
				meshhdrlen =
					ieee80211_new_mesh_header(&mesh_hdr,
							sdata,
							skb->data + ETH_ALEN,
							NULL);
			else
				meshhdrlen =
					ieee80211_new_mesh_header(&mesh_hdr,
							sdata,
							skb->data,
							skb->data + ETH_ALEN);

		}
		break;
#endif
	case NL80211_IFTYPE_STATION:
		if (sdata->wdev.wiphy->flags & WIPHY_FLAG_SUPPORTS_TDLS) {
			bool tdls_peer = false;

			rcu_read_lock();
			sta = sta_info_get(sdata, skb->data);
			if (sta) {
				authorized = test_sta_flag(sta,
							WLAN_STA_AUTHORIZED);
				wme_sta = test_sta_flag(sta, WLAN_STA_WME);
				tdls_peer = test_sta_flag(sta,
							 WLAN_STA_TDLS_PEER);
				tdls_auth = test_sta_flag(sta,
						WLAN_STA_TDLS_PEER_AUTH);
			}
			rcu_read_unlock();

			/*
			 * If the TDLS link is enabled, send everything
			 * directly. Otherwise, allow TDLS setup frames
			 * to be transmitted indirectly.
			 */
			tdls_direct = tdls_peer && (tdls_auth ||
				 !(ethertype == ETH_P_TDLS && skb->len > 14 &&
				   skb->data[14] == WLAN_TDLS_SNAP_RFTYPE));
		}

		if (tdls_direct) {
			/* link during setup - throw out frames to peer */
			if (!tdls_auth) {
				ret = NETDEV_TX_OK;
				goto fail;
			}

			/* DA SA BSSID */
			memcpy(hdr.addr1, skb->data, ETH_ALEN);
			memcpy(hdr.addr2, skb->data + ETH_ALEN, ETH_ALEN);
			memcpy(hdr.addr3, sdata->u.mgd.bssid, ETH_ALEN);
			hdrlen = 24;
		}  else if (sdata->u.mgd.use_4addr &&
			    cpu_to_be16(ethertype) != sdata->control_port_protocol) {
			fc |= cpu_to_le16(IEEE80211_FCTL_FROMDS |
					  IEEE80211_FCTL_TODS);
			/* RA TA DA SA */
			memcpy(hdr.addr1, sdata->u.mgd.bssid, ETH_ALEN);
			memcpy(hdr.addr2, sdata->vif.addr, ETH_ALEN);
			memcpy(hdr.addr3, skb->data, ETH_ALEN);
			memcpy(hdr.addr4, skb->data + ETH_ALEN, ETH_ALEN);
			hdrlen = 30;
		} else {
			fc |= cpu_to_le16(IEEE80211_FCTL_TODS);
			/* BSSID SA DA */
			memcpy(hdr.addr1, sdata->u.mgd.bssid, ETH_ALEN);
			memcpy(hdr.addr2, skb->data + ETH_ALEN, ETH_ALEN);
			memcpy(hdr.addr3, skb->data, ETH_ALEN);
			hdrlen = 24;
		}
		break;
	case NL80211_IFTYPE_ADHOC:
		/* DA SA BSSID */
		memcpy(hdr.addr1, skb->data, ETH_ALEN);
		memcpy(hdr.addr2, skb->data + ETH_ALEN, ETH_ALEN);
		memcpy(hdr.addr3, sdata->u.ibss.bssid, ETH_ALEN);
		hdrlen = 24;
		break;
	default:
		ret = NETDEV_TX_OK;
		goto fail;
	}
