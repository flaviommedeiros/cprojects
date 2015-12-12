switch(EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		info->chip = ym3812_init(clock & 0x7FFFFFFF,rate);
		//assert_always(info->chip != NULL, "Error creating YM3812 chip");

		//info->stream = stream_create(device,0,1,rate,info,ym3812_stream_update);

		/* YM3812 setup */
		ym3812_set_timer_handler (info->chip, TimerHandler, info);
		ym3812_set_irq_handler   (info->chip, IRQHandler, info);
		ym3812_set_update_handler(info->chip, _stream_update, info);

		//info->timer[0] = timer_alloc(device->machine, timer_callback_0, info);
		//info->timer[1] = timer_alloc(device->machine, timer_callback_1, info);
		break;
#endif
	case EC_DBOPL:
		info->chip = adlib_OPL2_init(clock & 0x7FFFFFFF, rate, _stream_update, info);
		break;
	}
