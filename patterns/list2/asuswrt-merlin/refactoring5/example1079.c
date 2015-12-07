# ifdef MBS_SUPPORT
if (MB_CUR_MAX != 1)
    return wcs_re_search_2 (bufp, string1, size1, string2, size2, startpos,
			    range, regs, stop);
  else
# endif
    return byte_re_search_2 (bufp, string1, size1, string2, size2, startpos,
			     range, regs, stop);
