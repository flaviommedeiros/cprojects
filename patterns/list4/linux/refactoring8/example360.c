struct resource res[] = {
		{
			.start = baseaddr,
			.end = baseaddr + 0x800 - 1,
			.flags = IORESOURCE_MEM,
#ifndef CONFIG_MACH_TX49XX
		}, {
			.start = irq,
			.flags = IORESOURCE_IRQ,
#endif
		}
	};
