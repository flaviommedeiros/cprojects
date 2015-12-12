struct snd_soc_dai_driver rt5640_dai[] = {
	{
		.name = "rt5640-aif1",
		.id = RT5640_AIF1,
		.playback = {
			.stream_name = "AIF1 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5640_STEREO_RATES,
			.formats = RT5640_FORMATS,
		},
		.capture = {
			.stream_name = "AIF1 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5640_STEREO_RATES,
			.formats = RT5640_FORMATS,
		},
		.ops = &rt5640_aif_dai_ops,
	},
	{
		.name = "rt5640-aif2",
		.id = RT5640_AIF2,
		.playback = {
			.stream_name = "AIF2 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5640_STEREO_RATES,
			.formats = RT5640_FORMATS,
		},
		.capture = {
			.stream_name = "AIF2 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5640_STEREO_RATES,
			.formats = RT5640_FORMATS,
		},
		.ops = &rt5640_aif_dai_ops,
	},
#if (CONFIG_SND_SOC_RT5643_MODULE | CONFIG_SND_SOC_RT5643 | \
	CONFIG_SND_SOC_RT5646_MODULE | CONFIG_SND_SOC_RT5646 )
	{
		.name = "rt5640-aif3",
		.id = RT5640_AIF3,
		.playback = {
			.stream_name = "AIF3 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5640_STEREO_RATES,
			.formats = RT5640_FORMATS,
		},
		.capture = {
			.stream_name = "AIF3 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5640_STEREO_RATES,
			.formats = RT5640_FORMATS,
		},
		.ops = &rt5640_aif_dai_ops,
	},
#endif
};
