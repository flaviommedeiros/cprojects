switch(info->EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		ymf262_reset_chip(info->chip);
		break;
#endif
	case EC_DBOPL:
		adlib_OPL3_reset(info->chip);
		break;
	}
