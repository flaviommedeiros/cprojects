#ifdef HAVE_ALLOCA
if (__libc_use_alloca (nmatch * sizeof (regmatch_t)))
    prev_idx_match = (regmatch_t *) alloca (nmatch * sizeof (regmatch_t));
  else
#endif
    {
      prev_idx_match = re_malloc (regmatch_t, nmatch);
      if (prev_idx_match == NULL)
	{
	  free_fail_stack_return (fs);
	  return REG_ESPACE;
	}
      prev_idx_match_malloced = 1;
    }
