switch(info->EMU_CORE)
		{
#ifdef ENABLE_ALL_CORES
		case EC_MAME:
			nes_psg_w(info->chip_apu, offset, data);
			break;
#endif
		case EC_NSFPLAY:
			// NES_APU handles the sqaure waves, NES_DMC the rest
			NES_APU_np_Write(info->chip_apu, 0x4000 | offset, data);
			NES_DMC_np_Write(info->chip_dmc, 0x4000 | offset, data);
			break;
		}
