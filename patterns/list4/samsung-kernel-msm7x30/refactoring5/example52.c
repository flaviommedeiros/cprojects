#ifdef PROP_TXSTATUS
if (bus->dhd->wlfc_state)
				dhd_wlfc_txcomplete(bus->dhd, pkt, FALSE);
			else
#endif
			dhd_txcomplete(bus->dhd, pkt, FALSE);
