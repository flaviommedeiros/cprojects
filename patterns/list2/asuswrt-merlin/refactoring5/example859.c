#ifdef CONFIG_NVRAM
if (default_vmode == VMODE_NVRAM) {
		vmode = nvram_read_byte(NV_VMODE);
		if (vmode < 1 || vmode > VMODE_MAX ||
		    control_mac_modes[vmode - 1].m[full] < cmode) {
			sense = read_control_sense(p);
			printk("Monitor sense value = 0x%x, ", sense);
			vmode = mac_map_monitor_sense(sense);
			if (control_mac_modes[vmode - 1].m[full] < cmode)
				vmode = VMODE_640_480_60;
		}
	} else
#endif
	{
		vmode=default_vmode;
		if (control_mac_modes[vmode - 1].m[full] < cmode) {
			if (cmode > CMODE_8)
				cmode--;
			else
				vmode = VMODE_640_480_60;
		}
	}
