static struct platform_device *m527x_devices[] __initdata = {
	&m527x_uart,
	&m527x_fec[0],
#ifdef CONFIG_FEC2
	&m527x_fec[1],
#endif
};
