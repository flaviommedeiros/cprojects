#ifdef	CONFIG_OMAP_MUX_DEBUG
if (debug || warn)
		printk(KERN_WARNING
			"MUX: setup %s (0x%p): 0x%04x -> 0x%04x\n",
			cfg->name, omap_ctrl_base_get() + cfg->mux_reg,
			orig, reg);
