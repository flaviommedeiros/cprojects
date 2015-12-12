switch(info->EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		ym2413_shutdown(info->chip);
		break;
#endif
	case EC_EMU2413:
		OPLL_delete(info->chip);
		break;
	}
