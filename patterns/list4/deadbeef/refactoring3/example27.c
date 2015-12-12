switch(info->EMU_CORE)
	{
	case EC_MAME:
		ym2612_reset_chip(info->chip);
		break;
#ifdef ENABLE_ALL_CORES
	case EC_GENS:
		YM2612_Reset(info->chip);
		break;
#endif
	}
