switch (type) {
#ifdef PROP_TXSTATUS
	case WLC_E_FIFO_CREDIT_MAP:
		dhd_os_wlfc_block(dhd_pub);
		dhd_wlfc_event(dhd_pub->info);
		dhd_wlfc_FIFOcreditmap_event(dhd_pub->info, event_data);
		dhd_os_wlfc_unblock(dhd_pub);
		WLFC_DBGMESG(("WLC_E_FIFO_CREDIT_MAP:(AC0,AC1,AC2,AC3),(BC_MC),(OTHER): "
			"(%d,%d,%d,%d),(%d),(%d)\n", event_data[0], event_data[1],
			event_data[2],
			event_data[3], event_data[4], event_data[5]));
		break;
#endif

	case WLC_E_IF:
		{
		dhd_if_event_t *ifevent = (dhd_if_event_t *)event_data;

		/* Ignore the event if NOIF is set */
		if (ifevent->flags & WLC_E_IF_FLAGS_BSSCFG_NOIF) {
			WLFC_DBGMESG(("WLC_E_IF: NO_IF set, event Ignored\r\n"));
			return (BCME_OK);
		}

#ifdef PROP_TXSTATUS
			{
		uint8* ea = pvt_data->eth.ether_dhost;
		WLFC_DBGMESG(("WLC_E_IF: idx:%d, action:%s, iftype:%s, "
		              "[%02x:%02x:%02x:%02x:%02x:%02x]\n",
		              ifevent->ifidx,
		              ((ifevent->action == WLC_E_IF_ADD) ? "ADD":"DEL"),
		              ((ifevent->is_AP == 0) ? "STA":"AP "),
		              ea[0], ea[1], ea[2], ea[3], ea[4], ea[5]));
		(void)ea;

		dhd_os_wlfc_block(dhd_pub);
		if (ifevent->action == WLC_E_IF_CHANGE)
			dhd_wlfc_interface_event(dhd_pub->info,
				eWLFC_MAC_ENTRY_ACTION_UPDATE,
				ifevent->ifidx, ifevent->is_AP, ea);
		else
			dhd_wlfc_interface_event(dhd_pub->info,
				((ifevent->action == WLC_E_IF_ADD) ?
				eWLFC_MAC_ENTRY_ACTION_ADD : eWLFC_MAC_ENTRY_ACTION_DEL),
				ifevent->ifidx, ifevent->is_AP, ea);
		dhd_os_wlfc_unblock(dhd_pub);

		/* dhd already has created an interface by default, for 0 */
		if (ifevent->ifidx == 0)
			break;
			}
#endif /* PROP_TXSTATUS */

#ifdef WL_CFG80211
			if (wl_cfg80211_is_progress_ifchange()) {
				DHD_ERROR(("%s:  ifidx %d for %s action %d\n",
					__FUNCTION__, ifevent->ifidx,
					event->ifname, ifevent->action));
				if (ifevent->action == WLC_E_IF_ADD ||
					ifevent->action == WLC_E_IF_CHANGE)
					wl_cfg80211_notify_ifchange();
				return (BCME_OK);
			}
#endif /* WL_CFG80211 */
		if (ifevent->ifidx > 0 && ifevent->ifidx < DHD_MAX_IFS) {
					if (ifevent->action == WLC_E_IF_ADD) {
						if (dhd_add_if(dhd_pub->info, ifevent->ifidx,
							NULL, event->ifname,
							event->addr.octet,
							ifevent->flags, ifevent->bssidx)) {
							DHD_ERROR(("%s: dhd_add_if failed!!"
									" ifidx: %d for %s\n",
									__FUNCTION__,
									ifevent->ifidx,
									event->ifname));
							return (BCME_ERROR);
						}
					}
					else if (ifevent->action == WLC_E_IF_DEL)
						dhd_del_if(dhd_pub->info, ifevent->ifidx);
		} else {
#ifndef PROP_TXSTATUS
			DHD_ERROR(("%s: Invalid ifidx %d for %s\n",
			           __FUNCTION__, ifevent->ifidx, event->ifname));
#endif /* !PROP_TXSTATUS */
		}
			}
			/* send up the if event: btamp user needs it */
			*ifidx = dhd_ifname2idx(dhd_pub->info, event->ifname);
			/* push up to external supp/auth */
			dhd_event(dhd_pub->info, (char *)pvt_data, evlen, *ifidx);
		break;


#ifdef WLMEDIA_HTSF
	case WLC_E_HTSFSYNC:
		htsf_update(dhd_pub->info, event_data);
		break;
#endif /* WLMEDIA_HTSF */
	case WLC_E_NDIS_LINK: {
		uint32 temp = hton32(WLC_E_LINK);

		memcpy((void *)(&pvt_data->event.event_type), &temp,
		       sizeof(pvt_data->event.event_type));
	}
	case WLC_E_PFN_NET_FOUND:
	case WLC_E_PFN_NET_LOST:
		break;
	case WLC_E_PFN_BSSID_NET_FOUND:
	case WLC_E_PFN_BSSID_NET_LOST:
	case WLC_E_PFN_BEST_BATCHING:
#ifdef PNO_SUPPORT
		dhd_pno_event_handler(dhd_pub, event, (void *)event_data);
#endif
		break;
		/* These are what external supplicant/authenticator wants */
		/* fall through */
	case WLC_E_LINK:
	case WLC_E_DEAUTH:
	case WLC_E_DEAUTH_IND:
	case WLC_E_DISASSOC:
	case WLC_E_DISASSOC_IND:
		DHD_EVENT(("%s: Link event %d, flags %x, status %x\n",
		           __FUNCTION__, type, flags, status));
		/* fall through */
	default:
		*ifidx = dhd_ifname2idx(dhd_pub->info, event->ifname);
		/* push up to external supp/auth */
		dhd_event(dhd_pub->info, (char *)pvt_data, evlen, *ifidx);
		DHD_TRACE(("%s: MAC event %d, flags %x, status %x\n",
		           __FUNCTION__, type, flags, status));
		BCM_REFERENCE(flags);
		BCM_REFERENCE(status);

		/* put it back to WLC_E_NDIS_LINK */
		if (type == WLC_E_NDIS_LINK) {
			uint32 temp;

			temp = ntoh32_ua((void *)&event->event_type);
			DHD_TRACE(("Converted to WLC_E_LINK type %d\n", temp));

			temp = ntoh32(WLC_E_NDIS_LINK);
			memcpy((void *)(&pvt_data->event.event_type), &temp,
			       sizeof(pvt_data->event.event_type));
		}
		break;
	}
