#ifdef HAVE_LSEEK64
if (lseek64(fds, (off_t)(TaskID*sizeof(ptask->ti_qs)), SEEK_SET) < 0)
#else
  if (lseek(fds, (off_t)(TaskID*sizeof(ptask->ti_qs)), SEEK_SET) < 0)
#endif
    {
    log_err(errno, __func__, "lseek");

    close(fds);

    return(-1);
    }
