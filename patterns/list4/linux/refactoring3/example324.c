switch (standard) {
	case DRX_STANDARD_8VSB:
		if (channel->mirror == DRX_MIRROR_AUTO)
			ext_attr->mirror = DRX_MIRROR_NO;
		else
			ext_attr->mirror = channel->mirror;
		rc = set_vsb(demod);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = set_frequency(demod, channel, tuner_freq_offset);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		break;
#ifndef DRXJ_VSB_ONLY
	case DRX_STANDARD_ITU_A:	/* fallthrough */
	case DRX_STANDARD_ITU_B:	/* fallthrough */
	case DRX_STANDARD_ITU_C:
		rc = set_qam_channel(demod, channel, tuner_freq_offset);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		break;
#endif
	case DRX_STANDARD_UNKNOWN:
	default:
		return -EIO;
	}
