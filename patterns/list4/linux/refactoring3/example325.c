switch (standard) {
	case DRX_STANDARD_8VSB:
#ifdef DRXJ_SIGNAL_ACCUM_ERR
		rc = get_acc_pkt_err(demod, &pkt);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
#endif
		if (lock_status != DRXJ_DEMOD_LOCK && lock_status != DRX_LOCKED) {
			p->pre_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			p->pre_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			p->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			p->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			p->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			p->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		} else {
			rc = get_vsb_post_rs_pck_err(dev_addr, &err, &pkt);
			if (rc != 0) {
				pr_err("error %d getting UCB\n", rc);
				p->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			} else {
				p->block_error.stat[0].scale = FE_SCALE_COUNTER;
				p->block_error.stat[0].uvalue += err;
				p->block_count.stat[0].scale = FE_SCALE_COUNTER;
				p->block_count.stat[0].uvalue += pkt;
			}

			/* PostViterbi is compute in steps of 10^(-6) */
			rc = get_vs_bpre_viterbi_ber(dev_addr, &ber, &cnt);
			if (rc != 0) {
				pr_err("error %d getting pre-ber\n", rc);
				p->pre_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			} else {
				p->pre_bit_error.stat[0].scale = FE_SCALE_COUNTER;
				p->pre_bit_error.stat[0].uvalue += ber;
				p->pre_bit_count.stat[0].scale = FE_SCALE_COUNTER;
				p->pre_bit_count.stat[0].uvalue += cnt;
			}

			rc = get_vs_bpost_viterbi_ber(dev_addr, &ber, &cnt);
			if (rc != 0) {
				pr_err("error %d getting post-ber\n", rc);
				p->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			} else {
				p->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
				p->post_bit_error.stat[0].uvalue += ber;
				p->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
				p->post_bit_count.stat[0].uvalue += cnt;
			}
			rc = get_vsbmer(dev_addr, &mer);
			if (rc != 0) {
				pr_err("error %d getting MER\n", rc);
				p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			} else {
				p->cnr.stat[0].svalue = mer * 100;
				p->cnr.stat[0].scale = FE_SCALE_DECIBEL;
			}
		}
		break;
#ifndef DRXJ_VSB_ONLY
	case DRX_STANDARD_ITU_A:
	case DRX_STANDARD_ITU_B:
	case DRX_STANDARD_ITU_C:
		rc = ctrl_get_qam_sig_quality(demod);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		break;
#endif
	default:
		return -EIO;
	}
