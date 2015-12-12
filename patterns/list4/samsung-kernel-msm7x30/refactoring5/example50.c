#ifdef BCMSDIOH_TXGLOM
if (bus->glom_enable && !queue_only) {
		dhd_bcmsdh_glom_clear(bus);
		pkt_cnt = bus->glom_cnt;
	} else
#endif
	{
		pkt_cnt = 1;
	}
