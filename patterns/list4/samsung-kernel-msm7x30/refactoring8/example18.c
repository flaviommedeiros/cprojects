static struct snd_soc_dai_driver atmel_ssc_dai[NUM_SSC_DEVICES] = {
	{
		.name = "atmel-ssc-dai.0",
		.probe = atmel_ssc_probe,
		.remove = atmel_ssc_remove,
		.suspend = atmel_ssc_suspend,
		.resume = atmel_ssc_resume,
		.playback = {
			.channels_min = 1,
			.channels_max = 2,
			.rates = ATMEL_SSC_RATES,
			.formats = ATMEL_SSC_FORMATS,},
		.capture = {
			.channels_min = 1,
			.channels_max = 2,
			.rates = ATMEL_SSC_RATES,
			.formats = ATMEL_SSC_FORMATS,},
		.ops = &atmel_ssc_dai_ops,
	},
#if NUM_SSC_DEVICES == 3
	{
		.name = "atmel-ssc-dai.1",
		.probe = atmel_ssc_probe,
		.remove = atmel_ssc_remove,
		.suspend = atmel_ssc_suspend,
		.resume = atmel_ssc_resume,
		.playback = {
			.channels_min = 1,
			.channels_max = 2,
			.rates = ATMEL_SSC_RATES,
			.formats = ATMEL_SSC_FORMATS,},
		.capture = {
			.channels_min = 1,
			.channels_max = 2,
			.rates = ATMEL_SSC_RATES,
			.formats = ATMEL_SSC_FORMATS,},
		.ops = &atmel_ssc_dai_ops,
	},
	{
		.name = "atmel-ssc-dai.2",
		.probe = atmel_ssc_probe,
		.remove = atmel_ssc_remove,
		.suspend = atmel_ssc_suspend,
		.resume = atmel_ssc_resume,
		.playback = {
			.channels_min = 1,
			.channels_max = 2,
			.rates = ATMEL_SSC_RATES,
			.formats = ATMEL_SSC_FORMATS,},
		.capture = {
			.channels_min = 1,
			.channels_max = 2,
			.rates = ATMEL_SSC_RATES,
			.formats = ATMEL_SSC_FORMATS,},
		.ops = &atmel_ssc_dai_ops,
	},
#endif
};
