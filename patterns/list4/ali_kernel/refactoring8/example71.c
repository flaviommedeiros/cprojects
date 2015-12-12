static struct devprobe2 parport_probes[] __initdata = {
#ifdef CONFIG_DE620		/* D-Link DE-620 adapter */
	{de620_probe, 0},
#endif
	{NULL, 0},
};
