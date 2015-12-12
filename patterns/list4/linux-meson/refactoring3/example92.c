switch (vinfo->mode) {
		case VMODE_480I:
		case VMODE_480CVBS:
		case VMODE_576I:
		case VMODE_576CVBS:
		case VMODE_1080I:
		case VMODE_1080I_50HZ:
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
		case VMODE_1080I_59HZ:
#endif

			osd_hw.free_dst_data[index].y_start = y0 / 2;
			osd_hw.free_dst_data[index].y_end = y1 / 2;
			break;
		default:
			osd_hw.free_dst_data[index].y_start = y0;
			osd_hw.free_dst_data[index].y_end = y1;
			break;
		}
