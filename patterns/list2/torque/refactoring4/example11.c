#ifdef USELIBCPUSET
if (read_cpuset(TTORQUECPUSET_BASE, cpus, mems) == -1)
#else
  if (read_cpuset(TTORQUECPUSET_PATH, cpus, mems) == -1)
#endif
    {
    if (errno != ENOENT)
      {
      /* Error */
      log_err(errno, __func__, log_buffer);
      goto finish;
      }
    }
  else if (! (hwloc_bitmap_iszero(cpus) || hwloc_bitmap_iszero(mems)))
    {
    /* Exists with non-empty cpus and mems, adjust and tell what we have and return */
    remove_logical_processor_if_requested(&cpus);
    sprintf(log_buffer, "cpus = ");
    hwloc_bitmap_list_snprintf(log_buffer + strlen(log_buffer), sizeof(log_buffer) - strlen(log_buffer), cpus);
    log_event(PBSEVENT_SYSTEM, PBS_EVENTCLASS_SERVER, __func__, log_buffer);

    sprintf(log_buffer, "mems = ");
    hwloc_bitmap_list_snprintf(log_buffer + strlen(log_buffer), sizeof(log_buffer) - strlen(log_buffer), mems);
    log_event(PBSEVENT_SYSTEM, PBS_EVENTCLASS_SERVER, __func__, log_buffer);

    rc = 0;
    goto finish;
    }
