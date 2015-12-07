#ifdef CMX_CONF_DEBUG
if (0) {
#else
	if (members == 2) {
#endif
		/* "other" becomes other party */
		other = (list_entry(conf->mlist.next,
		    struct dsp_conf_member, list))->dsp;
		if (other == member)
			other = (list_entry(conf->mlist.prev,
			    struct dsp_conf_member, list))->dsp;
		o_q = other->rx_buff; /* received data */
		o_rr = (other->rx_R + len) & CMX_BUFF_MASK;
			/* end of rx-pointer */
		o_r = (o_rr - rr + r) & CMX_BUFF_MASK;
			/* start rx-pointer at current read position*/
		/* -> if echo is NOT enabled */
		if (!dsp->echo.software) {
			/*
			 * -> copy other member's rx-data,
			 * if tx-data is available, mix
			 */
			while (o_r != o_rr && t != tt) {
				*d++ = dsp_audio_mix_law[(p[t]<<8)|o_q[o_r]];
				t = (t+1) & CMX_BUFF_MASK;
				o_r = (o_r+1) & CMX_BUFF_MASK;
			}
			while (o_r != o_rr) {
				*d++ = o_q[o_r];
				o_r = (o_r+1) & CMX_BUFF_MASK;
			}
		/* -> if echo is enabled */
		} else {
			/*
			 * -> mix other member's rx-data with echo,
			 * if tx-data is available, mix
			 */
			while (r != rr && t != tt) {
				sample = dsp_audio_law_to_s32[p[t]] +
				    dsp_audio_law_to_s32[q[r]] +
				    dsp_audio_law_to_s32[o_q[o_r]];
				if (sample < -32768)
					sample = -32768;
				else if (sample > 32767)
					sample = 32767;
				*d++ = dsp_audio_s16_to_law[sample & 0xffff];
				    /* tx-data + rx_data + echo */
				t = (t+1) & CMX_BUFF_MASK;
				r = (r+1) & CMX_BUFF_MASK;
				o_r = (o_r+1) & CMX_BUFF_MASK;
			}
			while (r != rr) {
				*d++ = dsp_audio_mix_law[(q[r]<<8)|o_q[o_r]];
				r = (r+1) & CMX_BUFF_MASK;
				o_r = (o_r+1) & CMX_BUFF_MASK;
			}
		}
		dsp->tx_R = t;
		goto send_packet;
	}
#ifdef DSP_NEVER_DEFINED
	}
