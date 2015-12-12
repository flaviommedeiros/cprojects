switch(EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		info->chip = ymf262_init(clock,rate);
		//assert_always(info->chip != NULL, "Error creating YMF262 chip");

		//info->stream = stream_create(device,0,4,rate,info,ymf262_stream_update);

		/* YMF262 setup */
		ymf262_set_timer_handler (info->chip, timer_handler_262, info);
		ymf262_set_irq_handler   (info->chip, IRQHandler_262, info);
		ymf262_set_update_handler(info->chip, _stream_update, info);

		//info->timer[0] = timer_alloc(device->machine, timer_callback_262_0, info);
		//info->timer[1] = timer_alloc(device->machine, timer_callback_262_1, info);
		break;
#endif
	case EC_DBOPL:
		info->chip = adlib_OPL3_init(clock, rate, _stream_update, info);
		break;
	}
