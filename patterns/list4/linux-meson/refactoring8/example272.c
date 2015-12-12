static int r820t_set_tv_standard(struct r820t_priv *priv,
				 unsigned bw,
				 enum v4l2_tuner_type type,
				 v4l2_std_id std, u32 delsys)

{
	int rc, i;
	u32 if_khz, filt_cal_lo;
	u8 data[5], val;
	u8 filt_gain, img_r, filt_q, hp_cor, ext_enable, loop_through;
	u8 lt_att, flt_ext_widest, polyfil_cur;
	bool need_calibration;

	tuner_dbg("selecting the delivery system\n");

	if (delsys == SYS_ISDBT) {
		if_khz = 4063;
		filt_cal_lo = 59000;
		filt_gain = 0x10;	/* +3db, 6mhz on */
		img_r = 0x00;		/* image negative */
		filt_q = 0x10;		/* r10[4]:low q(1'b1) */
		hp_cor = 0x6a;		/* 1.7m disable, +2cap, 1.25mhz */
		ext_enable = 0x40;	/* r30[6], ext enable; r30[5]:0 ext at lna max */
		loop_through = 0x00;	/* r5[7], lt on */
		lt_att = 0x00;		/* r31[7], lt att enable */
		flt_ext_widest = 0x00;	/* r15[7]: flt_ext_wide off */
		polyfil_cur = 0x60;	/* r25[6:5]:min */
	} else {
		if (bw <= 6) {
			if_khz = 3570;
			filt_cal_lo = 56000;	/* 52000->56000 */
			filt_gain = 0x10;	/* +3db, 6mhz on */
			img_r = 0x00;		/* image negative */
			filt_q = 0x10;		/* r10[4]:low q(1'b1) */
			hp_cor = 0x6b;		/* 1.7m disable, +2cap, 1.0mhz */
			ext_enable = 0x60;	/* r30[6]=1 ext enable; r30[5]:1 ext at lna max-1 */
			loop_through = 0x00;	/* r5[7], lt on */
			lt_att = 0x00;		/* r31[7], lt att enable */
			flt_ext_widest = 0x00;	/* r15[7]: flt_ext_wide off */
			polyfil_cur = 0x60;	/* r25[6:5]:min */
		} else if (bw == 7) {
#if 0
			/*
			 * There are two 7 MHz tables defined on the original
			 * driver, but just the second one seems to be visible
			 * by rtl2832. Keep this one here commented, as it
			 * might be needed in the future
			 */

			if_khz = 4070;
			filt_cal_lo = 60000;
			filt_gain = 0x10;	/* +3db, 6mhz on */
			img_r = 0x00;		/* image negative */
			filt_q = 0x10;		/* r10[4]:low q(1'b1) */
			hp_cor = 0x2b;		/* 1.7m disable, +1cap, 1.0mhz */
			ext_enable = 0x60;	/* r30[6]=1 ext enable; r30[5]:1 ext at lna max-1 */
			loop_through = 0x00;	/* r5[7], lt on */
			lt_att = 0x00;		/* r31[7], lt att enable */
			flt_ext_widest = 0x00;	/* r15[7]: flt_ext_wide off */
			polyfil_cur = 0x60;	/* r25[6:5]:min */
#endif
			/* 7 MHz, second table */
			if_khz = 4570;
			filt_cal_lo = 63000;
			filt_gain = 0x10;	/* +3db, 6mhz on */
			img_r = 0x00;		/* image negative */
			filt_q = 0x10;		/* r10[4]:low q(1'b1) */
			hp_cor = 0x2a;		/* 1.7m disable, +1cap, 1.25mhz */
			ext_enable = 0x60;	/* r30[6]=1 ext enable; r30[5]:1 ext at lna max-1 */
			loop_through = 0x00;	/* r5[7], lt on */
			lt_att = 0x00;		/* r31[7], lt att enable */
			flt_ext_widest = 0x00;	/* r15[7]: flt_ext_wide off */
			polyfil_cur = 0x60;	/* r25[6:5]:min */
		} else {
			if_khz = 4570;
			filt_cal_lo = 68500;
			filt_gain = 0x10;	/* +3db, 6mhz on */
			img_r = 0x00;		/* image negative */
			filt_q = 0x10;		/* r10[4]:low q(1'b1) */
			hp_cor = 0x0b;		/* 1.7m disable, +0cap, 1.0mhz */
			ext_enable = 0x60;	/* r30[6]=1 ext enable; r30[5]:1 ext at lna max-1 */
			loop_through = 0x00;	/* r5[7], lt on */
			lt_att = 0x00;		/* r31[7], lt att enable */
			flt_ext_widest = 0x00;	/* r15[7]: flt_ext_wide off */
			polyfil_cur = 0x60;	/* r25[6:5]:min */
		}
	}

	/* Initialize the shadow registers */
	memcpy(priv->regs, r820t_init_array, sizeof(r820t_init_array));

	/* Init Flag & Xtal_check Result */
	if (priv->imr_done)
		val = 1 | priv->xtal_cap_sel << 1;
	else
		val = 0;
	rc = r820t_write_reg_mask(priv, 0x0c, val, 0x0f);
	if (rc < 0)
		return rc;

	/* version */
	rc = r820t_write_reg_mask(priv, 0x13, VER_NUM, 0x3f);
	if (rc < 0)
		return rc;

	/* for LT Gain test */
	if (type != V4L2_TUNER_ANALOG_TV) {
		rc = r820t_write_reg_mask(priv, 0x1d, 0x00, 0x38);
		if (rc < 0)
			return rc;
		usleep_range(1000, 2000);
	}
	priv->int_freq = if_khz * 1000;

	/* Check if standard changed. If so, filter calibration is needed */
	if (type != priv->type)
		need_calibration = true;
	else if ((type == V4L2_TUNER_ANALOG_TV) && (std != priv->std))
		need_calibration = true;
	else if ((type == V4L2_TUNER_DIGITAL_TV) &&
		 ((delsys != priv->delsys) || bw != priv->bw))
		need_calibration = true;
	else
		need_calibration = false;

	if (need_calibration) {
		tuner_dbg("calibrating the tuner\n");
		for (i = 0; i < 2; i++) {
			/* Set filt_cap */
			rc = r820t_write_reg_mask(priv, 0x0b, hp_cor, 0x60);
			if (rc < 0)
				return rc;

			/* set cali clk =on */
			rc = r820t_write_reg_mask(priv, 0x0f, 0x04, 0x04);
			if (rc < 0)
				return rc;

			/* X'tal cap 0pF for PLL */
			rc = r820t_write_reg_mask(priv, 0x10, 0x00, 0x03);
			if (rc < 0)
				return rc;

			rc = r820t_set_pll(priv, type, filt_cal_lo * 1000);
			if (rc < 0 || !priv->has_lock)
				return rc;

			/* Start Trigger */
			rc = r820t_write_reg_mask(priv, 0x0b, 0x10, 0x10);
			if (rc < 0)
				return rc;

			usleep_range(1000, 2000);

			/* Stop Trigger */
			rc = r820t_write_reg_mask(priv, 0x0b, 0x00, 0x10);
			if (rc < 0)
				return rc;

			/* set cali clk =off */
			rc = r820t_write_reg_mask(priv, 0x0f, 0x00, 0x04);
			if (rc < 0)
				return rc;

			/* Check if calibration worked */
			rc = r820t_read(priv, 0x00, data, sizeof(data));
			if (rc < 0)
				return rc;

			priv->fil_cal_code = data[4] & 0x0f;
			if (priv->fil_cal_code && priv->fil_cal_code != 0x0f)
				break;
		}
		/* narrowest */
		if (priv->fil_cal_code == 0x0f)
			priv->fil_cal_code = 0;
	}

	rc = r820t_write_reg_mask(priv, 0x0a,
				  filt_q | priv->fil_cal_code, 0x1f);
	if (rc < 0)
		return rc;

	/* Set BW, Filter_gain, & HP corner */
	rc = r820t_write_reg_mask(priv, 0x0b, hp_cor, 0xef);
	if (rc < 0)
		return rc;


	/* Set Img_R */
	rc = r820t_write_reg_mask(priv, 0x07, img_r, 0x80);
	if (rc < 0)
		return rc;

	/* Set filt_3dB, V6MHz */
	rc = r820t_write_reg_mask(priv, 0x06, filt_gain, 0x30);
	if (rc < 0)
		return rc;

	/* channel filter extension */
	rc = r820t_write_reg_mask(priv, 0x1e, ext_enable, 0x60);
	if (rc < 0)
		return rc;

	/* Loop through */
	rc = r820t_write_reg_mask(priv, 0x05, loop_through, 0x80);
	if (rc < 0)
		return rc;

	/* Loop through attenuation */
	rc = r820t_write_reg_mask(priv, 0x1f, lt_att, 0x80);
	if (rc < 0)
		return rc;

	/* filter extension widest */
	rc = r820t_write_reg_mask(priv, 0x0f, flt_ext_widest, 0x80);
	if (rc < 0)
		return rc;

	/* RF poly filter current */
	rc = r820t_write_reg_mask(priv, 0x19, polyfil_cur, 0x60);
	if (rc < 0)
		return rc;

	/* Store current standard. If it changes, re-calibrate the tuner */
	priv->delsys = delsys;
	priv->type = type;
	priv->std = std;
	priv->bw = bw;

	return 0;
}
