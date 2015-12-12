switch (key) {
	case CFG_SERVER_NAME:
		*val = xstrdup(server_name != NULL ? server_name : "");
		break;
#ifdef HAVE_SAMPLERATE
	case CFG_RESAMPLING_QUALITY:
		switch (src_quality) {
		case SRC_SINC_BEST_QUALITY:
			*val = xstrdup("2");
			break;
		case SRC_SINC_MEDIUM_QUALITY:
			*val = xstrdup("1");
			break;
		case SRC_SINC_FASTEST:
			*val = xstrdup("0");
			break;
		}
		break;
#endif
	default:
		return -OP_ERROR_NOT_OPTION;
	}
