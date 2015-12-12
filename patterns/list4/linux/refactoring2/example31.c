#ifdef CONFIG_PPC_RTAS
if (memory_limit)
		first_memblock_size = min_t(u64, first_memblock_size, memory_limit);
