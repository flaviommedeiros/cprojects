static const struct snd_kcontrol_new snd_ac97_controls_alc650[] = {
	AC97_SINGLE("Duplicate Front", AC97_ALC650_MULTICH, 0, 1, 0),
	AC97_SINGLE("Surround Down Mix", AC97_ALC650_MULTICH, 1, 1, 0),
	AC97_SINGLE("Center/LFE Down Mix", AC97_ALC650_MULTICH, 2, 1, 0),
	AC97_SINGLE("Exchange Center/LFE", AC97_ALC650_MULTICH, 3, 1, 0),
	/* 4: Analog Input To Surround */
	/* 5: Analog Input To Center/LFE */
	/* 6: Independent Master Volume Right */
	/* 7: Independent Master Volume Left */
	/* 8: reserved */
	/* 9: Line-In/Surround share */
	/* 10: Mic/CLFE share */
	/* 11-13: in IEC958 controls */
	{
		.iface = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Swap Surround Slot",
		.info = snd_ac97_info_volsw,
		.get = snd_ac97_get_volsw,
		.put = alc650_swap_surround_put,
		.private_value =  AC97_SINGLE_VALUE(AC97_ALC650_MULTICH, 14, 1, 0),
	},
#if 0 /* always set in patch_alc650 */
	AC97_SINGLE("IEC958 Input Clock Enable", AC97_ALC650_CLOCK, 0, 1, 0),
	AC97_SINGLE("IEC958 Input Pin Enable", AC97_ALC650_CLOCK, 1, 1, 0),
	AC97_SINGLE("Surround DAC Switch", AC97_ALC650_SURR_DAC_VOL, 15, 1, 1),
	AC97_DOUBLE("Surround DAC Volume", AC97_ALC650_SURR_DAC_VOL, 8, 0, 31, 1),
	AC97_SINGLE("Center/LFE DAC Switch", AC97_ALC650_LFE_DAC_VOL, 15, 1, 1),
	AC97_DOUBLE("Center/LFE DAC Volume", AC97_ALC650_LFE_DAC_VOL, 8, 0, 31, 1),
#endif
	AC97_SURROUND_JACK_MODE_CTL,
	AC97_CHANNEL_MODE_CTL,
};
