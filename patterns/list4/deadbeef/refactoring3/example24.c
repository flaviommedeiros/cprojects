switch(info->EMU_CORE)
	{
	case EC_MAME:
		ym2612_update_one(info->chip, outputs, samples);
		break;
#ifdef ENABLE_ALL_CORES
	case EC_GENS:
		YM2612_ClearBuffer(info->GensBuf, samples);
		YM2612_Update(info->chip, info->GensBuf, samples);
		YM2612_DacAndTimers_Update(info->chip, info->GensBuf, samples);
		for (i = 0x00; i < samples; i ++)
		{
			outputs[0x00][i] = (stream_sample_t)info->GensBuf[0x00][i];
			outputs[0x01][i] = (stream_sample_t)info->GensBuf[0x01][i];
		}
		break;
#endif
	}
