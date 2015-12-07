#ifdef NO_BINARY_CLAUSES
if (!ISLITREASON (reason))
#endif
    {
      assert (reason->locked);
      reason->locked = 0;
      if (reason->learned && reason->size > 2)
	{
	  assert (ps->llocked > 0);
	  ps->llocked--;
	}
    }
