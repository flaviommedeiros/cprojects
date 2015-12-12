switch(info->AY_EMU_CORE)
		{
#ifdef ENABLE_ALL_CORES
		case EC_MAME:
			ay8910_set_srchg_cb_ym(info->psg, CallbackFunc, AYDataPtr);
			break;
#endif
		case EC_EMU2149:
			break;
		}
