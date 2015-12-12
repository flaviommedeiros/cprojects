switch(info->EMU_CORE)
	{
	case EC_MAME:
		sn76496_set_mutemask(info->chip, MuteMask);
		break;
#ifdef ENABLE_ALL_CORES
	case EC_MAXIM:
		SN76489_SetMute(info->chip, ~MuteMask & 0x0F);
		break;
#endif
	}
