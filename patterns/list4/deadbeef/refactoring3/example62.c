switch(info->AY_EMU_CORE)
		{
#ifdef ENABLE_ALL_CORES
		case EC_MAME:
			ay8910_set_clock_ym(info->psg, clock);
			break;
#endif
		case EC_EMU2149:
			PSG_set_clock((PSG*)info->psg, clock);
			break;
		}
