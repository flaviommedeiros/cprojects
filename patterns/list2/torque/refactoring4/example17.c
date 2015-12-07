#if defined(HAVE_STRUCT_STAT64) && defined(HAVE_STAT64) && defined(LARGEFILE_WORKS)
if (lstat64(namebuf, &sb) == -1)
#else
      if (lstat(namebuf, &sb) == -1)
#endif
        {
        log_err(errno, __func__, "stat");

        rtnv = -1;

        continue;
        }
