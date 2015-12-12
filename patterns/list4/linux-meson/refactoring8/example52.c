static struct ich_pcm_table ali_pcms[] = {
	{
		.playback_ops = &snd_intel8x0_ali_playback_ops,
		.capture_ops = &snd_intel8x0_ali_capture_ops,
		.prealloc_size = 64 * 1024,
		.prealloc_max_size = 128 * 1024,
	},
	{
		.suffix = "MIC ADC",
		.capture_ops = &snd_intel8x0_ali_capture_mic_ops,
		.prealloc_size = 0,
		.prealloc_max_size = 128 * 1024,
		.ac97_idx = ALID_MIC,
	},
	{
		.suffix = "IEC958",
		.playback_ops = &snd_intel8x0_ali_ac97spdifout_ops,
		/* .capture_ops = &snd_intel8x0_ali_spdifin_ops, */
		.prealloc_size = 64 * 1024,
		.prealloc_max_size = 128 * 1024,
		.ac97_idx = ALID_AC97SPDIFOUT,
	},
#if 0 // NYI
	{
		.suffix = "HW IEC958",
		.playback_ops = &snd_intel8x0_ali_spdifout_ops,
		.prealloc_size = 64 * 1024,
		.prealloc_max_size = 128 * 1024,
	},
#endif
};
