switch (vinfo->mode) {
		case VMODE_480I:
		case VMODE_480CVBS:
		case VMODE_576I:
		case VMODE_576CVBS:
			if (osd_hw.free_scale_mode[index]) {
				osd_hw.field_out_en = 1;

				if (osd_hw.free_scale_data[index].y_end == 719)
					osd_hw.bot_type = 2;
				else if (osd_hw.free_scale_data[index].y_end == 1079)
					osd_hw.bot_type = 3;
				else
					osd_hw.bot_type = 2;
			}
			osd_hw.scan_mode = real_scan_mode = SCAN_MODE_INTERLACE;
			break;
		case VMODE_1080I:
		case VMODE_1080I_50HZ:
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
		case VMODE_1080I_59HZ:
#endif
			if (osd_hw.free_scale_mode[index]) {
				osd_hw.field_out_en = 1;

				if (osd_hw.free_scale_data[index].y_end == 719)
					osd_hw.bot_type = 1;
				else if (osd_hw.free_scale_data[index].y_end == 1079)
					osd_hw.bot_type = 2;
				else
					osd_hw.bot_type = 1;
			}
			osd_hw.scan_mode = real_scan_mode = SCAN_MODE_INTERLACE;
			break;
		case VMODE_4K2K_24HZ:
		case VMODE_4K2K_25HZ:
		case VMODE_4K2K_30HZ:
		case VMODE_4K2K_SMPTE:
			if (osd_hw.fb_for_4k2k) {
				if (osd_hw.free_scale_enable[index])
					osd_hw.scale_workaround = 1;
			}
			osd_hw.field_out_en = 0;
			break;
		default:
			if (osd_hw.free_scale_mode[index])
				osd_hw.field_out_en = 0;
			break;
		}
