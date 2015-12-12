void __init set_intr_stub(enum exception_code code, void *handler)
{
	unsigned long addr;
	u8 *vector = (u8 *)(CONFIG_INTERRUPT_VECTOR_BASE + code);
	unsigned long flags;

	addr = (unsigned long) handler - (unsigned long) vector;

	flags = arch_local_cli_save();

	vector[0] = 0xdc;		/* JMP handler */
	vector[1] = addr;
	vector[2] = addr >> 8;
	vector[3] = addr >> 16;
	vector[4] = addr >> 24;
	vector[5] = 0xcb;
	vector[6] = 0xcb;
	vector[7] = 0xcb;

	arch_local_irq_restore(flags);

#ifndef CONFIG_MN10300_CACHE_SNOOP
	mn10300_dcache_flush_inv();
	mn10300_icache_inv();
#endif
}
