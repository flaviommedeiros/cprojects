#ifdef HAVE_LIBREADLINE
if (isatty(STDIN_FILENO)) {
		p = readline(prompt);
		if (!p)
			return 1;
		memcpy(buf, p, bufsz);
		free(p);
	} else
#endif
	{
		fputs(prompt, stdout);
		fflush(stdout);

		if (!fgets(buf, bufsz, stdin))
			return 1;
	}
