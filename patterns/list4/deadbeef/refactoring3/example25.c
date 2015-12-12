switch(EMU_CORE)
	{
	case EC_MAME:
		//info->chip = ym2612_init(info,clock,rate,timer_handler,IRQHandler);
		info->chip = ym2612_init(info, clock, rate, NULL, NULL, IsVGMInit, ChipFlags);
		break;
#ifdef ENABLE_ALL_CORES
	case EC_GENS:
		if (info->GensBuf[0x00] == NULL)
		{
			info->GensBuf[0x00] = malloc(sizeof(int) * 0x100);
			info->GensBuf[0x01] = info->GensBuf[0x00] + 0x80;
		}
		info->chip = YM2612_Init(clock, rate, 0x00);
		YM2612_SetMute(info->chip, 0x80);	// Disable SSG-EG
		YM2612_SetOptions(ChipFlags);
		break;
#endif
	}
