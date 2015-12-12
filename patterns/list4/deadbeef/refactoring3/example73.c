switch(info->EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		ymf262_shutdown(info->chip);
		break;
#endif
	case EC_DBOPL:
		adlib_OPL3_stop(info->chip);
		break;
	}
