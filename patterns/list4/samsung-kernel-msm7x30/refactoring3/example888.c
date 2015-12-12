switch (sdata->vif.type) {
			case NL80211_IFTYPE_AP:
				sdata->vif.bss_conf.enable_beacon =
					!!sdata->u.ap.beacon;
				break;
			case NL80211_IFTYPE_ADHOC:
				sdata->vif.bss_conf.enable_beacon =
					!!sdata->u.ibss.presp;
				break;
#ifdef CONFIG_MAC80211_MESH
			case NL80211_IFTYPE_MESH_POINT:
				sdata->vif.bss_conf.enable_beacon =
					!!sdata->u.mesh.mesh_id_len;
				break;
#endif
			default:
				/* not reached */
				WARN_ON(1);
				break;
			}
