#ifdef CONFIG_EARLYFB
if (btext_find_display())
#endif
		register_console(&prom_early_console);
