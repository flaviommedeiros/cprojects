#ifdef ALSA_NEW
if ((err = snd_pcm_hw_params_set_buffer_time_near(pcm, hw, &alsa_buffer_time, 0)) < 0)
#else
	if ((err = snd_pcm_hw_params_set_buffer_time_near(pcm, hw, alsa_buffer_time, 0)) < 0)
#endif
	{
		printf("Set buffer time failed: %s.\n", snd_strerror(-err));
		return -1;
	}
