switch (VORTEX_PCM_TYPE(pcm)) {
	case VORTEX_PCM_ADB:
		err = snd_pcm_add_chmap_ctls(pcm, SNDRV_PCM_STREAM_PLAYBACK,
					     snd_pcm_std_chmaps,
					     VORTEX_IS_QUAD(chip) ? 4 : 2,
					     0, NULL);
		if (err < 0)
			return err;
		err = snd_pcm_add_chmap_ctls(pcm, SNDRV_PCM_STREAM_CAPTURE,
					     snd_pcm_std_chmaps, 2, 0, NULL);
		if (err < 0)
			return err;
		break;
#ifdef CHIP_AU8830
	case VORTEX_PCM_A3D:
		err = snd_pcm_add_chmap_ctls(pcm, SNDRV_PCM_STREAM_PLAYBACK,
					     snd_pcm_std_chmaps, 1, 0, NULL);
		if (err < 0)
			return err;
		break;
#endif
	}
