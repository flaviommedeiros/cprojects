switch(info->EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		nes_psg_update_sound(info->chip_apu, outputs, samples);
		break;
#endif
	case EC_NSFPLAY:
		for (CurSmpl = 0x00; CurSmpl < samples; CurSmpl ++)
		{
			NES_APU_np_Render(info->chip_apu, &Buffer[0]);
			NES_DMC_np_Render(info->chip_dmc, &Buffer[2]);
			outputs[0][CurSmpl] = Buffer[0] + Buffer[2];
			outputs[1][CurSmpl] = Buffer[1] + Buffer[3];
		}
		break;
	}
