# ifdef MBS_SUPPORT
if (MB_CUR_MAX != 1)
    ret = wcs_regex_compile (pattern, strlen (pattern), syntax, preg);
  else
# endif
    ret = byte_regex_compile (pattern, strlen (pattern), syntax, preg);
