static const struct snd_soc_dapm_widget wm1133_ev1_widgets[] = {
#ifdef USE_SIMIC
	SND_SOC_DAPM_MIC("SiMIC", NULL),
#endif
	SND_SOC_DAPM_MIC("Mic1 Jack", NULL),
	SND_SOC_DAPM_MIC("Mic2 Jack", NULL),
	SND_SOC_DAPM_LINE("Line In Jack", NULL),
	SND_SOC_DAPM_LINE("Line Out Jack", NULL),
	SND_SOC_DAPM_HP("Headphone Jack", NULL),
};
