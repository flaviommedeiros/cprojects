static struct sbmix_elem *snd_als4000_controls[] = {
						/* ALS4000a.PDF regs page */
	&snd_sb16_ctl_master_play_vol,		/* MX30/31 12 */
	&snd_dt019x_ctl_pcm_play_switch,	/* MX4C    16 */
	&snd_sb16_ctl_pcm_play_vol,		/* MX32/33 12 */
	&snd_sb16_ctl_synth_capture_route,	/* MX3D/3E 14 */
	&snd_dt019x_ctl_synth_play_switch,	/* MX4C    16 */
	&snd_sb16_ctl_synth_play_vol,		/* MX34/35 12/13 */
	&snd_sb16_ctl_cd_capture_route,		/* MX3D/3E 14 */
	&snd_sb16_ctl_cd_play_switch,		/* MX3C    14 */
	&snd_sb16_ctl_cd_play_vol,		/* MX36/37 13 */
	&snd_sb16_ctl_line_capture_route,	/* MX3D/3E 14 */
	&snd_sb16_ctl_line_play_switch,		/* MX3C    14 */
	&snd_sb16_ctl_line_play_vol,		/* MX38/39 13 */
	&snd_sb16_ctl_mic_capture_route,	/* MX3D/3E 14 */
	&snd_als4000_ctl_mic_20db_boost,	/* MX4D    16 */
	&snd_sb16_ctl_mic_play_switch,		/* MX3C    14 */
	&snd_sb16_ctl_mic_play_vol,		/* MX3A    13 */
	&snd_sb16_ctl_pc_speaker_vol,		/* MX3B    14 */
	&snd_sb16_ctl_capture_vol,		/* MX3F/40 15 */
	&snd_sb16_ctl_play_vol,			/* MX41/42 15 */
	&snd_als4000_ctl_master_mono_playback_switch, /* MX4C 16 */
	&snd_als4k_ctl_master_mono_capture_route, /* MX4B  16 */
	&snd_als4000_ctl_mono_playback_switch,	/* MX4C    16 */
	&snd_als4000_ctl_mixer_analog_loopback, /* MX4D    16 */
	&snd_als4000_ctl_mixer_digital_loopback, /* CR3    21 */
	&snd_als4000_3d_control_switch,		 /* MX50   17 */
	&snd_als4000_3d_control_ratio,		 /* MX50   17 */
	&snd_als4000_3d_control_freq,		 /* MX50   17 */
	&snd_als4000_3d_control_delay,		 /* MX51   18 */
	&snd_als4000_3d_control_poweroff_switch,	/* MX51    18 */
	&snd_als4000_ctl_3db_freq_control_switch,	/* MX4F    17 */
#ifdef NOT_AVAILABLE
	&snd_als4000_ctl_fmdac,
	&snd_als4000_ctl_qsound,
#endif
};
