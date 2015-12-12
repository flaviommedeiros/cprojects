switch (pre_saw->standard) {
	case DRX_STANDARD_8VSB:
		ext_attr->vsb_pre_saw_cfg = *pre_saw;
		break;
#ifndef DRXJ_VSB_ONLY
	case DRX_STANDARD_ITU_A:	/* fallthrough */
	case DRX_STANDARD_ITU_B:	/* fallthrough */
	case DRX_STANDARD_ITU_C:
		ext_attr->qam_pre_saw_cfg = *pre_saw;
		break;
#endif
	default:
		return -EINVAL;
	}
