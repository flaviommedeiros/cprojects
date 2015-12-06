switch (cmd) {
    case AOCONTROL_GET_VOLUME:
    case AOCONTROL_SET_VOLUME: {
        ao_control_vol_t *vol = (ao_control_vol_t *)arg;
        int fd, v, devs;

#ifdef SNDCTL_DSP_GETPLAYVOL
        // Try OSS4 first
        if (volume_oss4(ao, vol, cmd) == CONTROL_OK)
            return CONTROL_OK;
#endif

        if (!af_fmt_is_pcm(ao->format))
            return CONTROL_TRUE;

        if ((fd = open(p->oss_mixer_device, O_RDONLY)) != -1) {
            ioctl(fd, SOUND_MIXER_READ_DEVMASK, &devs);
            if (devs & (1 << p->oss_mixer_channel)) {
                if (cmd == AOCONTROL_GET_VOLUME) {
                    ioctl(fd, MIXER_READ(p->oss_mixer_channel), &v);
                    vol->right = (v & 0xFF00) >> 8;
                    vol->left = v & 0x00FF;
                } else {
                    v = ((int)vol->right << 8) | (int)vol->left;
                    ioctl(fd, MIXER_WRITE(p->oss_mixer_channel), &v);
                }
            } else {
                close(fd);
                return CONTROL_ERROR;
            }
            close(fd);
            return CONTROL_OK;
        }
        return CONTROL_ERROR;
    }
#ifdef SNDCTL_DSP_GETPLAYVOL
    case AOCONTROL_HAS_SOFT_VOLUME:
        return CONTROL_TRUE;
#endif
    }
