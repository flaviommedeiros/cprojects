static int generic_set_freq(struct dvb_frontend *fe, u32 freq /* in HZ */,
			    enum v4l2_tuner_type new_type,
			    unsigned int type,
			    v4l2_std_id std,
			    u16 int_freq)
{
	struct xc2028_data *priv = fe->tuner_priv;
	int		   rc = -EINVAL;
	unsigned char	   buf[4];
	u32		   div, offset = 0;

	tuner_dbg("%s called\n", __func__);

	mutex_lock(&priv->lock);

	tuner_dbg("should set frequency %d kHz\n", freq / 1000);

	if (check_firmware(fe, type, std, int_freq) < 0)
		goto ret;

	/* On some cases xc2028 can disable video output, if
	 * very weak signals are received. By sending a soft
	 * reset, this is re-enabled. So, it is better to always
	 * send a soft reset before changing channels, to be sure
	 * that xc2028 will be in a safe state.
	 * Maybe this might also be needed for DTV.
	 */
	switch (new_type) {
	case V4L2_TUNER_ANALOG_TV:
		rc = send_seq(priv, {0x00, 0x00});

		/* Analog mode requires offset = 0 */
		break;
	case V4L2_TUNER_RADIO:
		/* Radio mode requires offset = 0 */
		break;
	case V4L2_TUNER_DIGITAL_TV:
		/*
		 * Digital modes require an offset to adjust to the
		 * proper frequency. The offset depends on what
		 * firmware version is used.
		 */

		/*
		 * Adjust to the center frequency. This is calculated by the
		 * formula: offset = 1.25MHz - BW/2
		 * For DTV 7/8, the firmware uses BW = 8000, so it needs a
		 * further adjustment to get the frequency center on VHF
		 */

		/*
		 * The firmware DTV78 used to work fine in UHF band (8 MHz
		 * bandwidth) but not at all in VHF band (7 MHz bandwidth).
		 * The real problem was connected to the formula used to
		 * calculate the center frequency offset in VHF band.
		 * In fact, removing the 500KHz adjustment fixed the problem.
		 * This is coherent to what was implemented for the DTV7
		 * firmware.
		 * In the end, now the center frequency is the same for all 3
		 * firmwares (DTV7, DTV8, DTV78) and doesn't depend on channel
		 * bandwidth.
		 */

		if (priv->cur_fw.type & DTV6)
			offset = 1750000;
		else	/* DTV7 or DTV8 or DTV78 */
			offset = 2750000;

		/*
		 * xc3028 additional "magic"
		 * Depending on the firmware version, it needs some adjustments
		 * to properly centralize the frequency. This seems to be
		 * needed to compensate the SCODE table adjustments made by
		 * newer firmwares
		 */

		/*
		 * The proper adjustment would be to do it at s-code table.
		 * However, this didn't work, as reported by
		 * Robert Lowery <rglowery@exemail.com.au>
		 */

#if 0
		/*
		 * Still need tests for XC3028L (firmware 3.2 or upper)
		 * So, for now, let's just comment the per-firmware
		 * version of this change. Reports with xc3028l working
		 * with and without the lines below are welcome
		 */

		if (priv->firm_version < 0x0302) {
			if (priv->cur_fw.type & DTV7)
				offset += 500000;
		} else {
			if (priv->cur_fw.type & DTV7)
				offset -= 300000;
			else if (type != ATSC) /* DVB @6MHz, DTV 8 and DTV 7/8 */
				offset += 200000;
		}
#endif
		break;
	default:
		tuner_err("Unsupported tuner type %d.\n", new_type);
		break;
	}
