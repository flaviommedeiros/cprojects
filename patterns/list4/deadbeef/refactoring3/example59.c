switch(info->EMU_CORE)
	{
	case EC_MAME:
		switch(offset)
		{
		case 0x00:
			sn76496_write_reg(info->chip, offset & 1, data);
			break;
		case 0x01:
			sn76496_stereo_w(info->chip, offset, data);
			break;
		}
		break;
#ifdef ENABLE_ALL_CORES
	case EC_MAXIM:
		switch(offset)
		{
		case 0x00:
			SN76489_Write((SN76489_Context*)info->chip, data);
			break;
		case 0x01:
			SN76489_GGStereoWrite((SN76489_Context*)info->chip, data);
			break;
		}
		break;
#endif
	}
