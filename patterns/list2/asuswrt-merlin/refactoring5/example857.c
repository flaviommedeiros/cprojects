#ifdef CONFIG_PPC_PMAC
if (machine_is(powermac)) {
		/* Indicate sleep capability */
		if (par->chip_gen == rage_M3) {
			pmac_call_feature(PMAC_FTR_DEVICE_CAN_WAKE, NULL, 0, 1);
			pmac_set_early_video_resume(aty128_early_resume, par);
		}

		/* Find default mode */
		if (mode_option) {
			if (!mac_find_mode(&var, info, mode_option, 8))
				var = default_var;
		} else {
			if (default_vmode <= 0 || default_vmode > VMODE_MAX)
				default_vmode = VMODE_1024_768_60;

			/* iMacs need that resolution
			 * PowerMac2,1 first r128 iMacs
			 * PowerMac2,2 summer 2000 iMacs
			 * PowerMac4,1 january 2001 iMacs "flower power"
			 */
			if (machine_is_compatible("PowerMac2,1") ||
			    machine_is_compatible("PowerMac2,2") ||
			    machine_is_compatible("PowerMac4,1"))
				default_vmode = VMODE_1024_768_75;

			/* iBook SE */
			if (machine_is_compatible("PowerBook2,2"))
				default_vmode = VMODE_800_600_60;

			/* PowerBook Firewire (Pismo), iBook Dual USB */
			if (machine_is_compatible("PowerBook3,1") ||
			    machine_is_compatible("PowerBook4,1"))
				default_vmode = VMODE_1024_768_60;

			/* PowerBook Titanium */
			if (machine_is_compatible("PowerBook3,2"))
				default_vmode = VMODE_1152_768_60;
	
			if (default_cmode > 16) 
			    default_cmode = CMODE_32;
			else if (default_cmode > 8) 
			    default_cmode = CMODE_16;
			else 
			    default_cmode = CMODE_8;

			if (mac_vmode_to_var(default_vmode, default_cmode, &var))
				var = default_var;
		}
	} else
#endif /* CONFIG_PPC_PMAC */
	{
		if (mode_option)
			if (fb_find_mode(&var, info, mode_option, NULL, 
					 0, &defaultmode, 8) == 0)
				var = default_var;
	}
