#ifdef CONFIG_MIPS_MT_SMTC
if ((read_c0_tcbind() & TCBIND_CURTC) == 0)
#endif /* CONFIG_MIPS_MT_SMTC */
	cpu_probe();
