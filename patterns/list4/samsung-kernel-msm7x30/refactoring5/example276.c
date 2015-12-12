# ifdef CONFIG_64BIT_PHYS_ADDR
if (cpu_has_64bits)
		uasm_i_scd(p, pte, 0, ptr);
	else
# endif
		UASM_i_SC(p, pte, 0, ptr);
