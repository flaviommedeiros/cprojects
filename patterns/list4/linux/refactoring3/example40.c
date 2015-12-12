switch (d) {
	case SOUND_MIXER_VOLUME:
	case SOUND_MIXER_PCM:
	case SOUND_MIXER_LINE:
	case SOUND_MIXER_IMIX:
	case SOUND_MIXER_LINE1:
#ifndef MSND_CLASSIC
	case SOUND_MIXER_MIC:
	case SOUND_MIXER_SYNTH:
#endif
		return (dev.left_levels[d] >> 8) * 100 / 0xff | 
			(((dev.right_levels[d] >> 8) * 100 / 0xff) << 8);
	default:
		return 0;
	}
