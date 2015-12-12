switch(EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		info->chip = ym2413_init(clock, rate);
		if (info->chip == NULL)
			return 0;
		//assert_always(info->chip != NULL, "Error creating YM2413 chip");
		ym2413_set_chip_mode(info->chip, info->Mode);

		/* stream system initialize */
		//info->stream = stream_create(device,0,2,rate,info,ym2413_stream_update);

		ym2413_set_update_handler(info->chip, _stream_update, info);
		break;
#endif
	case EC_EMU2413:
		info->chip = OPLL_new(clock, rate);
		if (info->chip == NULL)
			return 0;

		OPLL_SetChipMode(info->chip, info->Mode);
		if (info->Mode)
			OPLL_setPatch(info->chip, vrc7_inst);
		break;
	}
