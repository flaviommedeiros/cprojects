switch (prev_standard) {
#ifndef DRXJ_VSB_ONLY
	case DRX_STANDARD_ITU_A:	/* fallthrough */
	case DRX_STANDARD_ITU_B:	/* fallthrough */
	case DRX_STANDARD_ITU_C:
		rc = power_down_qam(demod, false);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		break;
#endif
	case DRX_STANDARD_8VSB:
		rc = power_down_vsb(demod, false);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		break;
	case DRX_STANDARD_UNKNOWN:
		/* Do nothing */
		break;
	case DRX_STANDARD_AUTO:	/* fallthrough */
	default:
		return -EINVAL;
	}
