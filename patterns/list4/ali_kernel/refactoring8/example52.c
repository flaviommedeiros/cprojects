static unsigned char snd_cmi8330_image[((CMI8330_CDINGAIN)-16) + 1] =
{
	0x40,			/* 16 - recording mux (SB-mixer-enabled) */
#ifdef ENABLE_SB_MIXER
	0x40,			/* 17 - mute mux (Mode2) */
#else
	0x0,			/* 17 - mute mux */
#endif
	0x0,			/* 18 - vol */
	0x0,			/* 19 - master volume */
	0x0,			/* 20 - line-in volume */
	0x0,			/* 21 - cd-in volume */
	0x0,			/* 22 - wave volume */
	0x0,			/* 23 - mute/rec mux */
	0x0,			/* 24 - wave rec gain */
	0x0,			/* 25 - line-in rec gain */
	0x0			/* 26 - cd-in rec gain */
};
