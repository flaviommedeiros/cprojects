switch (key) {
#ifdef HAVE_CDDB
	case 0:
		if (parse_cddb_url(val, &http_uri, &use_http)) {
			http_free_uri(&http_uri);
			free(cddb_url);
			cddb_url = xstrdup(val);
		} else
			return -IP_ERROR_INVALID_URI;
		break;
#endif
	default:
		return -IP_ERROR_NOT_OPTION;
	}
