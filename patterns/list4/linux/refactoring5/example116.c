#ifdef	CONFIG_X86_IO_APIC
if (virq + i < nr_legacy_irqs() && legacy_irq_data[virq + i])
			data = legacy_irq_data[virq + i];
		else
#endif
			data = alloc_apic_chip_data(node);
