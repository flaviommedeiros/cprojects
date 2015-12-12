switch (amiga_chipset) {
#ifdef CONFIG_FB_AMIGA_OCS
	case CS_OCS:
		strcat(info->fix.id, "OCS");
default_chipset:
		chipset = TAG_OCS;
		maxdepth[TAG_SHRES] = 0;	/* OCS means no SHRES */
		maxdepth[TAG_HIRES] = 4;
		maxdepth[TAG_LORES] = 6;
		maxfmode = TAG_FMODE_1;
		defmode = amiga_vblank == 50 ? DEFMODE_PAL : DEFMODE_NTSC;
		info->fix.smem_len = VIDEOMEMSIZE_OCS;
		break;
#endif /* CONFIG_FB_AMIGA_OCS */

#ifdef CONFIG_FB_AMIGA_ECS
	case CS_ECS:
		strcat(info->fix.id, "ECS");
		chipset = TAG_ECS;
		maxdepth[TAG_SHRES] = 2;
		maxdepth[TAG_HIRES] = 4;
		maxdepth[TAG_LORES] = 6;
		maxfmode = TAG_FMODE_1;
		if (AMIGAHW_PRESENT(AMBER_FF))
			defmode = amiga_vblank == 50 ? DEFMODE_AMBER_PAL
						     : DEFMODE_AMBER_NTSC;
		else
			defmode = amiga_vblank == 50 ? DEFMODE_PAL
						     : DEFMODE_NTSC;
		if (amiga_chip_avail() - CHIPRAM_SAFETY_LIMIT >
		    VIDEOMEMSIZE_ECS_2M)
			info->fix.smem_len = VIDEOMEMSIZE_ECS_2M;
		else
			info->fix.smem_len = VIDEOMEMSIZE_ECS_1M;
		break;
#endif /* CONFIG_FB_AMIGA_ECS */

#ifdef CONFIG_FB_AMIGA_AGA
	case CS_AGA:
		strcat(info->fix.id, "AGA");
		chipset = TAG_AGA;
		maxdepth[TAG_SHRES] = 8;
		maxdepth[TAG_HIRES] = 8;
		maxdepth[TAG_LORES] = 8;
		maxfmode = TAG_FMODE_4;
		defmode = DEFMODE_AGA;
		if (amiga_chip_avail() - CHIPRAM_SAFETY_LIMIT >
		    VIDEOMEMSIZE_AGA_2M)
			info->fix.smem_len = VIDEOMEMSIZE_AGA_2M;
		else
			info->fix.smem_len = VIDEOMEMSIZE_AGA_1M;
		break;
#endif /* CONFIG_FB_AMIGA_AGA */

	default:
#ifdef CONFIG_FB_AMIGA_OCS
		printk("Unknown graphics chipset, defaulting to OCS\n");
		strcat(info->fix.id, "Unknown");
		goto default_chipset;
#else /* CONFIG_FB_AMIGA_OCS */
		err = -ENODEV;
		goto release;
#endif /* CONFIG_FB_AMIGA_OCS */
		break;
	}
