static struct snd_soc_dai_driver sh4_ssi_dai[] = {
{
	.name			= "ssi-dai.0",
	.playback = {
		.rates		= SSI_RATES,
		.formats	= SSI_FMTS,
		.channels_min	= 2,
		.channels_max	= 8,
	},
	.capture = {
		.rates		= SSI_RATES,
		.formats	= SSI_FMTS,
		.channels_min	= 2,
		.channels_max	= 8,
	},
	.ops = &ssi_dai_ops,
},
#ifdef CONFIG_CPU_SUBTYPE_SH7760
{
	.name			= "ssi-dai.1",
	.playback = {
		.rates		= SSI_RATES,
		.formats	= SSI_FMTS,
		.channels_min	= 2,
		.channels_max	= 8,
	},
	.capture = {
		.rates		= SSI_RATES,
		.formats	= SSI_FMTS,
		.channels_min	= 2,
		.channels_max	= 8,
	},
	.ops = &ssi_dai_ops,
},
#endif
};
