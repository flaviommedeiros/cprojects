switch(EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		rate = ay8910_start(&info->chip, clock, chip_type, Flags);
		break;
#endif
	case EC_EMU2149:
		if (Flags & YM2149_PIN26_LOW)
			clock /= 2;
		info->chip = PSG_new(clock, rate);
		if (info->chip == NULL)
			return 0;
		PSG_setVolumeMode((PSG*)info->chip, (chip_type & 0x10) ? 1 : 2);
		PSG_setFlags((PSG*)info->chip, Flags & ~YM2149_PIN26_LOW);
		break;
	}
