switch(info->EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		// no options for MAME's NES core
		break;
#endif
	case EC_NSFPLAY:
		// shared APU/DMC options
		for (CurOpt = 0; CurOpt < 2; CurOpt ++)
		{
			NES_APU_np_SetOption(info->chip_apu, CurOpt, (NesOptions >> CurOpt) & 0x01);
			NES_DMC_np_SetOption(info->chip_dmc, CurOpt, (NesOptions >> CurOpt) & 0x01);
		}
		// APU-only options
		for (; CurOpt < 4; CurOpt ++)
			NES_APU_np_SetOption(info->chip_apu, CurOpt-2+2, (NesOptions >> CurOpt) & 0x01);
		// DMC-only options
		for (; CurOpt < 10; CurOpt ++)
			NES_DMC_np_SetOption(info->chip_dmc, CurOpt-4+2, (NesOptions >> CurOpt) & 0x01);
		break;
	}
