#if QLZ_STREAMING_BUFFER > 0
if (state->stream_counter + size - 1 >= QLZ_STREAMING_BUFFER)
#endif
	{
		reset_table_compress(state);
		r = base + qlz_compress_core((const unsigned char *)source, (unsigned char*)destination + base, size, state);
#if QLZ_STREAMING_BUFFER > 0
		reset_table_compress(state);
#endif
		if(r == base)
		{
			memcpy(destination + base, source, size);
			r = size + base;
			compressed = 0;
		}
		else
		{
			compressed = 1;
		}
		state->stream_counter = 0;
	}
#if QLZ_STREAMING_BUFFER > 0
	else
	{
		unsigned char *src = state->stream_buffer + state->stream_counter;

		memcpy(src, source, size);
		r = base + qlz_compress_core(src, (unsigned char*)destination + base, size, state);

 		if(r == base)
		{
			memcpy(destination + base, src, size);
			r = size + base;
			compressed = 0;
			reset_table_compress(state);
		}
		else
		{
			compressed = 1;
		}
		state->stream_counter += size;
	}
