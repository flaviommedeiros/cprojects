switch (*standard) {
#ifndef DRXJ_VSB_ONLY
	case DRX_STANDARD_ITU_A:	/* fallthrough */
	case DRX_STANDARD_ITU_B:	/* fallthrough */
	case DRX_STANDARD_ITU_C:
		do {
			u16 dummy;
			rc = drxj_dap_read_reg16(demod->my_i2c_dev_addr, SCU_RAM_VERSION_HI__A, &dummy, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
		} while (0);
		break;
#endif
	case DRX_STANDARD_8VSB:
		rc = set_vsb_leak_n_gain(demod);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		break;
	default:
		ext_attr->standard = DRX_STANDARD_UNKNOWN;
		return -EINVAL;
		break;
	}
