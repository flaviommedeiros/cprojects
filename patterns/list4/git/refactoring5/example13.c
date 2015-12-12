#ifdef HAVE_ALLOCA
if (__libc_use_alloca (sizeof (struct dests_alloc)))
    dests_alloc = (struct dests_alloc *) alloca (sizeof (struct dests_alloc));
  else
#endif
    {
      dests_alloc = re_malloc (struct dests_alloc, 1);
      if (BE (dests_alloc == NULL, 0))
	return 0;
      dests_node_malloced = true;
    }
