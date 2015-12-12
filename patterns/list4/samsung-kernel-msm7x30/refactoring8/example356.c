static struct adie_codec_hwsetting_entry tty_headset_mono_call_rx_settings[] = {
#if 0
	{
		.freq_plan = 8000,
		.osr = 256,
		.actions = tty_headset_mono_call_rx_8KHz_osr256_actions,
		.action_sz = ARRAY_SIZE(tty_headset_mono_call_rx_8KHz_osr256_actions),
	},
	{
		.freq_plan = 16000,
		.osr = 256,
		.actions = tty_headset_mono_call_rx_16KHz_osr256_actions,
		.action_sz = ARRAY_SIZE(tty_headset_mono_call_rx_16KHz_osr256_actions),
	},
#endif
	{
		.freq_plan = 48000,
		.osr = 256,
		.actions = tty_headset_mono_call_rx_48KHz_osr256_actions,
		.action_sz = ARRAY_SIZE(tty_headset_mono_call_rx_48KHz_osr256_actions),
	}
};
