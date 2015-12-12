switch (obj_type) {
	case MP4_MPEG4_AAC_MAIN_AUDIO_TYPE:	return "Main";
	case MP4_MPEG4_AAC_LC_AUDIO_TYPE:	return "LC";
	case MP4_MPEG4_AAC_SSR_AUDIO_TYPE:	return "SSR";
	case MP4_MPEG4_AAC_LTP_AUDIO_TYPE:	return "LTP";
#ifdef MP4_MPEG4_AAC_HE_AUDIO_TYPE
	case MP4_MPEG4_AAC_HE_AUDIO_TYPE:	return "HE";
#endif
	case MP4_MPEG4_AAC_SCALABLE_AUDIO_TYPE:	return "Scalable";
	}
