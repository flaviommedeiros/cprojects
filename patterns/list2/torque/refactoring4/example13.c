#ifdef USELIBCPUSET
if (read_cpuset(TBOOTCPUSET_BASE, bootcpus, bootmems) == -1)
#else
  if (read_cpuset(TBOOTCPUSET_PATH, bootcpus, bootmems) == -1)
#endif
    {
    if (errno != ENOENT)
      {
      /* Error */
      log_err(errno, __func__, log_buffer);
      goto finish;
      }
    }
  else
    {
    sprintf(log_buffer, "subtracting cpus of boot cpuset: ");
    hwloc_bitmap_list_snprintf(log_buffer + strlen(log_buffer), sizeof(log_buffer) - strlen(log_buffer), bootcpus);
    log_event(PBSEVENT_SYSTEM, PBS_EVENTCLASS_SERVER, __func__, log_buffer);

    sprintf(log_buffer, "subtracting mems of boot cpuset: ");
    hwloc_bitmap_list_snprintf(log_buffer + strlen(log_buffer), sizeof(log_buffer) - strlen(log_buffer), bootmems);
    log_event(PBSEVENT_SYSTEM, PBS_EVENTCLASS_SERVER, __func__, log_buffer);

    hwloc_bitmap_andnot(cpus, cpus, bootcpus);
    hwloc_bitmap_andnot(mems, mems, bootmems);
    }
