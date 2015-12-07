#ifdef SYSTEM_WGETRC
if (!strcmp (file, SYSTEM_WGETRC))
    {
      fprintf (stderr, _("\
%s: Warning: Both system and user wgetrc point to %s.\n"),
               exec_name, quote (file));
    }
  else
#endif
    ok &= run_wgetrc (file);
