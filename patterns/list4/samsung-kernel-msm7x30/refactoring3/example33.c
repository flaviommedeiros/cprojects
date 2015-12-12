switch (cmd) {
		/* get information */
	case SNDRV_DM_FM_IOCTL_INFO:
		{
			struct snd_dm_fm_info info;

			info.fm_mode = opl3->fm_mode;
			info.rhythm = opl3->rhythm;
			if (copy_to_user(argp, &info, sizeof(struct snd_dm_fm_info)))
				return -EFAULT;
			return 0;
		}

	case SNDRV_DM_FM_IOCTL_RESET:
#ifdef CONFIG_SND_OSSEMUL
	case SNDRV_DM_FM_OSS_IOCTL_RESET:
#endif
		snd_opl3_reset(opl3);
		return 0;

	case SNDRV_DM_FM_IOCTL_PLAY_NOTE:
#ifdef CONFIG_SND_OSSEMUL
	case SNDRV_DM_FM_OSS_IOCTL_PLAY_NOTE:
#endif
		{
			struct snd_dm_fm_note note;
			if (copy_from_user(&note, argp, sizeof(struct snd_dm_fm_note)))
				return -EFAULT;
			return snd_opl3_play_note(opl3, &note);
		}

	case SNDRV_DM_FM_IOCTL_SET_VOICE:
#ifdef CONFIG_SND_OSSEMUL
	case SNDRV_DM_FM_OSS_IOCTL_SET_VOICE:
#endif
		{
			struct snd_dm_fm_voice voice;
			if (copy_from_user(&voice, argp, sizeof(struct snd_dm_fm_voice)))
				return -EFAULT;
			return snd_opl3_set_voice(opl3, &voice);
		}

	case SNDRV_DM_FM_IOCTL_SET_PARAMS:
#ifdef CONFIG_SND_OSSEMUL
	case SNDRV_DM_FM_OSS_IOCTL_SET_PARAMS:
#endif
		{
			struct snd_dm_fm_params params;
			if (copy_from_user(&params, argp, sizeof(struct snd_dm_fm_params)))
				return -EFAULT;
			return snd_opl3_set_params(opl3, &params);
		}

	case SNDRV_DM_FM_IOCTL_SET_MODE:
#ifdef CONFIG_SND_OSSEMUL
	case SNDRV_DM_FM_OSS_IOCTL_SET_MODE:
#endif
		return snd_opl3_set_mode(opl3, (int) arg);

	case SNDRV_DM_FM_IOCTL_SET_CONNECTION:
#ifdef CONFIG_SND_OSSEMUL
	case SNDRV_DM_FM_OSS_IOCTL_SET_OPL:
#endif
		return snd_opl3_set_connection(opl3, (int) arg);

#ifdef OPL3_SUPPORT_SYNTH
	case SNDRV_DM_FM_IOCTL_CLEAR_PATCHES:
		snd_opl3_clear_patches(opl3);
		return 0;
#endif

#ifdef CONFIG_SND_DEBUG
	default:
		snd_printk(KERN_WARNING "unknown IOCTL: 0x%x\n", cmd);
#endif
	}
