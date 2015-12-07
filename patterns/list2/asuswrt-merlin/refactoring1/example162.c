if (env_sysrc && file_exists_p (env_sysrc))
    {
      ok &= run_wgetrc (env_sysrc);
      /* If there are any problems parsing the system wgetrc file, tell
         the user and exit */
      if (! ok)
        {
          fprintf (stderr, _("\
Parsing system wgetrc file (env SYSTEM_WGETRC) failed.  Please check\n\
'%s',\n\
or specify a different file using --config.\n"), env_sysrc);
          exit (WGET_EXIT_PARSE_ERROR);
        }
    }
  /* Otherwise, if SYSTEM_WGETRC is defined, use it.  */
#ifdef SYSTEM_WGETRC
  else if (file_exists_p (SYSTEM_WGETRC))
    ok &= run_wgetrc (SYSTEM_WGETRC);
#endif
