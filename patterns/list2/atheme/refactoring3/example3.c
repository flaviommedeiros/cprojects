switch (preg->type)
	{
		case at_posix:
			regfree(&preg->un.posix);
			break;
#ifdef HAVE_PCRE
		case at_pcre:
			pcre_free(preg->un.pcre);
			break;
#endif
		default:
			slog(LG_ERROR, "regex_destroy(): we were given a pattern of unknown type %d, bad!", preg->type);
			break;
	}
