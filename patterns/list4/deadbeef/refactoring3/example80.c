switch(info->AY_EMU_CORE)
		{
#ifdef ENABLE_ALL_CORES
		case EC_MAME:
			return ay8910_read_ym(info->psg);
#endif
		case EC_EMU2149:
			return PSG_readIO((PSG*)info->psg);
		}
