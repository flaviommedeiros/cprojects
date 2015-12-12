switch(info->EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		ay8910_stop_ym(info->chip);
		break;
#endif
	case EC_EMU2149:
		PSG_delete((PSG*)info->chip);
		break;
	}
