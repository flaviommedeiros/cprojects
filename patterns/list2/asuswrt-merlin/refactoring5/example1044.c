#ifdef CONFIG_ACPI
if (!acpi_noirq)
		acpi_penalize_isa_irq(irq, active);
	else
#endif
		pirq_penalize_isa_irq(irq, active);
