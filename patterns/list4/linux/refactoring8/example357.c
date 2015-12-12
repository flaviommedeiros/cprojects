static struct resource pnx833x_ethernet_resources[] = {
	[0] = {
		.start = PNX8335_IP3902_PORTS_START,
		.end   = PNX8335_IP3902_PORTS_END,
		.flags = IORESOURCE_MEM,
	},
#ifdef CONFIG_SOC_PNX8335
	[1] = {
		.start = PNX8335_PIC_ETHERNET_INT,
		.end   = PNX8335_PIC_ETHERNET_INT,
		.flags = IORESOURCE_IRQ,
	},
#endif
};
