#ifdef HAVE_ALLOCA
if (__libc_use_alloca ((sizeof (re_node_set) + sizeof (bitset_t)) * SBC_MAX
			 + ndests * 3 * sizeof (re_dfastate_t *)))
    dest_states = (re_dfastate_t **)
      alloca (ndests * 3 * sizeof (re_dfastate_t *));
  else
#endif
    {
      dest_states = (re_dfastate_t **)
	malloc (ndests * 3 * sizeof (re_dfastate_t *));
      if (BE (dest_states == NULL, 0))
	{
out_free:
	  if (dest_states_malloced)
	    free (dest_states);
	  re_node_set_free (&follows);
	  for (i = 0; i < ndests; ++i)
	    re_node_set_free (dests_node + i);
	  if (dests_node_malloced)
	    free (dests_alloc);
	  return 0;
	}
      dest_states_malloced = true;
    }
