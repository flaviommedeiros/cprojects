switch(info->EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		ymf262_write(info->chip, offset & 3, data);
		break;
#endif
	case EC_DBOPL:
		adlib_OPL3_writeIO(info->chip, offset & 3, data);
		break;
	}
