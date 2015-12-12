switch(info->EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		ym2413_reset_chip(info->chip);
		if (info->Mode)
			ym2413_override_patches(info->chip, vrc7_inst);
		break;
#endif
	case EC_EMU2413:
		OPLL_reset(info->chip);
		// EMU2413 doesn't reset the patch data in OPLL_reset
		//if (info->Mode)
		//	OPLL_setPatch(info->chip, vrc7_inst);
		break;
	}
