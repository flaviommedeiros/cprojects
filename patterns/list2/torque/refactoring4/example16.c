#if defined(HAVE_STRUCT_STAT64) && defined(HAVE_STAT64) && defined(LARGEFILE_WORKS)
if (lstat64(dirname, &sb) == -1)
#else
  if (lstat(dirname, &sb) == -1)
#endif
    {

    if (errno != ENOENT)
      log_err(errno, __func__, "stat");

    return(-1);
    }
