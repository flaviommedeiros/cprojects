switch(info->EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		ym2413_update_one(info->chip, outputs, samples);
		break;
#endif
	case EC_EMU2413:
		OPLL_calc_stereo(info->chip, outputs, samples, -1);
		break;
	}
