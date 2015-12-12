switch(info->EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		ym2413_update_one(info->chip, DUMMYBUF, 0);
		break;
#endif
	case EC_EMU2413:
		OPLL_calc_stereo(info->chip, DUMMYBUF, 0, -1);
		break;
	}
