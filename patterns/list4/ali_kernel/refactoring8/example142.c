static int32_t mt9t013_setting(enum mt9t013_reg_update rupdate,
	enum mt9t013_setting rt)
{
	int32_t rc = 0;

	switch (rupdate) {
	case UPDATE_PERIODIC: {

	if (rt == RES_PREVIEW || rt == RES_CAPTURE) {
#if 0
		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				MT9T013_REG_RESET_REGISTER,
				MT9T013_RESET_REGISTER_PWOFF);
		if (rc < 0)
			return rc;
#endif

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_VT_PIX_CLK_DIV,
				mt9t013_regs.reg_pat[rt].vt_pix_clk_div);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_VT_SYS_CLK_DIV,
				mt9t013_regs.reg_pat[rt].vt_sys_clk_div);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_PRE_PLL_CLK_DIV,
				mt9t013_regs.reg_pat[rt].pre_pll_clk_div);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_PLL_MULTIPLIER,
				mt9t013_regs.reg_pat[rt].pll_multiplier);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_OP_PIX_CLK_DIV,
				mt9t013_regs.reg_pat[rt].op_pix_clk_div);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_OP_SYS_CLK_DIV,
				mt9t013_regs.reg_pat[rt].op_sys_clk_div);
		if (rc < 0)
			return rc;

		mdelay(5);

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_GROUPED_PARAMETER_HOLD,
				GROUPED_PARAMETER_HOLD);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_ROW_SPEED,
				mt9t013_regs.reg_pat[rt].row_speed);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_X_ADDR_START,
				mt9t013_regs.reg_pat[rt].x_addr_start);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_X_ADDR_END,
				mt9t013_regs.reg_pat[rt].x_addr_end);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_Y_ADDR_START,
				mt9t013_regs.reg_pat[rt].y_addr_start);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_Y_ADDR_END,
				mt9t013_regs.reg_pat[rt].y_addr_end);
		if (rc < 0)
			return rc;

		if (machine_is_sapphire()) {
			if (rt == 0)
				rc = mt9t013_i2c_write_w(mt9t013_client->addr,
					REG_READ_MODE,
					0x046F);
			else
				rc = mt9t013_i2c_write_w(mt9t013_client->addr,
					REG_READ_MODE,
					0x0027);
		} else
			rc = mt9t013_i2c_write_w(mt9t013_client->addr,
					REG_READ_MODE,
					mt9t013_regs.reg_pat[rt].read_mode);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_SCALE_M,
				mt9t013_regs.reg_pat[rt].scale_m);
		if (rc < 0)
			return rc;


		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_X_OUTPUT_SIZE,
				mt9t013_regs.reg_pat[rt].x_output_size);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_Y_OUTPUT_SIZE,
				mt9t013_regs.reg_pat[rt].y_output_size);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_LINE_LENGTH_PCK,
				mt9t013_regs.reg_pat[rt].line_length_pck);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
			REG_FRAME_LENGTH_LINES,
			(mt9t013_regs.reg_pat[rt].frame_length_lines *
			mt9t013_ctrl->fps_divider / 0x00000400));
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
			REG_COARSE_INT_TIME,
			mt9t013_regs.reg_pat[rt].coarse_int_time);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
			REG_FINE_INT_TIME,
			mt9t013_regs.reg_pat[rt].fine_int_time);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
			REG_GROUPED_PARAMETER_HOLD,
			GROUPED_PARAMETER_UPDATE);
		if (rc < 0)
			return rc;

		rc = mt9t013_test(mt9t013_ctrl->set_test);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
			MT9T013_REG_RESET_REGISTER,
			MT9T013_RESET_REGISTER_PWON);
		if (rc < 0)
			return rc;

		mdelay(5);

		return rc;
	}
	}
		break;

	/*CAMSENSOR_REG_UPDATE_PERIODIC */
	case REG_INIT: {
	if (rt == RES_PREVIEW || rt == RES_CAPTURE) {

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				MT9T013_REG_RESET_REGISTER,
				MT9T013_RESET_REGISTER_PWOFF);
		if (rc < 0)
			/* MODE_SELECT, stop streaming */
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_VT_PIX_CLK_DIV,
				mt9t013_regs.reg_pat[rt].vt_pix_clk_div);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_VT_SYS_CLK_DIV,
				mt9t013_regs.reg_pat[rt].vt_sys_clk_div);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_PRE_PLL_CLK_DIV,
				mt9t013_regs.reg_pat[rt].pre_pll_clk_div);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_PLL_MULTIPLIER,
				mt9t013_regs.reg_pat[rt].pll_multiplier);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_OP_PIX_CLK_DIV,
				mt9t013_regs.reg_pat[rt].op_pix_clk_div);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_OP_SYS_CLK_DIV,
				mt9t013_regs.reg_pat[rt].op_sys_clk_div);
		if (rc < 0)
			return rc;

		mdelay(5);

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_GROUPED_PARAMETER_HOLD,
				GROUPED_PARAMETER_HOLD);
		if (rc < 0)
			return rc;

		/* additional power saving mode ok around 38.2MHz */
		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				0x3084, 0x2409);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				0x3092, 0x0A49);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				0x3094, 0x4949);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				0x3096, 0x4949);
		if (rc < 0)
			return rc;

		/* Set preview or snapshot mode */
		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_ROW_SPEED,
				mt9t013_regs.reg_pat[rt].row_speed);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_X_ADDR_START,
				mt9t013_regs.reg_pat[rt].x_addr_start);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_X_ADDR_END,
				mt9t013_regs.reg_pat[rt].x_addr_end);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_Y_ADDR_START,
				mt9t013_regs.reg_pat[rt].y_addr_start);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_Y_ADDR_END,
				mt9t013_regs.reg_pat[rt].y_addr_end);
		if (rc < 0)
			return rc;

		if (machine_is_sapphire()) {
			if (rt == 0)
				rc = mt9t013_i2c_write_w(mt9t013_client->addr,
					REG_READ_MODE,
					0x046F);
			else
				rc = mt9t013_i2c_write_w(mt9t013_client->addr,
					REG_READ_MODE,
					0x0027);
		} else
			rc = mt9t013_i2c_write_w(mt9t013_client->addr,
					REG_READ_MODE,
					mt9t013_regs.reg_pat[rt].read_mode);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_SCALE_M,
				mt9t013_regs.reg_pat[rt].scale_m);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_X_OUTPUT_SIZE,
				mt9t013_regs.reg_pat[rt].x_output_size);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_Y_OUTPUT_SIZE,
				mt9t013_regs.reg_pat[rt].y_output_size);
		if (rc < 0)
			return 0;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_LINE_LENGTH_PCK,
				mt9t013_regs.reg_pat[rt].line_length_pck);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_FRAME_LENGTH_LINES,
				mt9t013_regs.reg_pat[rt].frame_length_lines);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_COARSE_INT_TIME,
				mt9t013_regs.reg_pat[rt].coarse_int_time);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_FINE_INT_TIME,
				mt9t013_regs.reg_pat[rt].fine_int_time);
		if (rc < 0)
			return rc;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_GROUPED_PARAMETER_HOLD,
				GROUPED_PARAMETER_UPDATE);
			if (rc < 0)
				return rc;

		/* load lens shading */
		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_GROUPED_PARAMETER_HOLD,
				GROUPED_PARAMETER_HOLD);
		if (rc < 0)
			return rc;

		/* most likely needs to be written only once. */
		rc = mt9t013_set_lc();
		if (rc < 0)
			return -EBUSY;

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				REG_GROUPED_PARAMETER_HOLD,
				GROUPED_PARAMETER_UPDATE);
		if (rc < 0)
			return rc;

		rc = mt9t013_test(mt9t013_ctrl->set_test);
		if (rc < 0)
			return rc;

		mdelay(5);

		rc =
			mt9t013_i2c_write_w(mt9t013_client->addr,
				MT9T013_REG_RESET_REGISTER,
				MT9T013_RESET_REGISTER_PWON);
		if (rc < 0)
			/* MODE_SELECT, stop streaming */
			return rc;

		CDBG("!!! mt9t013 !!! PowerOn is done!\n");
		mdelay(5);
		return rc;
		}
	} /* case CAMSENSOR_REG_INIT: */
	break;

	/*CAMSENSOR_REG_INIT */
	default:
		rc = -EINVAL;
		break;
	} /* switch (rupdate) */

	return rc;
}
