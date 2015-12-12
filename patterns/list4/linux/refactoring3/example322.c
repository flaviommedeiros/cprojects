switch (agc_settings->standard) {
	case DRX_STANDARD_8VSB:
		ext_attr->vsb_if_agc_cfg = *agc_settings;
		break;
#ifndef DRXJ_VSB_ONLY
	case DRX_STANDARD_ITU_A:
	case DRX_STANDARD_ITU_B:
	case DRX_STANDARD_ITU_C:
		ext_attr->qam_if_agc_cfg = *agc_settings;
		break;
#endif
	default:
		return -EIO;
	}
