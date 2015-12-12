switch (key) {
#ifdef HAVE_CDDB
	case 0:
		if (!cddb_url)
			cddb_url = xstrdup("freedb.freedb.org:8880");
		*val = xstrdup(cddb_url);
		break;
#endif
	default:
		return -IP_ERROR_NOT_OPTION;
	}
