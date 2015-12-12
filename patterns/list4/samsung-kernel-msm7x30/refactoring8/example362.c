static struct adie_codec_hwsetting_entry handset_voip_tx_settings[] = {
#if 0
	{
		.freq_plan = 8000,
		.osr = 256,
		.actions = imic_8KHz_osr256_actions,
		.action_sz = ARRAY_SIZE(imic_8KHz_osr256_actions),
	},
	{
		.freq_plan = 16000,
		.osr = 256,
		.actions = imic_16KHz_osr256_actions,
		.action_sz = ARRAY_SIZE(imic_16KHz_osr256_actions),
	},
#endif
	{
		.freq_plan = 48000,
		.osr = 256,
		.actions = handset_voip_tx_48KHz_osr256_actions,
		.action_sz = ARRAY_SIZE(handset_voip_tx_48KHz_osr256_actions),
	}
};
