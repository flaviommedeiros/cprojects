static struct snddev_icodec_data speaker_loopback_rx_data = {
	.capability = (SNDDEV_CAP_RX | SNDDEV_CAP_VOICE),
	.name = "speaker_loopback_rx",
	.copp_id = 0,
	.acdb_id = ACDB_ID_SPEAKER_LOOPBACK_RX,
	.profile = &speaker_loopback_rx_profile,
	.channel_mode = 2,
	.pmctl_id_sz = 0,
#ifdef CONFIG_VP_A2220_16KHZ
	.default_sample_rate = 16000,
#else
	.default_sample_rate = 48000,
#endif
	.pamp_on = &msm_snddev_poweramp_on_speaker_call,
	.pamp_off = &msm_snddev_poweramp_off_speaker_call,
//	.property = SIDE_TONE_MASK,
	.max_voice_rx_vol[VOC_NB_INDEX] = 1000,
	.min_voice_rx_vol[VOC_NB_INDEX] = -500,
	.max_voice_rx_vol[VOC_WB_INDEX] = 1000,
	.min_voice_rx_vol[VOC_WB_INDEX] = -500,
};
