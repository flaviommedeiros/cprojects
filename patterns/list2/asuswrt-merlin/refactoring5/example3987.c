# ifdef MBS_SUPPORT
if (MB_CUR_MAX != 1)
    return wcs_re_compile_fastmap(bufp);
  else
# endif
    return byte_re_compile_fastmap(bufp);
