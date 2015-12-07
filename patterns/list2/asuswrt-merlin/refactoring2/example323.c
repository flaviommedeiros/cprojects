#if !DEFLATE_DEBUG
if (state->debug)
#endif
	    printf("z_decompress%d: bad seq # %d, expected %d\n",
		   state->unit, seq, state->seqno);
