switch(info->EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		ym3812_update_one(info->chip, outputs, samples);
		break;
#endif
	case EC_DBOPL:
		adlib_OPL2_getsample(info->chip, outputs, samples);
		break;
	}
