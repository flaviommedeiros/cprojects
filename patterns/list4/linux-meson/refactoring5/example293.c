#ifdef CONFIG_OF
if (of_have_populated_dt())
		irqchip_init();
	else
#endif
		gic_init(0, 29, dist_base, cpu_base);
