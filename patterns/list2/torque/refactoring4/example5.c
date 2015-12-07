#ifdef __CYGWIN__
if (IamRoot() == 1)
#else
  if ((getuid() == 0) &&
      (geteuid() != pjob->ji_qs.ji_un.ji_momt.ji_exuid))
#endif
    {
    if (setgroups(pjob->ji_grpcache->gc_ngroup,(gid_t *)pjob->ji_grpcache->gc_groups) != PBSE_NONE)
      {
      snprintf(log_buffer,sizeof(log_buffer),
        "setgroups failed for UID = %lu, error: %s\n",
        (unsigned long)pjob->ji_qs.ji_un.ji_momt.ji_exuid,
        strerror(errno));

      log_err(errno, __func__, log_buffer);
      }

    if (setegid(pjob->ji_qs.ji_un.ji_momt.ji_exgid) != PBSE_NONE)
      {
      snprintf(log_buffer, sizeof(log_buffer),
        "setegid(%lu) failed for UID = %lu, error: %s\n",
        (unsigned long)pjob->ji_qs.ji_un.ji_momt.ji_exgid,
        (unsigned long)pjob->ji_qs.ji_un.ji_momt.ji_exuid,
        strerror(errno));

      log_err(errno, __func__, log_buffer);

      return(-1);
      }

    if (setuid_ext(pjob->ji_qs.ji_un.ji_momt.ji_exuid, TRUE) != PBSE_NONE)
      {
      snprintf(log_buffer, sizeof(log_buffer),
        "seteuid(%lu) failed, error: %s\n",
        (unsigned long)pjob->ji_qs.ji_un.ji_momt.ji_exuid,
        strerror(errno));

      log_err(errno, __func__, log_buffer);

      setegid(pbsgroup);
      return(-1);
      }

    changed_to_user = TRUE;
    }
