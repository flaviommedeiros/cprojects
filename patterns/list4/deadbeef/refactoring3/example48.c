switch(info->EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		ym3812_update_one(info->chip, DUMMYBUF, 0);
		break;
#endif
	case EC_DBOPL:
		adlib_OPL2_getsample(info->chip, DUMMYBUF, 0);
		break;
	}