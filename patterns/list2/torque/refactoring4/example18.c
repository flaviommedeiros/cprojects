#if defined(FNDELAY) && !defined(__hpux)
if (flags & FNDELAY)
#else
  if (flags & O_NONBLOCK)
#endif
    {
      /* flags already set */
      /* NO-OP */
    }
  else
    {
#if defined(FNDELAY) && !defined(__hpux)
    flags |= FNDELAY;
#else
    flags |= O_NONBLOCK;
#endif
    if (fcntl(fd,F_SETFL,flags) == -1)
      {
      snprintf(log_buf, sizeof(log_buf), "cannot set file status flags to %d for unmunge of %s", 
	       flags, mungeFileName);
      log_err(errno, __func__, log_buf);
      pclose(munge_pipe);
      return(PBSE_SYSTEM);
      }
    }
