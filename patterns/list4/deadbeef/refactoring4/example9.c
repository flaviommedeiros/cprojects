#ifdef ALSA_NEW
if ((err = snd_pcm_hw_params_set_period_time_near(pcm, hw, &alsa_period_time, 0)) < 0)
#else
	if ((err = snd_pcm_hw_params_set_period_time_near(pcm, hw, alsa_period_time, 0)) < 0)
#endif
	{
		printf("Set period time failed: %s.\n", snd_strerror(-err));
		return -1;
	}
