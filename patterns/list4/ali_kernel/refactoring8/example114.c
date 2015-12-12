static struct of_device_id __devinitdata of_platform_serial_table[] = {
	{ .type = "serial", .compatible = "ns8250",   .data = (void *)PORT_8250, },
	{ .type = "serial", .compatible = "ns16450",  .data = (void *)PORT_16450, },
	{ .type = "serial", .compatible = "ns16550a", .data = (void *)PORT_16550A, },
	{ .type = "serial", .compatible = "ns16550",  .data = (void *)PORT_16550, },
	{ .type = "serial", .compatible = "ns16750",  .data = (void *)PORT_16750, },
	{ .type = "serial", .compatible = "ns16850",  .data = (void *)PORT_16850, },
#ifdef CONFIG_SERIAL_OF_PLATFORM_NWPSERIAL
	{ .type = "serial", .compatible = "ibm,qpace-nwp-serial",
					.data = (void *)PORT_NWPSERIAL, },
#endif
	{ .type = "serial",			      .data = (void *)PORT_UNKNOWN, },
	{ /* end of list */ },
};
