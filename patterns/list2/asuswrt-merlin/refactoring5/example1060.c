#ifdef CONFIG_PPC_PMI
if (pmi_dev)
		return set_pmode_pmi(cpu, slow_mode);
	else
#endif
		return set_pmode_reg(cpu, slow_mode);
