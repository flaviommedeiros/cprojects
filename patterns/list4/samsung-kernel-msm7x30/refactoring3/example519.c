switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
#ifdef CONFIG_PM
	case SNDRV_PCM_TRIGGER_RESUME:
#endif
		err = line6_pcm_acquire(line6pcm, LINE6_BIT_PCM_ALSA_PLAYBACK_STREAM);

		if (err < 0)
			return err;

		break;

	case SNDRV_PCM_TRIGGER_STOP:
#ifdef CONFIG_PM
	case SNDRV_PCM_TRIGGER_SUSPEND:
#endif
		err = line6_pcm_release(line6pcm, LINE6_BIT_PCM_ALSA_PLAYBACK_STREAM);

		if (err < 0)
			return err;

		break;

	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		set_bit(LINE6_INDEX_PAUSE_PLAYBACK, &line6pcm->flags);
		break;

	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		clear_bit(LINE6_INDEX_PAUSE_PLAYBACK, &line6pcm->flags);
		break;

	default:
		return -EINVAL;
	}
