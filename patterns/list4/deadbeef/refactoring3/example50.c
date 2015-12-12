switch(info->EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		ym3812_shutdown(info->chip);
		break;
#endif
	case EC_DBOPL:
		adlib_OPL2_stop(info->chip);
		break;
	}
