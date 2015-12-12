# ifdef CONFIG_PHYS_ADDR_T_64BIT
if (cpu_has_64bits)
		uasm_i_sd(p, pte, 0, ptr);
	else
# endif
		UASM_i_SW(p, pte, 0, ptr);
