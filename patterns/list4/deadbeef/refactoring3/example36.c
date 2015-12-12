switch(AY_EMU_CORE)
		{
#ifdef ENABLE_ALL_CORES
		case EC_MAME:
			info->psg = ay8910_start_ym(NULL, CHTYPE_YM2608, ay_clock, &intf->ay8910_intf);
			break;
#endif
		case EC_EMU2149:
			info->psg = PSG_new(ay_clock, *AYrate);
			if (info->psg == NULL)
				return 0;
			PSG_setVolumeMode((PSG*)info->psg, 1);	// YM2149 volume mode
			break;
		}
