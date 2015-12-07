# ifdef MBS_SUPPORT
if (MB_CUR_MAX != 1)
    ret = wcs_regex_compile (pattern, length, re_syntax_options, bufp);
  else
# endif
    ret = byte_regex_compile (pattern, length, re_syntax_options, bufp);
