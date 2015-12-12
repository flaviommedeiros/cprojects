switch(info->EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		ymf262_set_mutemask(info->chip, MuteMask);
		break;
#endif
	case EC_DBOPL:
		adlib_OPL3_set_mute_mask(info->chip, MuteMask);
		break;
	}
