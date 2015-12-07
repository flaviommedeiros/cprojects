# ifdef CONFIG_64BIT_PHYS_ADDR
if (cpu_has_64bits)
		i_scd(p, pte, 0, ptr);
	else
# endif
		i_SC(p, pte, 0, ptr);
