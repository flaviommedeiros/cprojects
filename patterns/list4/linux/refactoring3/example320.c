switch (ext_attr->standard) {
	case DRX_STANDARD_8VSB:
		clp_sum_max = 1023;
		clp_dir_to = (u16) (-9);
		sns_sum_max = 1023;
		sns_dir_to = (u16) (-9);
		ki_innergain_min = (u16) (-32768);
		ki_max = 0x032C;
		agc_ki_dgain = 0xC;
		if_iaccu_hi_tgt_min = 2047;
		ki_min = 0x0117;
		ingain_tgt_max = 16383;
		clp_ctrl_mode = 0;
		rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_AGC_KI_MINGAIN__A, 0x7fff, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_AGC_KI_MAXGAIN__A, 0x0, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_AGC_CLP_SUM__A, 0, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_AGC_CLP_CYCCNT__A, 0, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_AGC_CLP_DIR_WD__A, 0, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_AGC_CLP_DIR_STP__A, 1, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_AGC_SNS_SUM__A, 0, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_AGC_SNS_CYCCNT__A, 0, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_AGC_SNS_DIR_WD__A, 0, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_AGC_SNS_DIR_STP__A, 1, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_AGC_INGAIN__A, 1024, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_VSB_AGC_POW_TGT__A, 22600, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_AGC_INGAIN_TGT__A, 13200, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		p_agc_if_settings = &(ext_attr->vsb_if_agc_cfg);
		p_agc_rf_settings = &(ext_attr->vsb_rf_agc_cfg);
		break;
#ifndef DRXJ_VSB_ONLY
	case DRX_STANDARD_ITU_A:
	case DRX_STANDARD_ITU_C:
	case DRX_STANDARD_ITU_B:
		ingain_tgt_max = 5119;
		clp_sum_max = 1023;
		clp_dir_to = (u16) (-5);
		sns_sum_max = 127;
		sns_dir_to = (u16) (-3);
		ki_innergain_min = 0;
		ki_max = 0x0657;
		if_iaccu_hi_tgt_min = 2047;
		agc_ki_dgain = 0x7;
		ki_min = 0x0117;
		clp_ctrl_mode = 0;
		rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_AGC_KI_MINGAIN__A, 0x7fff, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_AGC_KI_MAXGAIN__A, 0x0, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_AGC_CLP_SUM__A, 0, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_AGC_CLP_CYCCNT__A, 0, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_AGC_CLP_DIR_WD__A, 0, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_AGC_CLP_DIR_STP__A, 1, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_AGC_SNS_SUM__A, 0, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_AGC_SNS_CYCCNT__A, 0, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_AGC_SNS_DIR_WD__A, 0, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_AGC_SNS_DIR_STP__A, 1, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		p_agc_if_settings = &(ext_attr->qam_if_agc_cfg);
		p_agc_rf_settings = &(ext_attr->qam_rf_agc_cfg);
		rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_AGC_INGAIN_TGT__A, p_agc_if_settings->top, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}

		rc = drxj_dap_read_reg16(dev_addr, SCU_RAM_AGC_KI__A, &agc_ki, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		agc_ki &= 0xf000;
		rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_AGC_KI__A, agc_ki, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		break;
#endif
	default:
		return -EINVAL;
	}
