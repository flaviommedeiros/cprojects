switch(info->EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		return ym3812_read(info->chip, offset & 1);
#endif
	case EC_DBOPL:
		return adlib_OPL2_reg_read(info->chip, offset & 0x01);
	default:
		return 0x00;
	}
