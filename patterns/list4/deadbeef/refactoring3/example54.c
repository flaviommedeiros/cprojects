switch(info->EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		opl_set_mute_mask(info->chip, MuteMask);
		break;
#endif
	case EC_DBOPL:
		adlib_OPL2_set_mute_mask(info->chip, MuteMask);
		break;
	}
