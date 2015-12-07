if (c->extended_cpuid_level >= 0x80000008) {
		u32 eax = cpuid_eax(0x80000008);

		c->x86_virt_bits = (eax >> 8) & 0xff;
		c->x86_phys_bits = eax & 0xff;
	}
#ifdef CONFIG_X86_32
	else if (cpu_has(c, X86_FEATURE_PAE) || cpu_has(c, X86_FEATURE_PSE36))
		c->x86_phys_bits = 36;
#endif
