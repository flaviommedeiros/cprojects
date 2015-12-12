static struct adie_codec_hwsetting_entry headset_voice_search_tx_settings[] = {
#if 0
	{
		.freq_plan = 8000,
		.osr = 256,
		.actions = headset_voice_search_tx_8KHz_osr256_actions,
		.action_sz = ARRAY_SIZE(headset_voice_search_tx_8KHz_osr256_actions),
	},
	{
		.freq_plan = 16000,
		.osr = 256,
		.actions = headset_voice_search_tx_16KHz_osr256_actions,
		.action_sz = ARRAY_SIZE(headset_voice_search_tx_16KHz_osr256_actions),
	},
#endif
	{
		.freq_plan = 48000,
		.osr = 256,
		.actions = headset_voice_search_tx_48KHz_osr256_actions,
		.action_sz = ARRAY_SIZE(headset_voice_search_tx_48KHz_osr256_actions),
	}
};
