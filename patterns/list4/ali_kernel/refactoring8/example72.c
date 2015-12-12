static struct devprobe2 tr_probes2[] __initdata = {
#ifdef CONFIG_SMCTR
	{smctr_probe, 0},
#endif
	{NULL, 0},
};
