if (has_isapnp(idx)
#ifndef MSND_CLASSIC
	    || cfg[idx] == SNDRV_AUTO_PORT
#endif
	    ) {
		printk(KERN_INFO LOGNAME ": Assuming PnP mode\n");
		return -ENODEV;
	}
