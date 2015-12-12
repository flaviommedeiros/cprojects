switch(info->EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		ym2413_set_mutemask(info->chip, MuteMask);
		break;
#endif
	case EC_EMU2413:
		OPLL_SetMuteMask(info->chip, MuteMask);
		break;
	}
