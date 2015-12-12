static struct adie_codec_hwsetting_entry tty_headset_mono_call_tx_settings[] = {
	/* 8KHz, 16KHz, 48KHz TTY Tx devices can shared same set of actions */
#if 0
	{
		.freq_plan = 8000,
		.osr = 256,
		.actions = tty_headset_mono_tx_8KHz_osr256_actions,
		.action_sz = ARRAY_SIZE(tty_headset_mono_tx_8KHz_osr256_actions),
	},
	{
		.freq_plan = 16000,
		.osr = 256,
		.actions = tty_headset_mono_tx_8KHz_osr256_actions,
		.action_sz = ARRAY_SIZE(tty_headset_mono_tx_8KHz_osr256_actions),
	},
#endif
	{
		.freq_plan = 48000,
		.osr = 256,
		.actions = tty_headset_mono_call_tx_48KHz_osr256_actions,
		.action_sz = ARRAY_SIZE(tty_headset_mono_call_tx_48KHz_osr256_actions),
	}
};
