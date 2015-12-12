#ifdef HAVE_LIBZ
if (hasSuffix(path, ".gz"))
		fp = cfopen(path, mode, 1);
	else
#endif
	{
		fp = cfopen(path, mode, 0);
#ifdef HAVE_LIBZ
		if (fp == NULL)
		{
			char	   *fname;

			fname = psprintf("%s.gz", path);
			fp = cfopen(fname, mode, 1);
			free_keep_errno(fname);
		}
#endif
	}
