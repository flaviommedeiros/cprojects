switch(info->EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		ymf262_update_one(info->chip, DUMMYBUF, 0);
		break;
#endif
	case EC_DBOPL:
		adlib_OPL3_getsample(info->chip, DUMMYBUF, 0);
		break;
	}
