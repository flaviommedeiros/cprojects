static struct adie_codec_hwsetting_entry speaker_call_rx_settings[] = {
	{
#ifdef CONFIG_VP_A2220_16KHZ
		.freq_plan = 16000,
#else
		.freq_plan = 48000,
#endif
		.osr = 256,
		.actions = speaker_call_rx_48KHz_osr256_actions,
		.action_sz = ARRAY_SIZE(speaker_call_rx_48KHz_osr256_actions),
	}
};
