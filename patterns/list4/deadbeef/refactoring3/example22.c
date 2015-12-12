switch(info->EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		nesapu_set_mute_mask(info->chip_apu, MuteMask);
		break;
#endif
	case EC_NSFPLAY:
		NES_APU_np_SetMask(info->chip_apu, (MuteMask & 0x03) >> 0);
		NES_DMC_np_SetMask(info->chip_dmc, (MuteMask & 0x1C) >> 2);
		break;
	}
