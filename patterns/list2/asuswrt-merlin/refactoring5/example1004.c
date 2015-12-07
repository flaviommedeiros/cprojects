#ifdef CONFIG_PCI
if (power_reg) {
			/* Both register bits seem to have the
			 * same effect, so until I figure out
			 * what the difference is...
			 */
			writel(AUXIO_PCIO_CPWR_OFF | AUXIO_PCIO_SPWR_OFF, power_reg);
		} else
#endif /* CONFIG_PCI */
			if (poweroff_method != NULL) {
				poweroff_method();
				/* not reached */
			}
