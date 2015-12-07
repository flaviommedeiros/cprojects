#if defined (HANDLE_MULTIBYTE)
if (_rl_compare_chars (ols, 0, NULL, nls, 0, NULL) == 0)
#else
  else if (*ols != *nls)
#endif
    {
      if (*ols)			/* don't step past the NUL */
	{
	  if (MB_CUR_MAX > 1 && rl_byte_oriented == 0)
	    ols = old + _rl_find_next_mbchar (old, ols - old, 1, MB_FIND_ANY);
	  else
	    ols++;
	}
      if (*nls)
	{
	  if (MB_CUR_MAX > 1 && rl_byte_oriented == 0)
	    nls = new + _rl_find_next_mbchar (new, nls - new, 1, MB_FIND_ANY);
	  else
	    nls++;
	}
    }
