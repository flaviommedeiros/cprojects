#ifdef ALSA_NEW
if ((err = snd_pcm_hw_params_get_period_size(hw, &alsa_period_size, 0)) < 0)	
#else
	alsa_buffer_size = err;
