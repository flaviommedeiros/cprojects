if (cinfo->irq
#ifndef CONFIG_CYZ_INTR
		&& !cy_is_Z(cinfo)
#endif /* CONFIG_CYZ_INTR */
		)
		free_irq(cinfo->irq, cinfo);
