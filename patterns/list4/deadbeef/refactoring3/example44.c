switch(info->EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		return c6280m_r(info->chip, offset);
#endif
	case EC_OOTAKE:
		return PSG_Read(info->chip, offset);
	default:
		return 0x00;
	}
