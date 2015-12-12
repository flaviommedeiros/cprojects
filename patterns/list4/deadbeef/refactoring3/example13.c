switch(info->EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		ym2413_write(info->chip, offset & 1, data);
		break;
#endif
	case EC_EMU2413:
		OPLL_writeIO(info->chip, offset & 1, data);
		break;
	}
