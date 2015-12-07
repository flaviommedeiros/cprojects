# ifdef	HAS_FSTAT
if (fstat(fileno(f), st) < 0)
# else
	if (stat(name, st) < 0)
# endif
	{
		perror(name);
		fprintf(stderr, "%s: cannot stat \"%s\"\n", progname, name);
		return 0;
	}
