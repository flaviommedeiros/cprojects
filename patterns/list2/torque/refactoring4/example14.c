#ifdef USELIBCPUSET
if (read_cpuset(TTORQUECPUSET_BASE, tcpus, tmems) == -1)
#else
  if (read_cpuset(TTORQUECPUSET_PATH, tcpus, tmems) == -1)
#endif
    {
    /* Error */
    log_err(errno, __func__, log_buffer);
    goto finish;
    }
