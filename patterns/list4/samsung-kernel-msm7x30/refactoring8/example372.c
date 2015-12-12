static struct snddev_icodec_data headset_call_rx_data = {
	.capability = (SNDDEV_CAP_RX | SNDDEV_CAP_VOICE),
	.name = "headset_call_rx",
	.copp_id = 0,
	.acdb_id = ACDB_ID_HEADSET_CALL_RX,
	.profile = &headset_call_rx_profile,
	.channel_mode = 2,
#ifdef CONFIG_VP_A2220_16KHZ
	.default_sample_rate = 16000,
#else
	.default_sample_rate = 48000,
#endif
	.pamp_on = msm_snddev_poweramp_on_headset_call,
	.pamp_off = msm_snddev_poweramp_off_headset_call,
//	.property = SIDE_TONE_MASK,
	.max_voice_rx_vol[VOC_NB_INDEX] = -700,
	.min_voice_rx_vol[VOC_NB_INDEX] = -2200,
	.max_voice_rx_vol[VOC_WB_INDEX] = -900,
	.min_voice_rx_vol[VOC_WB_INDEX] = -2400
};
