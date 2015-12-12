#ifdef CONFIG_CEVT_GIC
if (!gic_present)
#endif
	clockevents_register_device(cd);
