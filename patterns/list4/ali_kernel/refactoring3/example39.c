switch (d) {
		/* master volume unscaled controls */
	case SOUND_MIXER_LINE:			/* line pot control */
		/* scaled by IMIX in digital mix */
		writeb(bLeft, dev.SMA + SMA_bInPotPosLeft);
		writeb(bRight, dev.SMA + SMA_bInPotPosRight);
		if (msnd_send_word(&dev, 0, 0, HDEXAR_IN_SET_POTS) == 0)
			chk_send_dsp_cmd(&dev, HDEX_AUX_REQ);
		break;
#ifndef MSND_CLASSIC
	case SOUND_MIXER_MIC:			/* mic pot control */
		/* scaled by IMIX in digital mix */
		writeb(bLeft, dev.SMA + SMA_bMicPotPosLeft);
		writeb(bRight, dev.SMA + SMA_bMicPotPosRight);
		if (msnd_send_word(&dev, 0, 0, HDEXAR_MIC_SET_POTS) == 0)
			chk_send_dsp_cmd(&dev, HDEX_AUX_REQ);
		break;
#endif
	case SOUND_MIXER_VOLUME:		/* master volume */
		writew(wLeft, dev.SMA + SMA_wCurrMastVolLeft);
		writew(wRight, dev.SMA + SMA_wCurrMastVolRight);
		/* fall through */

	case SOUND_MIXER_LINE1:			/* aux pot control */
		/* scaled by master volume */
		/* fall through */

		/* digital controls */
	case SOUND_MIXER_SYNTH:			/* synth vol (dsp mix) */
	case SOUND_MIXER_PCM:			/* pcm vol (dsp mix) */
	case SOUND_MIXER_IMIX:			/* input monitor (dsp mix) */
		/* scaled by master volume */
		updatemaster = 1;
		break;

	default:
		return 0;
	}
