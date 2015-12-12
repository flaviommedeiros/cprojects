static struct snd_kcontrol_new snd_cmipci_8738_mixer_switches[] = {
#if 0 /* controlled in pcm device */
	DEFINE_MIXER_SWITCH("IEC958 In Record", spdif_in),
	DEFINE_MIXER_SWITCH("IEC958 Out", spdif_out),
	DEFINE_MIXER_SWITCH("IEC958 Out To DAC", spdo2dac),
#endif
	// DEFINE_MIXER_SWITCH("IEC958 Output Switch", spdif_enable),
	{ .name = "IEC958 Output Switch",
	  .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
	  .info = snd_cmipci_uswitch_info,
	  .get = snd_cmipci_spdout_enable_get,
	  .put = snd_cmipci_spdout_enable_put,
	},
	DEFINE_MIXER_SWITCH("IEC958 In Valid", spdi_valid),
	DEFINE_MIXER_SWITCH("IEC958 Copyright", spdif_copyright),
	DEFINE_MIXER_SWITCH("IEC958 5V", spdo_5v),
//	DEFINE_MIXER_SWITCH("IEC958 In/Out 48KHz", spdo_48k),
	DEFINE_MIXER_SWITCH("IEC958 Loop", spdif_loop),
	DEFINE_MIXER_SWITCH("IEC958 In Monitor", spdi_monitor),
};
