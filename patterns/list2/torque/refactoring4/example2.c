#if defined(HAVE_STRUCT_STAT64) && defined(HAVE_STAT64) && defined(LARGEFILE_WORKS)
if (job_log_opened && (fstat64(fileno(joblogfile), &file_stat) != 0))
#else
  if (job_log_opened && (fstat(fileno(joblogfile), &file_stat) != 0))
#endif
    {
    /* FAILURE */

    log_err(errno, __func__, "PBS cannot fstat joblogfile");
    pthread_mutex_unlock(&job_log_mutex);

    return(0);
    }
