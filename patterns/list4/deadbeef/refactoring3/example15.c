switch(info->EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		break;
#endif
	case EC_EMU2413:
		for (CurChn = 0x00; CurChn < 0x0E; CurChn ++)
			OPLL_set_pan(info->chip, CurChn, PanVals[CurChn]);
		break;
	}
