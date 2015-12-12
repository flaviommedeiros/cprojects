switch(info->EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		c6280m_w(info->chip, offset, data);
		break;
#endif
	case EC_OOTAKE:
		PSG_Write(info->chip, offset, data);
		break;
	}
