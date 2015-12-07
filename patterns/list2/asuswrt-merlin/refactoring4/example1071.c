#ifdef NO_64BIT_MATH
if (high32(rdbx->index) > 0 ||
	  low32(rdbx->index) > seq_num_median)
#else
  if (rdbx->index > seq_num_median)
#endif
    return index_guess(&rdbx->index, guess, s);
