struct snd_soc_dai sh4_ssi_dai[] = {
{
	.name			= "SSI0",
	.id			= 0,
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
	.name			= "SSI1",
	.id			= 1,
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
