switch(info->EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		ay8910_write_ym(info->chip, offset, data);
		break;
#endif
	case EC_EMU2149:
		PSG_writeIO((PSG*)info->chip, offset, data);
		break;
	}
