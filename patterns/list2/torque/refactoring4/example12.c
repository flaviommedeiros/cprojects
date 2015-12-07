#ifdef USELIBCPUSET
if (read_cpuset(TROOTCPUSET_BASE, cpus, mems) == -1)
#else
  if (read_cpuset(TROOTCPUSET_PATH, cpus, mems) == -1)
#endif
    {
    log_err(errno, __func__, log_buffer);
    goto finish;
    }
