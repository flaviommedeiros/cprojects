switch(info->EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		device_reset_c6280m(info->chip);
		break;
#endif
	case EC_OOTAKE:
		PSG_ResetVolumeReg(info->chip);
		break;
	}
