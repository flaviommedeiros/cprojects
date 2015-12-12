switch(info->EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		return ymf262_read(info->chip, offset & 3);
#endif
	case EC_DBOPL:
		return adlib_OPL3_reg_read(info->chip, offset & 0x03);
	default:
		return 0x00;
	}
