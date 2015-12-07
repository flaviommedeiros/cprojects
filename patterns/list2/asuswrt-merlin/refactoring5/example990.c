# ifdef CONFIG_64BIT_PHYS_ADDR
if (cpu_has_64bits)
		i_lld(p, pte, 0, ptr);
	else
# endif
		i_LL(p, pte, 0, ptr);
