struct snd_soc_dai_driver aml_dai[] = {
	{	.name = "aml-dai0",
		.id = 0,
		.suspend = aml_dai_i2s_suspend,
		.resume = aml_dai_i2s_resume,
		.playback = {
			.channels_min = 1,
			.channels_max = 8,
			.rates = AML_DAI_I2S_RATES,
			.formats = AML_DAI_I2S_FORMATS,},
		.capture = {
			.channels_min = 1,
			.channels_max = 8,
			.rates = AML_DAI_I2S_RATES,
			.formats = AML_DAI_I2S_FORMATS,},
		.ops = &aml_dai_i2s_ops,
	},
#ifdef AML_DAI_PCM_SUPPORT
	{	.name = "aml-dai1",
		.id = 1,
		.suspend = aml_dai_pcm_suspend,
		.resume = aml_dai_pcm_resume,
		.playback = {
			.channels_min = 1,
			.channels_max = 1,
			.rates = AML_DAI_PCM_RATES,
			.formats = AML_DAI_PCM_FORMATS,},
		.capture = {
			.channels_min = 1,
			.channels_max = 1,
			.rates = AML_DAI_PCM_RATES,
			.formats = AML_DAI_PCM_FORMATS,},
		.ops = &aml_dai_pcm_ops,
	},
#endif
};
