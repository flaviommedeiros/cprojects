# ifdef MBS_SUPPORT
if (MB_CUR_MAX != 1)
    ret = wcs_regex_compile (s, strlen (s), re_syntax_options, &re_comp_buf);
  else
# endif
    ret = byte_regex_compile (s, strlen (s), re_syntax_options, &re_comp_buf);
