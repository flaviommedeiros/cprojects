if (x2apic_mode
#ifdef CONFIG_X86_UV
		       && apic != &apic_x2apic_uv_x
#endif
		       ) {
		if (x2apic_phys)
			apic = &apic_x2apic_phys;
		else
			apic = &apic_x2apic_cluster;
	}
