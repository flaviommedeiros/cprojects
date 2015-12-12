#if QLZ_STREAMING_BUFFER > 0
if (state->stream_counter + qlz_size_decompressed(source) - 1 >= QLZ_STREAMING_BUFFER) 
#endif
	{
		if((*source & 1) == 1)
		{
			reset_table_decompress(state);
			dsiz = qlz_decompress_core((const unsigned char *)source, (unsigned char *)destination, dsiz, state, (const unsigned char *)destination);
		}
		else
		{
			memcpy(destination, source + qlz_size_header(source), dsiz);
		}
		state->stream_counter = 0;
		reset_table_decompress(state);
	}
#if QLZ_STREAMING_BUFFER > 0
	else
	{
		unsigned char *dst = state->stream_buffer + state->stream_counter;
		if((*source & 1) == 1)
		{
			dsiz = qlz_decompress_core((const unsigned char *)source, dst, dsiz, state, (const unsigned char *)state->stream_buffer);
		}
		else
		{
			memcpy(dst, source + qlz_size_header(source), dsiz);
			reset_table_decompress(state);
		}
		memcpy(destination, dst, dsiz);
		state->stream_counter += dsiz;
	}
