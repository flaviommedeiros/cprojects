switch(info->EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		ay8910_set_mute_mask_ym(info->chip, MuteMask);
		break;
#endif
	case EC_EMU2149:
		PSG_setMask((PSG*)info->chip, MuteMask);
		break;
	}
