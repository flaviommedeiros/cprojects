#ifdef CONFIG_OF
if (of_have_populated_dt())
		of_irq_init(ux500_dt_irq_match);
	else
#endif
		gic_init(0, 29, dist_base, cpu_base);
