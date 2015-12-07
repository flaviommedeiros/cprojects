#ifdef CONFIG_NVRAM
if (default_vmode <= 0 || default_vmode > VMODE_MAX ||
		    !platinum_reg_init[default_vmode-1])
#endif
			default_vmode = VMODE_CHOOSE;
