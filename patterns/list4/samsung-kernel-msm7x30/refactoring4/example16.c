#ifdef CUSTOMER_HW4
if (bus->dpc_sched || bus->rxskip || pktq_len(&bus->txq) || bus->readframes)
#else
		if (bus->dpc_sched || bus->rxskip || pktq_len(&bus->txq))
#endif /* CUSTOMER_HW4 */
			return BCME_BUSY;
