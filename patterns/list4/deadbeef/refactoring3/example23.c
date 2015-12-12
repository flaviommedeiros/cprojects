switch(info->EMU_CORE)
	{
	case EC_MAME:
		ym2612_update_one(info->chip, DUMMYBUF, 0);
		break;
#ifdef ENABLE_ALL_CORES
	case EC_GENS:
		YM2612_Update(info->chip, DUMMYBUF, 0);
		YM2612_DacAndTimers_Update(info->chip, DUMMYBUF, 0);
		break;
#endif
	}
