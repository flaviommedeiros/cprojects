static struct bfin_pint_regs * const pint[NR_PINT_SYS_IRQS] = {
	(struct bfin_pint_regs *)PINT0_MASK_SET,
	(struct bfin_pint_regs *)PINT1_MASK_SET,
	(struct bfin_pint_regs *)PINT2_MASK_SET,
	(struct bfin_pint_regs *)PINT3_MASK_SET,
#ifdef CONFIG_BF60x
	(struct bfin_pint_regs *)PINT4_MASK_SET,
	(struct bfin_pint_regs *)PINT5_MASK_SET,
#endif
};
