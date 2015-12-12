switch(info->EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		c6280m_update(info->chip, outputs, samples);
		break;
#endif
	case EC_OOTAKE:
		PSG_Mix(info->chip, outputs, samples);
		break;
	}
