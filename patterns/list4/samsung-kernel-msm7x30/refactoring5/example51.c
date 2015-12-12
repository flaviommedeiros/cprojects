#ifdef PROP_TXSTATUS
if (bus->dhd->wlfc_state) {
		dhd_os_sdunlock(bus->dhd);
		dhd_wlfc_txcomplete(bus->dhd, pkt, ret == 0);
		dhd_os_sdlock(bus->dhd);
	} else {
#endif /* PROP_TXSTATUS */
#ifdef SDTEST
	if (chan != SDPCM_TEST_CHANNEL) {
		dhd_txcomplete(bus->dhd, pkt, ret != 0);
	}
#else /* SDTEST */
	dhd_txcomplete(bus->dhd, pkt, ret != 0);
#endif /* SDTEST */
	if (free_pkt)
		PKTFREE(osh, pkt, TRUE);

#ifdef PROP_TXSTATUS
	}
