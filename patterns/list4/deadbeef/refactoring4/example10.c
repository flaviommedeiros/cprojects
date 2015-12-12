#ifdef ALSA_NEW
if ((err = snd_pcm_hw_params_get_buffer_size(hw, &alsa_buffer_size)) < 0)
#else
	if ((err = snd_pcm_hw_params_get_buffer_size(hw)) < 0)
#endif
	{
		printf ("snd_pcm_hw_params_get_buffer_size() failed: %s\n", snd_strerror(-err));
		return -1;
	}
