#ifdef CONFIG_X86_64
if (!test_and_clear_bit_long(idx, bdata->node_bootmem_map))
#else
		if (!test_and_clear_bit(idx, bdata->node_bootmem_map))
#endif
			BUG();
