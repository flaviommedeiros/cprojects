# ifdef MBS_SUPPORT
if (MB_CUR_MAX != 1)
    result = wcs_re_match_2_internal (bufp, string1, size1, string2, size2,
				      pos, regs, stop,
				      NULL, 0, NULL, 0, NULL, NULL);
  else
# endif
    result = byte_re_match_2_internal (bufp, string1, size1, string2, size2,
				  pos, regs, stop);
