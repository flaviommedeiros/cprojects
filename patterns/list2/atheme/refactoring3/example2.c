switch (preg->type)
	{
		case at_posix:
			return regexec(&preg->un.posix, string, 0, NULL, 0) == 0;
#ifdef HAVE_PCRE
		case at_pcre:
			return pcre_exec(preg->un.pcre, NULL, string, strlen(string), 0, 0, NULL, 0) >= 0;
#endif
		default:
			slog(LG_ERROR, "regex_match(): we were given a pattern of unknown type %d, bad!", preg->type);
			return false;
	}
