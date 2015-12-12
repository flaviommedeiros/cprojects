switch(EMU_CORE)
	{
	case EC_MAME:
		rate = sn76496_start(&info->chip, clock, shiftregwidth, noisetaps,
							negate, stereo, clockdivider, freq0);
		sn76496_freq_limiter(clock & 0x3FFFFFFF, clockdivider, SampleRate);
		break;
#ifdef ENABLE_ALL_CORES
	case EC_MAXIM:
		rate = SampleRate;
		info->chip = SN76489_Init(clock, rate);
		if (info->chip == NULL)
			return 0;
		SN76489_Config((SN76489_Context*)info->chip, noisetaps, shiftregwidth, 0);
		break;
#endif
	}
