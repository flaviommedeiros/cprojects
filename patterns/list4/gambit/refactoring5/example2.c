#ifdef USE_POSIX
if (d->fd_rd < 0)
    *len_done = 0;
  else
    {
      int n = 0;

      if ((n = read (d->fd_rd, buf, len)) < 0)
        {
#if 0
          if (errno == EIO) errno = EAGAIN;
#else
          if (errno == EIO) /* on linux, treating EIO as EAGAIN gives an infinite loop */
            n = 0;
          else
#endif
            e = err_code_from_errno ();
        }

      *len_done = n;
    }
