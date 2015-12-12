switch(info->EMU_CORE)
	{
	case EC_MAME:
		sn76496_reset(info->chip);
		break;
#ifdef ENABLE_ALL_CORES
	case EC_MAXIM:
		SN76489_Reset((SN76489_Context*)info->chip);
		break;
#endif
	}
