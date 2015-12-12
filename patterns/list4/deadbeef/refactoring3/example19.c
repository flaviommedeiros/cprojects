switch(info->EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		device_reset_nesapu(info->chip_apu);
		break;
#endif
	case EC_NSFPLAY:
		NES_APU_np_Reset(info->chip_apu);
		NES_DMC_np_Reset(info->chip_dmc);
		break;
	}
