switch (format->interleave) {
		case 1:
			dsp_format = DSP_AUDIOFORM_MM_32BE;
			break;
#ifdef ECHOCARD_HAS_STEREO_BIG_ENDIAN32
		case 2:
			dsp_format = DSP_AUDIOFORM_SS_32BE;
			break;
#endif
		}
