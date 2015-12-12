switch (pp_ptr->op) {
#ifdef CONFIG_FB_MSM_MDP40
	case mdp_op_csc_cfg:
		ret = mdp4_csc_config(&(pp_ptr->data.csc_cfg_data));
		for (i = 0; i < CSC_MAX_BLOCKS; i++) {
			if (pp_ptr->data.csc_cfg_data.block ==
					csc_cfg_matrix[i].block) {
				memcpy(&csc_cfg_matrix[i].csc_data,
				&(pp_ptr->data.csc_cfg_data.csc_data),
				sizeof(struct mdp_csc_cfg));
				break;
			}
		}
		break;

	case mdp_op_pcc_cfg:
		ret = mdp4_pcc_cfg(&(pp_ptr->data.pcc_cfg_data));
		break;

	case mdp_op_lut_cfg:
		switch (pp_ptr->data.lut_cfg_data.lut_type) {
		case mdp_lut_igc:
			ret = mdp4_igc_lut_config(
					(struct mdp_igc_lut_data *)
					&pp_ptr->data.lut_cfg_data.data);
			break;

		case mdp_lut_pgc:
			ret = mdp4_argc_cfg(
				&pp_ptr->data.lut_cfg_data.data.pgc_lut_data);
			break;

		case mdp_lut_hist:
			ret = mdp_hist_lut_config(
					(struct mdp_hist_lut_data *)
					&pp_ptr->data.lut_cfg_data.data);
			break;

		default:
			break;
		}
		break;
	case mdp_op_qseed_cfg:
		ret = mdp4_qseed_cfg((struct mdp_qseed_cfg_data *)
						&pp_ptr->data.qseed_cfg_data);
		break;
	case mdp_op_calib_cfg:
		ret = mdp4_calib_config((struct mdp_calib_config_data *)
						&pp_ptr->data.calib_cfg);
		break;
#endif
	case mdp_bl_scale_cfg:
		ret = msmfb_validate_scale_config(&pp_ptr->data.bl_scale_data);
		if (ret) {
			pr_err("%s: invalid scale config\n", __func__);
			break;
		}
		ret = mdp_bl_scale_config(mfd, (struct mdp_bl_scale_data *)
				&pp_ptr->data.bl_scale_data);
		break;

	default:
		pr_warn("Unsupported request to MDP_PP IOCTL.\n");
		ret = -EINVAL;
		break;
	}
