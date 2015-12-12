#ifdef CONFIG_MACH_ARIESVE
if (id == P_EBI1_CLK || id == P_PBUS_CLK)
#else
	if (id == P_EBI1_CLK || id == P_EBI1_FIXED_CLK)
#endif
		return;
