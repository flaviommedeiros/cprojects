static const struct snd_soc_dapm_route wm1133_ev1_map[] = {

#ifdef USE_SIMIC
	/* SiMIC --> IN1LN (with automatic bias) via SP1 */
	{ "IN1LN", NULL, "Mic Bias" },
	{ "Mic Bias", NULL, "SiMIC" },
#endif

	/* Mic 1 Jack --> IN1LN and IN1LP (with automatic bias) */
	{ "IN1LN", NULL, "Mic Bias" },
	{ "IN1LP", NULL, "Mic1 Jack" },
	{ "Mic Bias", NULL, "Mic1 Jack" },

	/* Mic 2 Jack --> IN1RN and IN1RP (with automatic bias) */
	{ "IN1RN", NULL, "Mic Bias" },
	{ "IN1RP", NULL, "Mic2 Jack" },
	{ "Mic Bias", NULL, "Mic2 Jack" },

	/* Line in Jack --> AUX (L+R) */
	{ "IN3R", NULL, "Line In Jack" },
	{ "IN3L", NULL, "Line In Jack" },

	/* Out1 --> Headphone Jack */
	{ "Headphone Jack", NULL, "OUT1R" },
	{ "Headphone Jack", NULL, "OUT1L" },

	/* Out1 --> Line Out Jack */
	{ "Line Out Jack", NULL, "OUT2R" },
	{ "Line Out Jack", NULL, "OUT2L" },
};
