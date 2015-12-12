switch(info->EMU_CORE)
	{
	case EC_MAME:
		ym2612_set_mutemask(info->chip, MuteMask);
		break;
#ifdef ENABLE_ALL_CORES
	case EC_GENS:
		YM2612_SetMute(info->chip, (int)MuteMask);
		break;
#endif
	}
