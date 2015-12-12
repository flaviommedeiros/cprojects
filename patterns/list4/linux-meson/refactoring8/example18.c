static struct snd_soc_dai_driver sh4_hac_dai[] = {
{
	.name			= "hac-dai.0",
	.ac97_control		= 1,
	.playback = {
		.rates		= AC97_RATES,
		.formats	= AC97_FMTS,
		.channels_min	= 2,
		.channels_max	= 2,
	},
	.capture = {
		.rates		= AC97_RATES,
		.formats	= AC97_FMTS,
		.channels_min	= 2,
		.channels_max	= 2,
	},
	.ops = &hac_dai_ops,
},
#ifdef CONFIG_CPU_SUBTYPE_SH7760
{
	.name			= "hac-dai.1",
	.id			= 1,
	.playback = {
		.rates		= AC97_RATES,
		.formats	= AC97_FMTS,
		.channels_min	= 2,
		.channels_max	= 2,
	},
	.capture = {
		.rates		= AC97_RATES,
		.formats	= AC97_FMTS,
		.channels_min	= 2,
		.channels_max	= 2,
	},
	.ops = &hac_dai_ops,

},
#endif
};
