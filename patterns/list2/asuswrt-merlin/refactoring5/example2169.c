#ifdef CONFIG_ARCH_ACORN
if (machine_is_riscpc()) {
		int i;
		for (i = 0; i < 4; i++)
			tag = memtag(tag, PHYS_OFFSET + (i << 26),
				 params->u1.s.pages_in_bank[i] * PAGE_SIZE);
	} else
#endif
	tag = memtag(tag, PHYS_OFFSET, params->u1.s.nr_pages * PAGE_SIZE);
