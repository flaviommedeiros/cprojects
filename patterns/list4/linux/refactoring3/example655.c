switch (sdata->vif.type) {
	case NL80211_IFTYPE_AP:
		err = ieee80211_assign_beacon(sdata, sdata->u.ap.next_beacon,
					      NULL);
		kfree(sdata->u.ap.next_beacon);
		sdata->u.ap.next_beacon = NULL;

		if (err < 0)
			return err;
		*changed |= err;
		break;
	case NL80211_IFTYPE_ADHOC:
		err = ieee80211_ibss_finish_csa(sdata);
		if (err < 0)
			return err;
		*changed |= err;
		break;
#ifdef CONFIG_MAC80211_MESH
	case NL80211_IFTYPE_MESH_POINT:
		err = ieee80211_mesh_finish_csa(sdata);
		if (err < 0)
			return err;
		*changed |= err;
		break;
#endif
	default:
		WARN_ON(1);
		return -EINVAL;
	}
