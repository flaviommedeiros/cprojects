#ifdef SIC_IMASK0
if (cpumask_test_cpu(0, affinity))
# endif
		bfin_write_SIC_IMASK(mask_bank,
				bfin_read_SIC_IMASK(mask_bank) |
				(1 << mask_bit));
