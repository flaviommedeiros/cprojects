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

			*y0 = osd_hw.free_dst_data[index].y_start * 2;
			*y1 = osd_hw.free_dst_data[index].y_end * 2;
			break;
		default:
			*y0 = osd_hw.free_dst_data[index].y_start;
			*y1 = osd_hw.free_dst_data[index].y_end;
			break;
		}
