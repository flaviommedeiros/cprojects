# ifdef CONFIG_64BIT_PHYS_ADDR
if (cpu_has_64bits)
		i_sd(p, pte, 0, ptr);
	else
# endif
		i_SW(p, pte, 0, ptr);
