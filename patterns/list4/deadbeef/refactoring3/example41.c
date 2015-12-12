switch(EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		rate = (clock & 0x7FFFFFFF)/16;
		if (((CHIP_SAMPLING_MODE & 0x01) && rate < CHIP_SAMPLE_RATE) ||
			CHIP_SAMPLING_MODE == 0x02)
			rate = CHIP_SAMPLE_RATE;
		
		info->chip = device_start_c6280m(clock, rate);
		if (info->chip == NULL)
			return 0;
		break;
#endif
	case EC_OOTAKE:
		rate = SampleRate;
		info->chip = PSG_Init(clock, rate);
		if (info->chip == NULL)
			return 0;
		break;
	}
