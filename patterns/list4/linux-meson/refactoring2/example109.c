#ifdef CONFIG_CEVT_GIC
if (!gic_present)
#endif
		cd->event_handler(cd);
