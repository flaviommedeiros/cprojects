switch(info->EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		c6280m_set_mute_mask(info->chip, MuteMask);
		break;
#endif
	case EC_OOTAKE:
		PSG_SetMuteMask(info->chip, MuteMask);
		break;
	}
