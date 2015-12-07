# ifdef MBS_SUPPORT
if (MB_CUR_MAX != 1)
    result = wcs_re_match_2_internal (bufp, NULL, 0, string, size,
				      pos, regs, size,
				      NULL, 0, NULL, 0, NULL, NULL);
  else
# endif
    result = byte_re_match_2_internal (bufp, NULL, 0, string, size,
				  pos, regs, size);
