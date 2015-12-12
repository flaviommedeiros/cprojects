switch (afe_gain->standard) {
	case DRX_STANDARD_8VSB:
		ext_attr->vsb_pga_cfg = gain * 13 + 140;
		break;
#ifndef DRXJ_VSB_ONLY
	case DRX_STANDARD_ITU_A:	/* fallthrough */
	case DRX_STANDARD_ITU_B:	/* fallthrough */
	case DRX_STANDARD_ITU_C:
		ext_attr->qam_pga_cfg = gain * 13 + 140;
		break;
#endif
	default:
		return -EIO;
	}
