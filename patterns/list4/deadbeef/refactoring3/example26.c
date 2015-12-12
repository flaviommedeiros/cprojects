switch(info->EMU_CORE)
	{
	case EC_MAME:
		ym2612_shutdown(info->chip);
		break;
#ifdef ENABLE_ALL_CORES
	case EC_GENS:
		YM2612_End(info->chip);
		if (info->GensBuf[0x00] != NULL)
		{
			free(info->GensBuf[0x00]);
			info->GensBuf[0x00] = NULL;
			info->GensBuf[0x01] = NULL;
		}
		break;
#endif
	}
