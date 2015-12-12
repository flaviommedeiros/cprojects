static struct sbmix_elem snd_als4000_controls[] = {
	SB_DOUBLE("PCM Playback Switch",
		  SB_DT019X_OUTPUT_SW2, SB_DT019X_OUTPUT_SW2, 2, 1, 1),
	SB_DOUBLE("Synth Playback Switch",
		  SB_DT019X_OUTPUT_SW2, SB_DT019X_OUTPUT_SW2, 4, 3, 1),
	SB_SINGLE("Mic Boost (+20dB)", SB_ALS4000_MIC_IN_GAIN, 0, 0x03),
	SB_SINGLE("Master Mono Playback Switch", SB_ALS4000_MONO_IO_CTRL, 5, 1),
	{
		.name = "Master Mono Capture Route",
		.type = SB_MIX_MONO_CAPTURE_ALS4K
	},
	SB_SINGLE("Mono Playback Switch", SB_DT019X_OUTPUT_SW2, 0, 1),
	SB_SINGLE("Analog Loopback Switch", SB_ALS4000_MIC_IN_GAIN, 7, 0x01),
	SB_SINGLE("3D Control - Switch", SB_ALS4000_3D_SND_FX, 6, 0x01),
	SB_SINGLE("Digital Loopback Switch",
		  SB_ALS4000_CR3_CONFIGURATION, 7, 0x01),
	/* FIXME: functionality of 3D controls might be swapped, I didn't find
	 * a description of how to identify what is supposed to be what */
	SB_SINGLE("3D Control - Level", SB_ALS4000_3D_SND_FX, 0, 0x07),
	/* FIXME: maybe there's actually some standard 3D ctrl name for it?? */
	SB_SINGLE("3D Control - Freq", SB_ALS4000_3D_SND_FX, 4, 0x03),
	/* FIXME: ALS4000a.pdf mentions BBD (Bucket Brigade Device) time delay,
	 * but what ALSA 3D attribute is that actually? "Center", "Depth",
	 * "Wide" or "Space" or even "Level"? Assuming "Wide" for now... */
	SB_SINGLE("3D Control - Wide", SB_ALS4000_3D_TIME_DELAY, 0, 0x0f),
	SB_SINGLE("3D PowerOff Switch", SB_ALS4000_3D_TIME_DELAY, 4, 0x01),
	SB_SINGLE("Master Playback 8kHz / 20kHz LPF Switch",
		  SB_ALS4000_FMDAC, 5, 0x01),
#ifdef NOT_AVAILABLE
	SB_SINGLE("FMDAC Switch (Option ?)", SB_ALS4000_FMDAC, 0, 0x01),
	SB_SINGLE("QSound Mode", SB_ALS4000_QSOUND, 1, 0x1f),
#endif
};
