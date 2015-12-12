static struct adie_codec_hwsetting_entry speaker_voip_tx_settings[] = {
#if 0
	{
		.freq_plan = 8000,
		.osr = 256,
		.actions = speaker_voip_tx_8KHz_osr256_actions,
		.action_sz = ARRAY_SIZE(speaker_voip_tx_8KHz_osr256_actions),
	},
	{ /* 8KHz profile is good for 16KHz */
		.freq_plan = 16000,
		.osr = 256,
		.actions = speaker_voip_tx_8KHz_osr256_actions,
		.action_sz = ARRAY_SIZE(speaker_voip_tx_8KHz_osr256_actions),
	},
#endif
	{
		.freq_plan = 48000,
		.osr = 256,
		.actions = speaker_voip_tx_48KHz_osr256_actions,
		.action_sz = ARRAY_SIZE(speaker_voip_tx_48KHz_osr256_actions),
	}
};
