#if !DEFLATE_DEBUG
if (state->debug)
#endif
	    printf("z_decompress%d: inflate returned %d (%s)\n",
		   state->unit, r, (state->strm.msg? state->strm.msg: ""));
