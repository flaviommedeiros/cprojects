switch(info->EMU_CORE)
	{
	case EC_MAME:
		break;
#ifdef ENABLE_ALL_CORES
	case EC_MAXIM:
		SN76489_SetPanning(info->chip, PanVals[0x00], PanVals[0x01], PanVals[0x02], PanVals[0x03]);
		break;
#endif
	}
