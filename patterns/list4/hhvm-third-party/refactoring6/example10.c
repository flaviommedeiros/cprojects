if (
#if defined NATIVE_ZOS
        (zos_type == __ZOS_NOFILE && DEE_action == DEE_SKIP) ||
#else  /* all other OS */
        (!isregfile(pathname) && DEE_action == DEE_SKIP) ||
#endif
        !test_incexc(lastcomp, include_patterns, exclude_patterns))
  return -1;
