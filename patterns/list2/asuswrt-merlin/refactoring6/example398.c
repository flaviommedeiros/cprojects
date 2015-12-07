if (cinfo->irq
#ifndef CONFIG_CYZ_INTR
		&& !IS_CYC_Z(*cinfo)
#endif /* CONFIG_CYZ_INTR */
		)
		free_irq(cinfo->irq, cinfo);
