#if !DEFLATE_DEBUG
if (state->debug)
#endif
		printf("z_incomp%d: inflateIncomp returned %d (%s)\n",
		       state->unit, r, (state->strm.msg? state->strm.msg: ""));
