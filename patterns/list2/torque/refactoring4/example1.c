#if defined(HAVE_STRUCT_STAT64) && defined(HAVE_STAT64) && defined(LARGEFILE_WORKS)
if (log_opened && (fstat64(fileno(logfile), &file_stat) != 0))
#else
  if (log_opened && (fstat(fileno(logfile), &file_stat) != 0))
#endif
    {
    /* FAILURE */

    pthread_mutex_unlock(&log_mutex);
    /* log_err through log_ext will lock the log_mutex, so release log_mutex before calling log_err */
    log_err(errno, "log_size", "PBS cannot fstat logfile");

    return(0);
    }
