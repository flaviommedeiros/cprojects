switch(info->EMU_CORE)
	{
	case EC_MAME:
		return ym2612_read(info->chip, offset & 3);
#ifdef ENABLE_ALL_CORES
	case EC_GENS:
		return YM2612_Read(info->chip);
#endif
	default:
		return 0x00;
	}
