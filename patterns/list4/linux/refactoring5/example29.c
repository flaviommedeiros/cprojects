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
				*d++ = dsp_audio_mix_law[(p[t] << 8) | o_q[o_r]];
				t = (t + 1) & CMX_BUFF_MASK;
				o_r = (o_r + 1) & CMX_BUFF_MASK;
			}
			while (o_r != o_rr) {
				*d++ = o_q[o_r];
				o_r = (o_r + 1) & CMX_BUFF_MASK;
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
				t = (t + 1) & CMX_BUFF_MASK;
				r = (r + 1) & CMX_BUFF_MASK;
				o_r = (o_r + 1) & CMX_BUFF_MASK;
			}
			while (r != rr) {
				*d++ = dsp_audio_mix_law[(q[r] << 8) | o_q[o_r]];
				r = (r + 1) & CMX_BUFF_MASK;
				o_r = (o_r + 1) & CMX_BUFF_MASK;
			}
		}
		dsp->tx_R = t;
		goto send_packet;
	}
	/* PROCESS DATA (three or more members) */
	/* -> if echo is NOT enabled */
	if (!dsp->echo.software) {
		/*
		 * -> subtract rx-data from conf-data,
		 * if tx-data is available, mix
		 */
		while (r != rr && t != tt) {
			sample = dsp_audio_law_to_s32[p[t]] + *c++ -
				dsp_audio_law_to_s32[q[r]];
			if (sample < -32768)
				sample = -32768;
			else if (sample > 32767)
				sample = 32767;
			*d++ = dsp_audio_s16_to_law[sample & 0xffff];
			/* conf-rx+tx */
			r = (r + 1) & CMX_BUFF_MASK;
			t = (t + 1) & CMX_BUFF_MASK;
		}
		while (r != rr) {
			sample = *c++ - dsp_audio_law_to_s32[q[r]];
			if (sample < -32768)
				sample = -32768;
			else if (sample > 32767)
				sample = 32767;
			*d++ = dsp_audio_s16_to_law[sample & 0xffff];
			/* conf-rx */
			r = (r + 1) & CMX_BUFF_MASK;
		}
		/* -> if echo is enabled */
	} else {
		/*
		 * -> encode conf-data, if tx-data
		 * is available, mix
		 */
		while (r != rr && t != tt) {
			sample = dsp_audio_law_to_s32[p[t]] + *c++;
			if (sample < -32768)
				sample = -32768;
			else if (sample > 32767)
				sample = 32767;
			*d++ = dsp_audio_s16_to_law[sample & 0xffff];
			/* conf(echo)+tx */
			t = (t + 1) & CMX_BUFF_MASK;
			r = (r + 1) & CMX_BUFF_MASK;
		}
		while (r != rr) {
			sample = *c++;
			if (sample < -32768)
				sample = -32768;
			else if (sample > 32767)
				sample = 32767;
			*d++ = dsp_audio_s16_to_law[sample & 0xffff];
			/* conf(echo) */
			r = (r + 1) & CMX_BUFF_MASK;
		}
	}
	dsp->tx_R = t;
	goto send_packet;

send_packet:
	/*
	 * send tx-data if enabled - don't filter,
	 * because we want what we send, not what we filtered
	 */
	if (dsp->tx_data) {
		if (tx_data_only) {
			hh->prim = DL_DATA_REQ;
			hh->id = 0;
			/* queue and trigger */
			skb_queue_tail(&dsp->sendq, nskb);
			schedule_work(&dsp->workq);
			/* exit because only tx_data is used */
			return;
		} else {
			txskb = mI_alloc_skb(len, GFP_ATOMIC);
			if (!txskb) {
				printk(KERN_ERR
				       "FATAL ERROR in mISDN_dsp.o: "
				       "cannot alloc %d bytes\n", len);
			} else {
				thh = mISDN_HEAD_P(txskb);
				thh->prim = DL_DATA_REQ;
				thh->id = 0;
				memcpy(skb_put(txskb, len), nskb->data + preload,
				       len);
				/* queue (trigger later) */
				skb_queue_tail(&dsp->sendq, txskb);
			}
		}
	}

	/* send data only to card, if we don't just calculated tx_data */
	/* adjust volume */
	if (dsp->tx_volume)
		dsp_change_volume(nskb, dsp->tx_volume);
	/* pipeline */
	if (dsp->pipeline.inuse)
		dsp_pipeline_process_tx(&dsp->pipeline, nskb->data,
					nskb->len);
	/* crypt */
	if (dsp->bf_enable)
		dsp_bf_encrypt(dsp, nskb->data, nskb->len);
	/* queue and trigger */
	skb_queue_tail(&dsp->sendq, nskb);
	schedule_work(&dsp->workq);
}
