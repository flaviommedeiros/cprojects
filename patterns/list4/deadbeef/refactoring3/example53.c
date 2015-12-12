switch(info->EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		ym3812_write(info->chip, offset & 1, data);
		break;
#endif
	case EC_DBOPL:
		adlib_OPL2_writeIO(info->chip, offset & 1, data);
		break;
	}
