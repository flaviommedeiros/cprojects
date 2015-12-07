if (safe_filename
      && strcmp (safe_filename, ".")
      && strcmp (safe_filename, "..")
#ifdef WIN32
      && win_safe_filename (safe_filename)
#endif
      )
    {
      const size_t outsize = strlen(safe_filename) + (directory ? strlen (directory) : 0) + 16;
      struct buffer out = alloc_buf_gc (outsize, gc);
      char dirsep[2];

      dirsep[0] = OS_SPECIFIC_DIRSEP;
      dirsep[1] = '\0';

      if (directory)
	buf_printf (&out, "%s%s", directory, dirsep);
      buf_printf (&out, "%s", safe_filename);

      return BSTR (&out);
    }
  else
    return NULL;
