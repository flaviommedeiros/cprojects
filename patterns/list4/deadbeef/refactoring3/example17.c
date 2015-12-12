switch(EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		info->chip_apu = device_start_nesapu(clock, rate);
		if (info->chip_apu == NULL)
			return 0;
		
		info->chip_dmc = NULL;
		info->chip_fds = NULL;
		
		info->Memory = (UINT8*)malloc(0x8000);
		memset(info->Memory, 0x00, 0x8000);
		nesapu_set_rom(info->chip_apu, info->Memory - 0x8000);
		break;
#endif
	case EC_NSFPLAY:
		info->chip_apu = NES_APU_np_Create(clock, rate);
		if (info->chip_apu == NULL)
			return 0;
		
		info->chip_dmc = NES_DMC_np_Create(clock, rate);
		if (info->chip_dmc == NULL)
		{
			NES_APU_np_Destroy(info->chip_apu);
			info->chip_apu = NULL;
			return 0;
		}
		
		NES_DMC_np_SetAPU(info->chip_dmc, info->chip_apu);
		
		info->Memory = (UINT8*)malloc(0x8000);
		memset(info->Memory, 0x00, 0x8000);
		NES_DMC_np_SetMemory(info->chip_dmc, info->Memory - 0x8000);
		break;
	}
