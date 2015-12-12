switch(info->EMU_CORE)
	{
	case EC_MAME:
		SN76496Update(info->chip, outputs, samples);
		break;
#ifdef ENABLE_ALL_CORES
	case EC_MAXIM:
		SN76489_Update((SN76489_Context*)info->chip, outputs, samples);
		break;
#endif
	}
