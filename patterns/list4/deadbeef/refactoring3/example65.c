switch(info->AY_EMU_CORE)
		{
#ifdef ENABLE_ALL_CORES
		case EC_MAME:
			ay8910_reset_ym(info->psg);
			break;
#endif
		case EC_EMU2149:
			PSG_reset((PSG*)info->psg);
			break;
		}