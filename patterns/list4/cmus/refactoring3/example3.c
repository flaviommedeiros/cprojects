switch (key) {
	case CFG_SERVER_NAME:
		free(server_name);
		server_name = val[0] != '\0' ? xstrdup(val) : NULL;
		break;
#ifdef HAVE_SAMPLERATE
	case CFG_RESAMPLING_QUALITY:
		if (strlen(val) != 1) {
			return -OP_ERROR_NOT_SUPPORTED;
		}
		switch (val[0]) {
		default:
		case '2':
			src_quality = SRC_SINC_BEST_QUALITY;
			break;
		case '1':
			src_quality = SRC_SINC_MEDIUM_QUALITY;
			break;
		case '0':
			src_quality = SRC_SINC_FASTEST;
			break;
		}
		break;
#endif
	default:
		d_print("unknown key %d = %s\n", key, val);
		return -OP_ERROR_NOT_OPTION;
	}
