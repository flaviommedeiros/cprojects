#ifdef CONFIG_BCM47XX
if (current_cpu_data.cputype == CPU_BCM4710 && (current_cpu_data.processor_id & 0xff) == 0) {
		printk("Enabling BCM4710A0 cache workarounds.\n");
		bcm4710 = 1;
	} else
#endif
		bcm4710 = 0;
