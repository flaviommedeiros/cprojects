switch(info->EMU_CORE)
	{
	case EC_MAME:
		ym2612_write(info->chip, offset & 3, data);
		break;
#ifdef ENABLE_ALL_CORES
	case EC_GENS:
		YM2612_Write(info->chip, (unsigned char)(offset & 0x03), data);
		break;
#endif
	}
